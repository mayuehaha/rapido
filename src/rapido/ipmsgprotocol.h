#ifndef IPMSGPROTOCOL_H
#define IPMSGPROTOCOL_H

#include <QThread>
#include <QUdpSocket>

class IpMsgProtocol : public QThread
{
    Q_OBJECT
public:
    explicit IpMsgProtocol();
    
protected:
    void run();

protected:
    QUdpSocket* m_pSocket;

signals:
    
private slots:
    void readPendingDatagrams();
};

#endif // IPMSGPROTOCOL_H
