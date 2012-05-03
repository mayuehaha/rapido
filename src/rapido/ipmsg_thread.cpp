#include "ipmsg_thread.h"
#include "global.h"
#include "ipmsg_const.h"

#include "ipmsg_protocol.h"
#include "mainwindow.h"
#include "chatwindow_manager.h"


IpMsgThread::IpMsgThread(QObject *parent) :
	QThread(parent)
{
	m_pIpMsg = NULL;
	m_pMainWindow = NULL;
}

IpMsgThread::~IpMsgThread()
{
	//exit(0);
	//wait();
	stop_and_finalize();
}

void IpMsgThread::setOwnerWindow(MainWindow* pMainWindow)
{
	m_pMainWindow = pMainWindow;
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
	QTimer timer;
	timer.start(R_SEND_MSG_PROCESS_INTERVAL);

	m_pIpMsg = new IpMsgProtocol;

	connect(&timer, SIGNAL(timeout()), m_pIpMsg, SLOT(processSendMsg()));

	connect(m_pIpMsg, SIGNAL(newMsg(IpMsgRecvPacket*)), rapido::pChatWindowManager, SLOT(newMsg(IpMsgRecvPacket*)));
	connect(m_pIpMsg, SIGNAL(onUserOnline(QString,QString)), m_pMainWindow, SLOT(onUserOnline(QString,QString)));
	connect(m_pIpMsg, SIGNAL(onUserOffline(QString)), m_pMainWindow, SLOT(onUserOffline(QString)));

	m_pIpMsg->start();

	exec();

	// While when delete the IpMsgProtocol instance, it will send a socket event to the internal UDP socket
	// so we must do this inside the thread. Otherwise we will got an exception.
	delete m_pIpMsg;
	m_pIpMsg = NULL;
}

void IpMsgThread::AddForSend(IpMsgSendPacket *pPacket)
{
	// TODO: lock the list first.
	//rapido::sendPacketList.append(send_packet);
	if(NULL == m_pIpMsg)
		return;
	m_pIpMsg->AddForSend(pPacket);
}
