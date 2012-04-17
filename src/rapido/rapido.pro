TRANSLATIONS = resources/i18n/rapido_zh_CN.ts

QT += network webkit sql

#win32:CONFIG += console

HEADERS += \
    mainwindow.h \
    ipmsg_const.h \
    global.h \
    ipmsg_thread.h \
    ipmsg_protocol.h \
    ipmsg_db.h \
    env.h \
    user_manager.h \
    ipmsg_user.h \
    chatwindow.h \
    chatwindow_manager.h \
    ipmsg_packet.h \
    ipmsg_msg.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    global.cpp \
    ipmsg_thread.cpp \
    ipmsg_protocol.cpp \
    ipmsg_db.cpp \
    env.cpp \
    user_manager.cpp \
    ipmsg_user.cpp \
    chatwindow.cpp \
    chatwindow_manager.cpp \
    ipmsg_packet.cpp \
    ipmsg_msg.cpp

RESOURCES += \
    resources/rapido.qrc

RC_FILE = resources/rapido.rc

#DEFINES += QT_NO_DEBUG_OUTPUT












