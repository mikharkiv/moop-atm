QT       += core gui
QT 		 += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    actions/toactions.cpp \
    bank.cpp \
    dbcontroller.cpp \
    localmediator.cpp \
    actions/action.cpp \
    actions/actions.cpp \
    atm.cpp \
    controllers/sessioncontroller.cpp \
    controllers/uicontroller.cpp \
    forms/cardwindow.cpp \
    forms/moneywindow.cpp \
    forms/receiptwindow.cpp \
    main.cpp \
    atmmainwindow.cpp

HEADERS += \
    account.h \
	actions/toactions.h \
    atmmainwindow.h \
    bank.h \
    bankresponse.h \
    dbcontroller.h \
    imediator.h \
	localmediator.h \
    actions/ActionsType.h \
    actions/action.h \
    actions/actions.h \
    atm.h \
    atmmainwindow.h \
    controllers/sessioncontroller.h \
    controllers/uicontroller.h \
    forms/cardwindow.h \
    forms/moneywindow.h \
    forms/receiptwindow.h

FORMS += \
    atmmainwindow.ui \
    forms/cardwindow.ui \
    forms/moneywindow.ui \
    forms/receiptwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
