#include "global.h"
#include "ipmsg_const.h"
#include "ipmsg_packet.h"


IpMsgPacket::IpMsgPacket(){}

IpMsgPacket::IpMsgPacket(QHostAddress address, quint16 port)
{
    this->ipAddress = address;
    this->port = port;
}


IpMsgSendPacket::IpMsgSendPacket(){}

IpMsgSendPacket::IpMsgSendPacket(QHostAddress address, quint16 port, QString additionalInfo,
                             QString extendedInfo, quint32 flags):IpMsgPacket(address, port)
{
    this->additionalInfo = additionalInfo;
    this->extendedInfo = extendedInfo;
    this->flags = flags;
	qint64 random = qrand() % 1024;
    this->packetNoString = QString("%1").arg(random);

	constructPacket();
}

void IpMsgSendPacket::constructPacket()
{
    this->packet.append(QString("%1%2").arg(IPMSG_VERSION).arg(R_COMMAND_SEPERATOR));

    this->packet.append(QString("%1%2").arg(this->packetNoString)
					.arg(R_COMMAND_SEPERATOR));

    this->packet.append(rapido::myself.getLoginName().toAscii());
    this->packet.append(R_COMMAND_SEPERATOR);
    this->packet.append(rapido::myself.getHost().toAscii());
    this->packet.append(R_COMMAND_SEPERATOR);
    this->packet.append(QString("%1%2").arg(this->flags).arg(R_COMMAND_SEPERATOR));
    this->packet.append(this->additionalInfo);
}

void IpMsgSendPacket::send()
{
    rapido::sendPacketList.append(this);
}

IpMsgSendPacket::~IpMsgSendPacket()
{
}


IpMsgRecvPacket::IpMsgRecvPacket(){}

IpMsgRecvPacket::IpMsgRecvPacket(QHostAddress senderIp, quint16 senderPort, QString packet)
	: IpMsgPacket(senderIp, senderPort)
{
	QStringList list = packet.split(R_COMMAND_SEPERATOR);

	// sanity check
	if (list.count() < R_IPMSG_NORMAL_FIELD_COUNT) {
		return;
	}

    this->packet = packet;
    this->extendedInfo = packet.section(QChar(R_EXTEND_INFO_SEPERATOR), 1, 1);

	//remember to add the situation of haven't the field
	this->additionalInfo = list.at(R_IPMSG_ADDITION_INFO_POS);

    this->packetNoString = list.at(R_IPMSG_PACKET_NO_POS);
    this->flags = list.at(R_IPMSG_FLAGS_POS).toUInt();

    this->packetUser.setName(this->additionalInfo);
    this->packetUser.setGroup(this->extendedInfo);
    this->packetUser.setHost(list.at(R_IPMSG_HOST_POS));
    this->packetUser.setIp(senderIp);
    this->packetUser.setLoginName(list.at(R_IPMSG_LOG_NAME_POS));
    this->packetUser.setMac("aa:aa:aa:aa:aa:aa");
}

IpMsgRecvPacket::~IpMsgRecvPacket()
{
}

