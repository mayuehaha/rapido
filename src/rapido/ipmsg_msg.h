#ifndef IPMSG_MSG_H
#define IPMSG_MSG_H

#include <QHostAddress>

#include "ipmsg_user.h"

class ipmsg_msg
{
public:
	enum States {
	    NotSend = 0, Sending = 1, SendOk = 2, SendFail = 3, SendAckOk = 4
	};

	ipmsg_msg();
private:

	IpMsgUser r_ipMsgUser;
	QString r_packet;
	QString r_extendedInfo;
	QString r_additionalInfo;
	QString r_packetNoString;
	quint32 r_flags;
	QHostAddress r_ipAddress;
	quint16 r_port;
};

#endif // IPMSG_MSG_H
