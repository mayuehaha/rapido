#ifndef IPMSG_THREAD_H
#define IPMSG_THREAD_H

#include <QThread>
#include <QMutex>

class IpMsgProtocol;
class MainWindow;

class IpMsgThread : public QThread
{
    Q_OBJECT
public:
    friend class IpMsgProtocol;
    explicit IpMsgThread(QObject *parent = 0);
    ~IpMsgThread();

    virtual void run(void);

	void setOwnerWindow(MainWindow* pMainWindow);
    void stop_and_finalize();

signals:
    
public slots:
    
private:
	MainWindow* m_pMainWindow;
    QMutex r_lock;
    IpMsgProtocol* m_pIpMsg;
};

#endif // IPMSG_THREAD_H
