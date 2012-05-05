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

	/// 设置一个计时器，定时发送待发送列表中的消息。
	connect(&timer, SIGNAL(timeout()), m_pIpMsg, SLOT(_ProcessSendMessage()));

	connect(m_pIpMsg, SIGNAL(_onReceiveMessage(IpMsgRecvPacket*)), rapido::pChatWindowManager, SLOT(_onReceiveMessage(IpMsgRecvPacket*)));
	connect(m_pIpMsg, SIGNAL(_onUserOnline(QString,QString)), m_pMainWindow, SLOT(onUserOnline(QString,QString)));
	connect(m_pIpMsg, SIGNAL(_onUserOffline(QString)), m_pMainWindow, SLOT(onUserOffline(QString)));

	// TODO: start()内部会绑定UDP端口，这有可能失败，所以start()应该有返回值，需要处理失败的情况。
	m_pIpMsg->start();

	exec();

	// While when delete the IpMsgProtocol instance, it will send a socket event to the internal UDP socket
	// so we must do this inside the thread. Otherwise we will got an exception.
	delete m_pIpMsg;
	m_pIpMsg = NULL;
}

void IpMsgThread::SendPacket(IpMsgSendPacket *pPacket)
{
	if(NULL == m_pIpMsg)
		return;
	m_pIpMsg->SendPacket(pPacket);
}
