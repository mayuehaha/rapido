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
    IpMsgPacket(QHostAddress senderIp, quint16 senderPort);

    virtual ~IpMsgPacket(){}

    //Is activity of virtual the same as java(live the vitual method implement by sun class)?
    virtual QString getIp(void) const { return ipAddress.toString(); }
    virtual QHostAddress getIpAddress(void) const { return ipAddress; }

    virtual quint16 getPort(void) const { return port; }

    void setPacketUser(IpMsgUser packet_user) { packetUser = packet_user; }
    IpMsgUser getPacketUser() const { return packetUser; }

    void setPacket(QString packet) { this->packet = packet; }
    QString getPacket() const { return this->packet; }

    void setExtendedInfo(QString extended_info) { extendedInfo = extended_info; }
    QString getExtendedInfo() const { return extendedInfo; }

    void setAdditionalInfo(QString additional_info) { additionalInfo = additional_info; }
    QString getAdditionalInfo() const { return additionalInfo; }

    void setPacketNoString(QString packetNo_string) { packetNoString = packetNo_string; }
    QString getPacketNoString() const { return packetNoString; }

    void setFlags(quint32 flag) { flags = flag; }
    quint32 getFlags() const { return flags; }

protected:
    QHostAddress ipAddress;
    quint16 port;

    IpMsgUser packetUser;
    QString packet;
	//group name
    QString extendedInfo;
	//ipmsg_name
    QString additionalInfo;
    QString packetNoString;
    quint32 flags;
};

class IpMsgSendPacket : public IpMsgPacket
{
public:
    IpMsgSendPacket();
	IpMsgSendPacket(QHostAddress address, quint16 port, QString additionalInfo,
		QString extendedInfo, quint32 flags);
    void send();
    ~IpMsgSendPacket();
private:
    void constructPacket();
};

class IpMsgRecvPacket : public IpMsgPacket
{
public:
    IpMsgRecvPacket();
	IpMsgRecvPacket(QHostAddress senderIp, quint16 senderPort, QString datagram);
	~IpMsgRecvPacket();
};

#endif // IPMSG_PACKET_H
