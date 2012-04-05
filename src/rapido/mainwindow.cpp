#include "mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QWebView(parent)
{
    QString strExecPath = QApplication::applicationDirPath();
    QString strUrl = "file:///";
    strUrl += strExecPath;
    strUrl += "/../skin/index.html";
    QUrl startURL = QUrl(strUrl);

    // Load web content now!
    setUrl(startURL);

    // Start the IpMsg-Protocol thread for register myself and receive messages.
    m_pIpMsgThread = new IpMsgProtocol;
    m_pIpMsgThread->start();
}
