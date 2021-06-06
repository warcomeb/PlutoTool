QT       += core gui
INCLUDEPATH += ../plutotool-cli

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addtransaction.cpp \
    main.cpp \
    ../plutotool-cli/account.cpp \
    ../plutotool-cli/accounttype.cpp \
    ../plutotool-cli/category.cpp \
    ../plutotool-cli/database.cpp \
    ../plutotool-cli/movement.cpp \
    ../plutotool-cli/payee.cpp \
    ../plutotool-cli/payeetype.cpp \
    ../plutotool-cli/scheduled.cpp \
    ../plutotool-cli/transaction.cpp \
    ../plutotool-cli/plutotoolreport.cpp \
    ../plutotool-cli/plutodefault.cpp \
    ../plutotool-cli/user.cpp \
    ../plutotool-cli/workorder.cpp \
    mainwindow.cpp

HEADERS += \
    addtransaction.h \
    mainwindow.h \
    ../plutotool-cli/account.h \
    ../plutotool-cli/accounttype.h \
    ../plutotool-cli/category.h \
    ../plutotool-cli/database.h \
    ../plutotool-cli/movement.h \
    ../plutotool-cli/payee.h \
    ../plutotool-cli/payeetype.h \
    ../plutotool-cli/scheduled.h \
    ../plutotool-cli/transaction.h \
    ../plutotool-cli/plutotoolreport.h \
    ../plutotool-cli/plutodefault.h \
    ../plutotool-cli/user.h \
    ../plutotool-cli/workorder.h

FORMS += \
    addtransaction.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    project.qrc
