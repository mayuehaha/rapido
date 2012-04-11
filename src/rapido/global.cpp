#include "global.h"
#include "ipmsg_thread.h"

#include "chatwindow_manager.h"

ChatWindowManager* g_chatWindowManager = NULL;


bool rapido_intialize(void)
{
	if(!rapido_env().Initialize())
		return false;

	g_chatWindowManager = new ChatWindowManager;

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

	if(NULL != g_chatWindowManager)
		delete g_chatWindowManager;
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


