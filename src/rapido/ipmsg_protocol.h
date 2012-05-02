#ifndef IPMSGPROTOCOL_H
#define IPMSGPROTOCOL_H

#include "ipmsg_db.h"

#include <QObject>
#include <QUdpSocket>
#include <QMutex>

class IpMsgSendPacket;
class IpMsgRecvPacket;

class IpMsgProtocol : public QObject
{
    Q_OBJECT
public:
    explicit IpMsgProtocol(QObject *parent = 0);
    
    void start();

	void AddForSend(IpMsgSendPacket* pPacket);

protected:
	// broadcast a message that I'm online now.
	void _broadcastOnlineMessage();
	// broadcast message (the target ip in send_packet will be ignored.)
	void _broadcastMessage(const IpMsgSendPacket* send_packet);
	// send message
	void _sendMessage(const IpMsgSendPacket* send_packet);

	void handleMsg(const IpMsgSendPacket* send_packet);

	void _processRecvMessage(const IpMsgRecvPacket* recvPacket);

signals:
	void newMsg(IpMsgRecvPacket* packet);
	void onUserOnline(const QString& strUserName, const QString& strIp);
	void onUserOffline(const QString& strIp);

private slots:
    void readPendingDatagrams();

public slots:
	void processSendMsg();	// this slot will be connect with a timer.

protected:
	QUdpSocket m_socket;
	IpMsgDB m_db;
	qint32 m_packetNo;

	QMutex m_SendPacketLocker;
	QList<IpMsgSendPacket*> m_SendPackets;
};


#endif // IPMSGPROTOCOL_H
