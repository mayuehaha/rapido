#include "mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QWebView(parent)
{
	//m_pTrayIcon = NULL;
	//m_pTrayMenu = NULL;

    QString strExecPath = QApplication::applicationDirPath();
    QString strUrl = "file:///";
    strUrl += strExecPath;
#if defined(Q_OS_MAC)
	strUrl += "/../../../skin/index.html";
#else
	strUrl += "/../skin/index.html";
#endif
	QUrl startURL = QUrl(strUrl);

    // Load web content now!
    setUrl(startURL);

    // Start the IpMsg-Protocol thread for register myself and receive messages.
    //m_pIpMsgThread = new IpMsgProtocol;
    //m_pIpMsgThread->start();
}

//MainWindow::~MainWindow()
//{
//	if(NULL != m_pTrayIcon)
//	{
//		m_pTrayIcon->hide();
//		delete m_pTrayIcon;
//	}

//	if(NULL != m_pTrayMenu)
//	{
//		delete m_pTrayMenu;
//	}

//	if(NULL != m_pQuitAction)
//		delete m_pQuitAction;
//}

void MainWindow::InitTrayIcon()
{
	if(!QSystemTrayIcon::isSystemTrayAvailable())
		return;
	m_pTrayIcon = new QSystemTrayIcon(this);

	connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(_onTrayIconEvent(QSystemTrayIcon::ActivationReason)));

	m_pTrayMenu = new QMenu(this);
	m_pQuitAction = new QAction(QObject::tr("E&xit"), this);
	connect(m_pQuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	m_pTrayMenu->addAction(m_pQuitAction);

	m_pTrayIcon->setContextMenu(m_pTrayMenu);

	m_pTrayIcon->setIcon(QIcon(":images/rapido.png"));
	m_pTrayIcon->setToolTip(QObject::tr("Rapido - MyIM"));

	// set flag, program will not exit when click the close button.
	QApplication::setQuitOnLastWindowClosed(false);
}

void MainWindow::ShowTrayIcon()
{
	if(NULL == m_pTrayIcon)
		return;
	m_pTrayIcon->show();
	m_pTrayIcon->showMessage("RapidoMessenger", "Hello world...", QSystemTrayIcon::Information, 10000);
}

void MainWindow::_onTrayIconEvent(QSystemTrayIcon::ActivationReason reason)
{
	switch(reason)
	{
	case QSystemTrayIcon::Trigger:			// click
	case QSystemTrayIcon::DoubleClick:		// double-click
		showNormal();
		//show();
		//setWindowState(Qt::WindowNoState);
		break;
	}
}
