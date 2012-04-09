#ifndef IPMSG_THREAD_H
#define IPMSG_THREAD_H

#include <QThread>

class IpMsgProtocol;

class IpMsgThread : public QThread
{
    Q_OBJECT
public:
    friend class IpMsgProtocol;
    explicit IpMsgThread(QObject *parent = 0);
    ~IpMsgThread();

    virtual void run(void);

    void stop_and_finalize();

signals:
    
public slots:
    
private:
    IpMsgProtocol* m_pIpMsg;
};

#endif // IPMSG_THREAD_H
