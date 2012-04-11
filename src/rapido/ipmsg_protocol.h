#ifndef IPMSGPROTOCOL_H
#define IPMSGPROTOCOL_H

#include "ipmsg_const.h"
#include "ipmsg_db.h"

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

signals:
	void newMsg(void);
    
private slots:
    void readPendingDatagrams();
};

#endif // IPMSGPROTOCOL_H
