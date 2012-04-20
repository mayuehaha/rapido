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
	void onLoginFailed(const QString& strReason);

public slots:
	void jsLogin(const QString& strUserId, const QString& strPasswd);

private slots:
	void _onTrayIconEvent(QSystemTrayIcon::ActivationReason reason);
	void _onAddJSObject();
	//void _onQuit();
    
protected:
	QSystemTrayIcon* m_pTrayIcon;
	QMenu* m_pTrayMenu;
	QAction* m_pQuitAction;
};

#endif // MAINWINDOW_H
