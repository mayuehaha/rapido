#ifndef IPMSGPROTOCOL_H
#define IPMSGPROTOCOL_H

#include "ipmsg_db.h"

#include <QObject>
#include <QUdpSocket>
#include <QMutex>

class IpMsgThread;
class IpMsgSendPacket;
class IpMsgRecvPacket;

class IpMsgProtocol : public QObject
{
    Q_OBJECT
public:
	friend class IpMsgThread;
    explicit IpMsgProtocol(QObject *parent = 0);
    
    void start();

	/// 将消息包放入列表中等待发送（内部会定时发送消息，并检查消息是否发送成功）
	void SendPacket(IpMsgSendPacket* pPacket);

protected:
	/// 广播一个上线消息
	void _BroadcastOnlineMessage();
	// broadcast message (the target ip in send_packet will be ignored.)
	void _BroadcastMessage(const IpMsgSendPacket* send_packet);
	// send message
	void _SendPacket(const IpMsgSendPacket* send_packet);

	//void handleMsg(const IpMsgSendPacket* send_packet);

	void _ProcessRecvMessage(const IpMsgRecvPacket* recvPacket);

signals:
	void newMsg(IpMsgRecvPacket* packet);
	void onUserOnline(const QString& strUserName, const QString& strIp);
	void onUserOffline(const QString& strIp);

private slots:
    void readPendingDatagrams();
	void processSendMsg();	// this slot will be connect with a timer.

public slots:

protected:
	QUdpSocket m_socket;
	IpMsgDB m_db;
	qint32 m_packetNo;

	QMutex m_SendPacketLock;
	QList<IpMsgSendPacket*> m_SendPackets;
};


#endif // IPMSGPROTOCOL_H
