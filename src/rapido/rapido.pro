TRANSLATIONS = resources/i18n/rapido_zh_CN.ts

QT += network webkit

win32:CONFIG += console

HEADERS += \
    mainwindow.h \
    ipmsg_const.h \
    global.h \
    ipmsg_thread.h \
    ipmsg_protocol.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    global.cpp \
    ipmsg_thread.cpp \
    ipmsg_protocol.cpp

RESOURCES += \
    resources/rapido.qrc

RC_FILE = resources/rapido.rc
