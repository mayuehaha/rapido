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

// ===============================================================

IpMsgSendPacket::IpMsgSendPacket()
{
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

