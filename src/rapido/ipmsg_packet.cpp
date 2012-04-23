#include "global.h"
#include "ipmsg_const.h"
#include "ipmsg_packet.h"


IpMsgPacket::IpMsgPacket(){}

IpMsgPacket::IpMsgPacket(QHostAddress address, quint16 port)
{
	m_ipAddress = address;
	m_port = port;
}


IpMsgSendPacket::IpMsgSendPacket(){}

IpMsgSendPacket::IpMsgSendPacket(QHostAddress address, quint16 port, QString additionalInfo,
        QString extendedInfo, quint32 flags):IpMsgPacket(address, port)
{
    m_additionalInfo = additionalInfo;
	m_extendedInfo = extendedInfo;
	m_flags = flags;
	qint64 random = qrand() % 1024;
	m_packetNoString = QString("%1").arg(random);

	constructPacket();
}

void IpMsgSendPacket::constructPacket()
{
	m_packet.append(QString("%1%2").arg(IPMSG_VERSION).arg(R_COMMAND_SEPERATOR));

	m_packet.append(QString("%1%2").arg(m_packetNoString)
					.arg(R_COMMAND_SEPERATOR));

	m_packet.append(rapido::myself.getLoginName().toAscii());
	m_packet.append(R_COMMAND_SEPERATOR);
	m_packet.append(rapido::myself.getHost().toAscii());
	m_packet.append(R_COMMAND_SEPERATOR);
	m_packet.append(QString("%1%2").arg(m_flags).arg(R_COMMAND_SEPERATOR));
	m_packet.append(m_additionalInfo);
}

IpMsgSendPacket::~IpMsgSendPacket()
{
}


IpMsgRecvPacket::IpMsgRecvPacket(){}

IpMsgRecvPacket::IpMsgRecvPacket(QHostAddress senderIp, quint16 senderPort, QString packet)
	: IpMsgPacket(senderIp, senderPort)
{
	m_packet = packet;
	m_extendedInfo = packet.section(QChar(R_EXTEND_INFO_SEPERATOR), 1, 1);

	QStringList list = packet.split(R_COMMAND_SEPERATOR);

	// sanity check
	if (list.count() < R_IPMSG_NORMAL_FIELD_COUNT) {
		return;
	}

	//remember to add the situation of haven't the field
	m_additionalInfo = toUnicode(list.at(R_IPMSG_ADDITION_INFO_POS).toAscii());

    m_packetNoString = list.at(R_IPMSG_PACKET_NO_POS);
	m_flags = list.at(R_IPMSG_FLAGS_POS).toUInt();

	m_ipMsgUser.setName(m_additionalInfo);
	m_ipMsgUser.setGroup(m_extendedInfo);
	m_ipMsgUser.setHost(list.at(R_IPMSG_HOST_POS));
	m_ipMsgUser.setIp(senderIp);
	m_ipMsgUser.setLoginName(list.at(R_IPMSG_LOG_NAME_POS));
	m_ipMsgUser.setMac("aa:aa:aa:aa:aa:aa");
}

IpMsgRecvPacket::~IpMsgRecvPacket()
{
}

