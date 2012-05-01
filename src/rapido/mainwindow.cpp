#include "mainwindow.h"
#include "global.h"

#include <QtGui>
#include <QWebFrame>
#include <QWebElementCollection>

MainWindow::MainWindow(QWidget *parent) :
    QWebView(parent)
{
	//m_pTrayIcon = NULL;
	//m_pTrayMenu = NULL;

	QString strUrl = rapido_env().m_strHtmlBasePath;
	strUrl += "login.html";
	QUrl startURL = QUrl(strUrl);

	// Signal is emitted before frame loads any web content:
	QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_onAddJSObject()));


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

	m_pTrayIcon->setIcon(QIcon(":images/tray_icon.png"));
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

void MainWindow::login(const QString& strUserId, const QString& strPasswd)
{
    qDebug() << strUserId << strPasswd;

	QString strUrl = rapido_env().m_strHtmlBasePath;
	strUrl += "index.html";
	QUrl startURL = QUrl(strUrl);
	//setUrl(startURL);
	page()->mainFrame()->load(startURL);


	//emit onLoginFailed("Oh, failed. [core]");
}

void MainWindow::startIpMsgThread(void)
{
    //qDebug() << "startIpMsg().";
	rapido_ipmsg_thread().setOwnerWindow(this);
	rapido_ipmsg_thread().start();
}
void MainWindow::onUserOnline(const QString& strUserName, const QString& strIp)
{
	// let UserManager class handle this information: add the user into a list.

	// finally, update the UI.
	emit jsOnUserOnline(strUserName, strIp);
}

void MainWindow::onUserOffline(const QString& strIp)
{
	emit jsOnUserOffline(strIp);
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
		default:
			break; 
	}
}

void MainWindow::_onAddJSObject()
{
	// TODO: maybe I should put the UserManager instance into page for the javascript call?

	page()->mainFrame()->addToJavaScriptWindowObject(QString("rCore"), this);
}
