#ifndef IPMSGPROTOCOL_H
#define IPMSGPROTOCOL_H

#include "ipmsg_const.h"
#include "ipmsg_db.h"
#include "ipmsg_packet.h"

#include <QObject>
#include <QUdpSocket>

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
    void handleMsg(IpMsgSendPacket IpMsgPkt);
signals:
    void newMsg(IpMsgRecvPacket *packet);
    
private slots:
    void readPendingDatagrams();

public slots:
	void processSendMsg();	// this slot will be connect with a timer.
};

#endif // IPMSGPROTOCOL_H
