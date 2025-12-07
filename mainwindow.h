#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void digitClicked();
    void pointClicked();
    void operatorClicked();
    void equalsClicked();
    void clearClicked();
    void exitClicked();

private:
    QLineEdit *display;
    double pendingValue;
    QString pendingOperator;
    bool waitingForOperand;

    double calculate(double left, const QString &op, double right);
};

#endif // MAINWINDOW_H
