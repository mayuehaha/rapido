#include "global.h"
#include "ipmsg_thread.h"

#include "chatwindow_manager.h"

IpMsgUser rapido::myself;
ChatWindowManager* rapido::pChatWindowManager = NULL;
QList<IpMsgUser> rapido::userList1;
QList<IpMsgSendPacket> rapido::sendPacketList;

bool rapido_intialize(void)
{

	//rapido::myself = new IpMsgUser();

	if(!rapido_env().Initialize())
		return false;

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
	//QByteArray tmp(cmdList.at(5).toAscii());
	return codec->toUnicode(qarray);
}

