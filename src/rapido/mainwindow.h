#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QtWebKit/qwebview.h>

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
    
public slots:
private slots:
	void _onTrayIconEvent(QSystemTrayIcon::ActivationReason reason);
	//void _onQuit();
    
protected:
	QSystemTrayIcon* m_pTrayIcon;
	QMenu* m_pTrayMenu;
	QAction* m_pQuitAction;
};

#endif // MAINWINDOW_H
