#ifndef IPMSG_PACKET_H
#define IPMSG_PACKET_H

#include <QHostAddress>

// TODO: message packet should have a refrence count.

class IpMsgPacket
{
public:
    IpMsgPacket();

    // create from received packet.
	IpMsgPacket(QHostAddress senderIp, quint16 senderPort, const QString& strContent);

    virtual ~IpMsgPacket(){}


	virtual QString ip(void) const { return m_ipAddress.toString(); }
    virtual QHostAddress ipAddress(void) const { return m_ipAddress; }
	virtual quint16 port(void) const { return m_port; }


private:
    QHostAddress m_ipAddress;
	quint16 m_port;
	QString m_strContent;
};

class IpMsgSendPacket : public IpMsgPacket
{
public:
    IpMsgSendPacket();
    ~IpMsgSendPacket();
};

class IpMsgRecvPacket : public IpMsgPacket
{
public:
    IpMsgRecvPacket();
    ~IpMsgRecvPacket();
};

#endif // IPMSG_PACKET_H
