#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QWebView.h>

//#include "ipmsg_protocol.h"

class MainWindow : public QWebView
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

	void InitTrayIcon(void);
	void ShowTrayIcon(void);

protected:
    //IpMsgProtocol* m_pIpMsgThread;

signals:
    
public slots:
    
protected:
	QSystemTrayIcon* m_pTrayIcon;
};

#endif // MAINWINDOW_H
