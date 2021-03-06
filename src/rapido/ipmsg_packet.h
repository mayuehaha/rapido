﻿/**
@file ipmsg_packet.h
@brief 对 IpMsg 格式的消息报文的封装类
*/

#ifndef IPMSG_PACKET_H
#define IPMSG_PACKET_H

#include <QHostAddress>
#include <QMutex>
#include <QTime>

#include "ipmsg_user.h"

// TODO: message packet should have a refrence count.

/// @brief IpMsg消息包处理的基类
///
/// 这是一个纯粹的数据处理的类，不涉及数据的接收与发送，只是管理消息包的数据的解析与合成等操作。
class IpMsgPacket
{
public:
    IpMsgPacket();
    // create from received packet.
    IpMsgPacket(QHostAddress senderIp, quint16 senderPort);
protected:
	/// 将析构函数作为保护成员函数，这样强制调用者只能使用new操作符来创建一个实例。
	virtual ~IpMsgPacket();

public:
	/// 没有缺省构造函数，所以要创建一个数据包实例，必须给出一些必须的数据。
	IpMsgPacket(QHostAddress ip);

	virtual qint32 AddRef();
	virtual qint32 Release();

	quint32 getCommand(void){return m_command;}

	// Is activity of virtual the same as java(live the vitual method implement by sun class)?
	virtual QString getIp(void) const { return m_ip.toString(); }
	virtual QHostAddress getIpAddress(void) const { return m_ip; }

	//virtual quint16 getPort(void) const { return m_port; }

//	void setPacketUser(IpMsgUser packet_user) { packetUser = packet_user; }
//	IpMsgUser getPacketUser() const { return packetUser; }

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
	//quint16 m_port;		// for send-packet, this is target port, for received-packet, this is sender's port.

	quint32 m_command;		///< 命令（与选项合成完整指令）
	quint32 m_options;		///< 选项（与命令合成完整指令）

	//IpMsgUser packetUser;
	QString m_packet;
	//group name
	QString extendedInfo;
	//ipmsg_name
	QString additionalInfo;
	QString packetNoString;
	quint32 m_flags;
};

/// @brief 用于构造要发送的消息包的类
///
/// 使用本类来构造要发送的消息包
class IpMsgSendPacket : public IpMsgPacket
{
protected:
	~IpMsgSendPacket();

public:
    IpMsgSendPacket();
	IpMsgSendPacket(QHostAddress address, quint16 port, QString additionalInfo,
		QString extendedInfo, quint32 flags);

	IpMsgSendPacket(QHostAddress ip, QString additionalInfo, QString extendedInfo, quint32 flags);

	/// 构造一个简单的纯命令消息包，例如广播上线、下线等。
	IpMsgSendPacket(QHostAddress ip, quint32 command, quint32 options = 0);

	//void send();
	/// 更新发送状态，每次发送后调用
	void UpdateSendFlag(void);
	/// 此消息包是否发送失败了（重试多次均无回应）
	bool IsSendFailed(void);
private:
	void _BuildPacket();
protected:
	QTime m_SendingTime;	/// 记录上一次发送消息的时间
	quint32 m_RetryCount;	/// 记录发送的尝试次数（重试三次，每次间隔2秒，如果还失败，说明对方断网了）
};

/// @brief 用于解析接收到的消息包的类
///
/// 每当接收到一个消息包，就产生一个本类的实例，并自动解析出必要的数据，例如命令、消息编号、消息内容、附加数据等等。
class IpMsgRecvPacket : public IpMsgPacket
{
protected:
	~IpMsgRecvPacket();
public:
	//IpMsgRecvPacket();
	IpMsgRecvPacket(QHostAddress ip, const QByteArray& datagram);
protected:
	bool _Parse(void);	///< 解析数据包
};



#endif // IPMSG_PACKET_H
