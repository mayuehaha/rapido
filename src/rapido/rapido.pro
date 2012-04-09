TRANSLATIONS = resources/i18n/rapido_zh_CN.ts

QT += network webkit

win32:CONFIG += console

HEADERS += \
    mainwindow.h \
    ipmsgprotocol.h \
    ipmsg_const.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    ipmsgprotocol.cpp

RESOURCES += \
    resources/rapido.qrc

RC_FILE = resources/rapido.rc
