#include "global.h"
#include "ipmsg_thread.h"

//IpMsgThread* g_ipmsg_thread = NULL;

IpMsgThread& rapido_get_ipmsg_thread(void)
{
//    if(NULL == g_ipmsg_thread)
//    {
//        g_ipmsg_thread = new IpMsgThread;
//    }
//    return g_ipmsg_thread;
    static IpMsgThread ipmsgthread;
    return ipmsgthread;
}



void rapido_finalize(void)
{
//    if(NULL != g_ipmsg_thread)
//    {
//        delete g_ipmsg_thread;
//        g_ipmsg_thread = NULL;
//    }

    rapido_get_ipmsg_thread().stop_and_finalize();

}
