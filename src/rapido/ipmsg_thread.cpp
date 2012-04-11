#include "ipmsg_thread.h"
#include "ipmsg_protocol.h"
#include "chatwindow_manager.h"

#include "global.h"

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
	// Use exit() to exit this thread.
	exit(0);
	// and wait until the thread really exit.
	wait();
}

void IpMsgThread::run(void)
{
	m_pIpMsg = new IpMsgProtocol;

	connect(m_pIpMsg, SIGNAL(newMsg()), g_chatWindowManager, SLOT(newMsg()));



	m_pIpMsg->start();

	exec();

	// While when delete the IpMsgProtocol instance, it will send a socket event to the internal UDP socket
	// so we must do this inside the thread. Otherwise we will got an exception.
	delete m_pIpMsg;
	m_pIpMsg = NULL;
}
