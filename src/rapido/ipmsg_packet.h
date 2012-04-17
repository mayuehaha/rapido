#ifndef IPMSG_PACKET_H
#define IPMSG_PACKET_H

#include <QHostAddress>

#include "ipmsg_user.h"

// TODO: message packet should have a refrence count.

class IpMsgPacket
{
public:
    IpMsgPacket();

    // create from received packet.
	IpMsgPacket(QHostAddress senderIp, quint16 senderPort, const QString additionalInfo);

    virtual ~IpMsgPacket(){}


	virtual QString ip(void) const { return m_ipAddress.toString(); }
	virtual QHostAddress ipAddress(void) const { return m_ipAddress; }
	virtual quint16 port(void) const { return m_port; }


public:
    QHostAddress m_ipAddress;
	quint16 m_port;
	QString m_strContent;

	IpMsgUser m_ipMsgUser;
	QString m_packet;
	QString m_extendedInfo;
	QString m_additionalInfo;
	QString m_packetNoString;
	quint32 m_flags;
};

class IpMsgSendPacket : public IpMsgPacket
{
public:
    IpMsgSendPacket();
	void constructPacket();
	IpMsgSendPacket(QHostAddress address, quint16 port, QString additionalInfo,
		QString extendedInfo, quint32 flags);
	//IpMsgSendPacket():MsgBase(packet, address, port)
    ~IpMsgSendPacket();
};

class IpMsgRecvPacket : public IpMsgPacket
{
public:
    IpMsgRecvPacket();
	IpMsgRecvPacket(QHostAddress senderIp, quint16 senderPort, const QByteArray& datagram);
	~IpMsgRecvPacket();
};

#endif // IPMSG_PACKET_H
