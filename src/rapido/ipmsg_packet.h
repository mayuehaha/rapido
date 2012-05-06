/**
@file ipmsg_packet.h
@brief 对 IpMsg 格式的消息报文的封装类
*/

#ifndef IPMSG_PACKET_H
#define IPMSG_PACKET_H

#include <QHostAddress>
#include <QMutex>

#include "ipmsg_user.h"

// TODO: message packet should have a refrence count.

class IpMsgPacket
{
public:
    IpMsgPacket();
    // create from received packet.
    IpMsgPacket(QHostAddress senderIp, quint16 senderPort);
protected:
	virtual ~IpMsgPacket();	// put this into protected area to make sure you must use "new" operator to create an instance.

public:

	void addRef();
	void delRef();

	// Is activity of virtual the same as java(live the vitual method implement by sun class)?
	virtual QString getIp(void) const { return m_ip.toString(); }
	virtual QHostAddress getIpAddress(void) const { return m_ip; }

	virtual quint16 getPort(void) const { return m_port; }

    void setPacketUser(IpMsgUser packet_user) { packetUser = packet_user; }
    IpMsgUser getPacketUser() const { return packetUser; }

	void setPacket(QString packet) { this->m_packet = packet; }
	QString getPacket() const { return this->m_packet; }

    void setExtendedInfo(QString extended_info) { extendedInfo = extended_info; }
    QString getExtendedInfo() const { return extendedInfo; }

    void setAdditionalInfo(QString additional_info) { additionalInfo = additional_info; }
    QString getAdditionalInfo() const { return additionalInfo; }

    void setPacketNoString(QString packetNo_string) { packetNoString = packetNo_string; }
    QString getPacketNoString() const { return packetNoString; }

	void setFlags(quint32 flag) { m_flags = flag; }
	quint32 getFlags() const { return m_flags; }

protected:
	qint32 m_ref;	// refrence of this instance, when it count down to 0, it will delete itself.

	QHostAddress m_ip;	// for send-packet, this is target ip, for received-packet, this is sender's ip.
	quint16 m_port;		// for send-packet, this is target port, for received-packet, this is sender's port.

    IpMsgUser packetUser;
	QString m_packet;
	//group name
    QString extendedInfo;
	//ipmsg_name
    QString additionalInfo;
    QString packetNoString;
	quint32 m_flags;
};

class IpMsgSendPacket : public IpMsgPacket
{
protected:
	~IpMsgSendPacket();

public:
    IpMsgSendPacket();
	IpMsgSendPacket(QHostAddress address, quint16 port, QString additionalInfo,
		QString extendedInfo, quint32 flags);
    void send();

private:
    void constructPacket();
};

class IpMsgRecvPacket : public IpMsgPacket
{
protected:
	~IpMsgRecvPacket();
public:
	//IpMsgRecvPacket();
	IpMsgRecvPacket(QHostAddress ip, quint16 port, QString datagram);
};



#endif // IPMSG_PACKET_H
