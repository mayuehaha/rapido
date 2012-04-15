#ifndef GLOBAL_H
#define GLOBAL_H

#include "env.h"
#include "ipmsg_thread.h"
//class IpMsgThread;

bool rapido_intialize(void);

// global finalize, should be call only once at main() when program exit.
void rapido_finalize(void);

Env& rapido_env(void);
IpMsgThread& rapido_ipmsg_thread(void);


class ChatWindowManager;

namespace rapido
{
	extern ChatWindowManager* pChatWindowManager;

}


#endif // GLOBAL_H
