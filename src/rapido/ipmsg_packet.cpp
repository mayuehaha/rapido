#include "ipmsg_packet.h"

IpMsgPacket::IpMsgPacket()
{
}

IpMsgPacket::IpMsgPacket(QHostAddress senderIp, quint16 senderPort, const QByteArray& datagram)
{
	m_ipAddress = senderIp;
	m_port = senderPort;
	//m_strContent = strContent;

}
//QString ip(void)  { return m_ipAddress.toString(); }
// ===============================================================

IpMsgSendPacket::IpMsgSendPacket()
{

}
IpMsgSendPacket::IpMsgSendPacket(QHostAddress address, quint16 port, QString additionalInfo,
	QString extendedInfo, quint32 flags)//: m_ipAddress(address), m_port(port), m_additionalInfo(additionalInfo)//,
	//m_extendedInfo(extendedInfo), m_flags(flags)
{
	m_packetNoString = "9527";
	//IpMsgUser = ;

	//constructPacket();
}

void IpMsgSendPacket::constructPacket()
{
//	m_packet.append(QString("%1%2").arg(IPMSG_VERSION).arg(COMMAND_SEPERATOR));

//	m_packet.append(QString("%1%2").arg(m_packetNoString)
//					.arg(COMMAND_SEPERATOR));

//	m_packet.append(IpMsgUser.loginName());
//	m_packet.append(COMMAND_SEPERATOR);
//	m_packet.append(IpMsgUser.host());
//	m_packet.append(COMMAND_SEPERATOR);
//	m_packet.append(QString("%1%2").arg(m_flags).arg(COMMAND_SEPERATOR));
//	m_packet.append(m_additionalInfo);
}

IpMsgSendPacket::~IpMsgSendPacket()
{
}

// ===============================================================

IpMsgRecvPacket::IpMsgRecvPacket()
{
}

IpMsgRecvPacket::IpMsgRecvPacket(QHostAddress senderIp, quint16 senderPort, const QByteArray& datagram)
	: IpMsgPacket(senderIp, senderPort, datagram)
{

}

IpMsgRecvPacket::~IpMsgRecvPacket()
{
}

