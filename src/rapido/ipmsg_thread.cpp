#include "ipmsg_thread.h"
#include "ipmsg_protocol.h"

IpMsgThread::IpMsgThread(QObject *parent) :
    QThread(parent)
{
    m_pIpMsg = NULL;
}

IpMsgThread::~IpMsgThread()
{
    //exit(0);
    //wait();
    stop_and_finalize();
}

void IpMsgThread::stop_and_finalize(void)
{
    exit(0);
    wait();
    delete m_pIpMsg;
    m_pIpMsg = NULL;
}

void IpMsgThread::run(void)
{
    m_pIpMsg = new IpMsgProtocol;
    m_pIpMsg->start();
    exec();
}
