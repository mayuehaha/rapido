#include "global.h"
#include "ipmsg_const.h"
#include "ipmsg_packet.h"


IpMsgPacket::IpMsgPacket(){}

IpMsgPacket::IpMsgPacket(QHostAddress address, quint16 port, const QString additionalInfo)
{
	m_ipAddress = address;
	m_port = port;
	m_additionalInfo = additionalInfo;
}


IpMsgSendPacket::IpMsgSendPacket(){}

IpMsgSendPacket::IpMsgSendPacket(QHostAddress address, quint16 port, QString additionalInfo,
		QString extendedInfo, quint32 flags):IpMsgPacket(address, port, additionalInfo)
{
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

    m_packet.append(rapido_env().m_strLoginName.toAscii());
	m_packet.append(R_COMMAND_SEPERATOR);
    m_packet.append(rapido_env().m_strHostName.toAscii());
	m_packet.append(R_COMMAND_SEPERATOR);
	m_packet.append(QString("%1%2").arg(m_flags).arg(R_COMMAND_SEPERATOR));
	m_packet.append(m_additionalInfo);
}

IpMsgSendPacket::~IpMsgSendPacket()
{
}


IpMsgRecvPacket::IpMsgRecvPacket(){}

IpMsgRecvPacket::IpMsgRecvPacket(QHostAddress senderIp, quint16 senderPort, QString packet)
	: IpMsgPacket(senderIp, senderPort, packet)
{

	QStringList list = packet.split(R_COMMAND_SEPERATOR);

	// sanity check
	if (list.count() < R_IPMSG_NORMAL_FIELD_COUNT) {
		return;
	}

	m_extendedInfo = m_packet.section(QChar(R_IPMSG_EXTENDED_INFO_POS), 1, 1);
	parseAdditionalInfo();

	m_packetNoString = list.at(MSG_PACKET_NO_POS);
	m_flags = list.at(MSG_FLAGS_POS).toUInt();
}

IpMsgRecvPacket::~IpMsgRecvPacket()
{
}

