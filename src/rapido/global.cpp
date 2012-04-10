#include "global.h"
#include "ipmsg_thread.h"

bool rapido_intialize(void)
{
	if(!rapido_env().Initialize())
		return false;
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


