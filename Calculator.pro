TEMPLATE = app
TARGET = Calculator

QT += core gui widgets

CONFIG += c++11

SOURCES += main.cpp \
    mainwindow.cpp

HEADERS += mainwindow.h

# Add paths for dictpen-libs to fix linking errors for GLESv2, EGL, mali
LIBS += -L$$PWD/../dictpen-libs -lGLESv2 -lEGL -lmali
INCLUDEPATH += $$PWD/../dictpen-libs/include

# Notes for cross-compiling to aarch64 (example):
# If you have a Qt build for aarch64, use that qmake. Example:
#   /opt/qt5.15.2-aarch64/bin/qmake -spec linux-aarch64-g++ Calculator.pro
# Or, point toolchain directly (example toolchain names vary):
#   /path/to/qt/bin/qmake "QMAKE_CC=/usr/bin/aarch64-linux-gnu-gcc" "QMAKE_CXX=/usr/bin/aarch64-linux-gnu-g++" Calculator.pro