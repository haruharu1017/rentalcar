# QT       += core gui
QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    car.cpp \
    carmanager.cpp \
    detailwindow.cpp \
    main.cpp \
    carwindow.cpp \
    mainwindow.cpp \
    renter.cpp

HEADERS += \
    car.h \
    carmanager.h \
    carwindow.h \
    detailwindow.h \
    mainwindow.h \
    renter.h

FORMS += \
    carwindow.ui \
    detailwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    cars.txt
