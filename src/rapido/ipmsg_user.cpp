
#include <QStringList>

#include "ipmsg_user.h"
#include "ipmsg_const.h"

IpMsgUser::IpMsgUser()
{
}

IpMsgUser::IpMsgUser(QString packet, QHostAddress address, quint16 port)
	: myIpAddress(address), myPort(port)
{
	initIpMsgUser(packet);
}



void IpMsgUser::initIpMsgUser(QString &packet)
{
	QStringList list = packet.split(R_IPMSG_COMMAND_SEPERATOR);

	if (list.size() < R_IPMSG_NORMAL_FIELD_COUNT) {
		return;
	}

	myLoginName = list.at(R_IPMSG_LOG_NAME_POS);

	quint32 flag = list.at(R_IPMSG_FLAGS_POS).toUInt();
	if (flag & IPMSG_BR_ENTRY || flag & IPMSG_BR_ABSENCE) {
		myGroup = packet.section(QChar(R_EXTEND_INFO_SEPERATOR), 1, 1);
		myName = parseAdditionalInfo(packet);
		if (myName.isEmpty()) {
			myName = myLoginName;
		}
	}

	// No sender name in this situation, so we set sender name to
	// sender's login name.
	if (flag & IPMSG_SENDMSG) {
		myName = myLoginName;
	}

	myHost = list.at(R_IPMSG_HOST_POS);
}

QString IpMsgUser::parseAdditionalInfo(QString &packet)
{
	int cnt = 0;
	int index = 0;
	while (cnt < R_IPMSG_ADDITION_INFO_POS) {
		int id = packet.indexOf(QChar(R_COMMAND_SEPERATOR), index);
		if (index == -1) {
			break;
		}
		++cnt;
		index = id + 1;
	}

	QString s = packet.right(packet.size() - index);

	return s.section(QChar(R_EXTEND_INFO_SEPERATOR), 0, 0);
}


IpMsgUser::~IpMsgUser()
{

}
