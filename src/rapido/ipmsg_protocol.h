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
<<<<<<< HEAD

	QUdpSocket m_socket;
	IpMsgDB m_db;
    qint32 m_packetNo;
	void broadcastLogin();

	// broadcast a message that I'm online now.
	void _broadcastOnlineMessage();
=======
	/// 广播一个上线消息
	void _BroadcastOnlineMessage();
>>>>>>> 229d281586472bab07b0d529e012c0eafdf7c10d
	// broadcast message (the target ip in send_packet will be ignored.)
	void _BroadcastMessage(const IpMsgSendPacket* send_packet);
	// send message
	void _SendPacket(const IpMsgSendPacket* send_packet);

<<<<<<< HEAD
	void _handleMsg(const IpMsgSendPacket* send_packet);
=======
	//void handleMsg(const IpMsgSendPacket* send_packet);
>>>>>>> 229d281586472bab07b0d529e012c0eafdf7c10d

	void _ProcessRecvMessage(const IpMsgRecvPacket* recvPacket);

signals:
	void _onReceiveMessage(IpMsgRecvPacket* packet);
	void _onUserOnline(const QString& strUserName, const QString& strIp);
	void _onUserOffline(const QString& strIp);

<<<<<<< HEAD
public slots:
    void readPendingDatagrams();
	void processSendMsg();	// this slot will be connect with a timer.

protected:
	QMutex m_SendPacketLocker;
=======
private slots:
	/// 当绑定的UDP端口上有数据可读时被调用
	void _ReadPendingDatagrams();
	/// 绑定到一个定时器上以定时执行发送消息包操作
	void _ProcessSendMessage();

public slots:

protected:
	QUdpSocket m_socket;
	IpMsgDB m_db;
	qint32 m_packetNo;

	QMutex m_SendPacketLock;
>>>>>>> 229d281586472bab07b0d529e012c0eafdf7c10d
	QList<IpMsgSendPacket*> m_SendPackets;
};


#endif // IPMSGPROTOCOL_H
