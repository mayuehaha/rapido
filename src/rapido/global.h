#ifndef GLOBAL_H
#define GLOBAL_H

#include <QList>

#include "env.h"
#include "ipmsg_thread.h"
#include "ipmsg_user.h"
#include "ipmsg_protocol.h"

//class IpMsgThread;

bool rapido_intialize(void);
// global finalize, should be call only once at main() when program exit.
void rapido_finalize(void);

QString toUnicode(QByteArray str);

Env& rapido_env(void);
IpMsgThread& rapido_ipmsg_thread(void);

class ChatWindowManager;

namespace rapido
{
	extern ChatWindowManager* pChatWindowManager;
	extern IpMsgUser myself;
    extern QList<IpMsgUser> userList;
	extern QList<IpMsgSendPacket> sendPacketList;
    extern QString entryMessage;
}


#endif // GLOBAL_H
