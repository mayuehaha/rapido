TRANSLATIONS = rapido_zh_CN.ts

QT += network webkit

win32:CONFIG += console

HEADERS += \
    mainwindow.h \
    ipmsgprotocol.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    ipmsgprotocol.cpp

RESOURCES += \
    resources/rapido.qrc

RC_FILE = resources/rapido.rc
