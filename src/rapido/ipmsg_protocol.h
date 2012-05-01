#ifndef IPMSGPROTOCOL_H
#define IPMSGPROTOCOL_H

#include "ipmsg_db.h"

#include <QObject>
#include <QUdpSocket>

class IpMsgSendPacket;
class IpMsgRecvPacket;

class IpMsgProtocol : public QObject
{
    Q_OBJECT
public:
    explicit IpMsgProtocol(QObject *parent = 0);
    
    void start();

protected:
    QUdpSocket m_socket;
	IpMsgDB m_db;
    qint32 m_packetNo;
	void broadcastLogin();
	void handleMsg(const IpMsgSendPacket* send_packet);
	void processRecvMsg(const IpMsgRecvPacket* recvPacket);
signals:
	void newMsg(IpMsgRecvPacket* packet);
	void onUserOnline(const QString& strUserName, const QString& strIp);
	void onUserOffline(const QString& strIp);

private slots:
    void readPendingDatagrams();

public slots:
	void processSendMsg();	// this slot will be connect with a timer.
};

#endif // IPMSGPROTOCOL_H
