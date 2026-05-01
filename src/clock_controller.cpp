#include "clock_controller.h"

#include <QDateTime>

ClockController::ClockController(QObject *parent) : QObject(parent) {}

QString ClockController::currentTime() const {
    return QDateTime::currentDateTime().toString("hh:mm:ss");
}

void ClockController::timeChanged() {
    emit currentTimeChanged();
}
