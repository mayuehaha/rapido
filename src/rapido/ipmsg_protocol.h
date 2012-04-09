#ifndef IPMSGPROTOCOL_H
#define IPMSGPROTOCOL_H

#include "ipmsg_const.h"

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

signals:
    
private slots:
    void readPendingDatagrams();
};

#endif // IPMSGPROTOCOL_H
