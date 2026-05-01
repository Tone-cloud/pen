#pragma once

#include <QObject>
#include <QString>

class ClockController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentTime READ currentTime NOTIFY currentTimeChanged)

public:
    explicit ClockController(QObject *parent = nullptr);

    QString currentTime() const;

    Q_INVOKABLE void timeChanged();

signals:
    void currentTimeChanged();
};
