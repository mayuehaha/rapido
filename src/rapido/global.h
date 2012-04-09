#ifndef GLOBAL_H
#define GLOBAL_H

#include "ipmsg_thread.h"
//class IpMsgThread;

//IpMsgThread* rapido_get_ipmsg_thread(void);
IpMsgThread& rapido_get_ipmsg_thread(void);

// global finalize, should be call only once at main() when program exit.
void rapido_finalize(void);

#endif // GLOBAL_H
