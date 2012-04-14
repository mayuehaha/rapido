#include "mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QWebView(parent)
{
	m_pTrayIcon = NULL;

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

void MainWindow::InitTrayIcon()
{
	if(!QSystemTrayIcon::isSystemTrayAvailable())
		return;
	m_pTrayIcon = new QSystemTrayIcon(this);

	m_pTrayIcon->setIcon(QIcon(":images/rapido.png"));
	m_pTrayIcon->setToolTip(QObject::tr("Rapido - MyIM"));
}

void MainWindow::ShowTrayIcon()
{
	if(NULL == m_pTrayIcon)
		return;
	m_pTrayIcon->show();
	m_pTrayIcon->showMessage("RapidoMessenger", "Hello world...", QSystemTrayIcon::Information, 10000);
}
