#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
//#include <QMainWindow>
//#include <QtWebKit/qwebview.h>
#include <QWebView>

//#include "ipmsg_protocol.h"

class MainWindow : public QWebView
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
	//~MainWindow();

	void InitTrayIcon();
	void ShowTrayIcon();

protected:
    //IpMsgProtocol* m_pIpMsgThread;

signals:
	// login.html
	void onLoginFailed(const QString& strReason);
	// index.html
	void jsOnUserOnline(const QString& strUserName, const QString& strIp);
	void jsOnUserOffline(const QString& strIp);

public slots:
	// login.html
	void login(const QString& strUserId, const QString& strPasswd);
	// index.html
	void startIpMsgThread(void);

	void onUserOnline(const QString& strUserName, const QString& strIp);
	void onUserOffline(const QString& strIp);

private slots:
	void _onTrayIconEvent(QSystemTrayIcon::ActivationReason reason);
	void _onAddJSObject();
	void _onQuit();
    
protected:
	QSystemTrayIcon* m_pTrayIcon;
	QMenu* m_pTrayMenu;
	QAction* m_pQuitAction;
};

#endif // MAINWINDOW_H
