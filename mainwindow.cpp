#include "mainwindow.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), pendingValue(0.0), waitingForOperand(true)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(36);

    QGridLayout *grid = new QGridLayout;

    // First row: Clear, Exit, Divide
    QPushButton *clearBtn = new QPushButton("C");
    QPushButton *exitBtn = new QPushButton("Exit");
    QPushButton *divBtn = new QPushButton("/");
    grid->addWidget(clearBtn, 0, 0);
    grid->addWidget(exitBtn, 0, 1);
    grid->addWidget(divBtn, 0, 2);

    // Digits and operators
    QString digits[9] = {"7","8","9","4","5","6","1","2","3"};
    int idx = 0;
    for (int row = 1; row <= 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton *btn = new QPushButton(digits[idx++]);
            grid->addWidget(btn, row, col);
            connect(btn, &QPushButton::clicked, this, &MainWindow::digitClicked);
        }
    }

    QPushButton *mulBtn = new QPushButton("*");
    QPushButton *subBtn = new QPushButton("-");
    QPushButton *addBtn = new QPushButton("+");
    grid->addWidget(mulBtn, 1, 3-1); // place roughly next to row1 col2
    grid->addWidget(subBtn, 2, 3-1);
    grid->addWidget(addBtn, 3, 3-1);
    // Note: we put operator buttons in column 2 to match layout

    // Zero, point and equals on last row
    QPushButton *zeroBtn = new QPushButton("0");
    QPushButton *pointBtn = new QPushButton(".");
    QPushButton *eqBtn = new QPushButton("=");
    grid->addWidget(zeroBtn, 4, 0, 1, 2); // span two columns
    grid->addWidget(pointBtn, 4, 2);
    grid->addWidget(eqBtn, 4, 3-1);

    // Connect signals
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearClicked);
    connect(exitBtn, &QPushButton::clicked, this, &MainWindow::exitClicked);
    connect(divBtn, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(mulBtn, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(subBtn, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(eqBtn, &QPushButton::clicked, this, &MainWindow::equalsClicked);
    connect(zeroBtn, &QPushButton::clicked, this, &MainWindow::digitClicked);
    connect(pointBtn, &QPushButton::clicked, this, &MainWindow::pointClicked);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(display);
    mainLayout->addLayout(grid);

    central->setLayout(mainLayout);
    setWindowTitle("Calculator");
    setMinimumSize(260, 280);
}

void MainWindow::digitClicked()
{
    QPushButton *clicked = qobject_cast<QPushButton *>(sender());
    if (!clicked)
        return;

    QString digit = clicked->text();
    if (display->text() == "0" && digit == "0")
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }

    display->setText(display->text() + digit);
}

void MainWindow::pointClicked()
{
    if (waitingForOperand) {
        display->setText("0");
        waitingForOperand = false;
    }
    if (!display->text().contains('.'))
        display->setText(display->text() + ".");
}

void MainWindow::operatorClicked()
{
    QPushButton *clicked = qobject_cast<QPushButton *>(sender());
    if (!clicked)
        return;

    double value = display->text().toDouble();

    if (!pendingOperator.isEmpty()) {
        // compute previous pending
        double result = calculate(pendingValue, pendingOperator, value);
        display->setText(QString::number(result, 'g', 15));
        pendingValue = result;
    } else {
        pendingValue = value;
    }

    pendingOperator = clicked->text();
    waitingForOperand = true;
}

void MainWindow::equalsClicked()
{
    double right = display->text().toDouble();
    if (pendingOperator.isEmpty())
        return;
    double result = calculate(pendingValue, pendingOperator, right);
    display->setText(QString::number(result, 'g', 15));
    pendingOperator.clear();
    waitingForOperand = true;
}

void MainWindow::clearClicked()
{
    display->setText("0");
    pendingOperator.clear();
    pendingValue = 0.0;
    waitingForOperand = true;
}

void MainWindow::exitClicked()
{
    qApp->quit();
}

double MainWindow::calculate(double left, const QString &op, double right)
{
    if (op == "+")
        return left + right;
    if (op == "-")
        return left - right;
    if (op == "*")
        return left * right;
    if (op == "/") {
        if (qFuzzyCompare(right + 1.0, 1.0)) {
            QMessageBox::warning(this, "Error", "Division by zero");
            return 0.0;
        }
        return left / right;
    }
    return right;
}
