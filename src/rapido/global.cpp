#include "global.h"
#include "ipmsg_thread.h"

#include "chatwindow_manager.h"

IpMsgUser rapido::myself;
ChatWindowManager* rapido::pChatWindowManager = NULL;
QList<IpMsgUser> rapido::userList;
QList<IpMsgSendPacket*> rapido::sendPacketList;
QString rapido::entryMessage;

bool rapido_intialize(void)
{

	//rapido::myself = new IpMsgUser();

	if(!rapido_env().Initialize())
		return false;

    rapido::entryMessage = QString("%1%2%3%4").arg(rapido::myself.getName())
            .arg(QChar(R_EXTEND_INFO_SEPERATOR))
            .arg(rapido::myself.getGroup())
            .arg(QChar(R_EXTEND_INFO_SEPERATOR));

	rapido::pChatWindowManager = new ChatWindowManager;

	return true;
}

void rapido_finalize(void)
{
//    if(NULL != g_ipmsg_thread)
//    {
//        delete g_ipmsg_thread;
//        g_ipmsg_thread = NULL;
//    }

	rapido_ipmsg_thread().stop_and_finalize();

	if(NULL != rapido::pChatWindowManager)
		delete rapido::pChatWindowManager;
}

Env& rapido_env(void)
{
	static Env env;
	return env;
}

IpMsgThread& rapido_ipmsg_thread(void)
{
//    if(NULL == g_ipmsg_thread)
//    {
//        g_ipmsg_thread = new IpMsgThread;
//    }
//    return g_ipmsg_thread;
    static IpMsgThread ipmsgthread;
    return ipmsgthread;
}

QString toUnicode(QByteArray qarray)
{
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	return codec->toUnicode(qarray);
}

