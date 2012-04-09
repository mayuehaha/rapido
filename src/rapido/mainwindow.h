#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebView.h>

//#include "ipmsg_protocol.h"

class MainWindow : public QWebView
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    //IpMsgProtocol* m_pIpMsgThread;

signals:
    
public slots:
    
};

#endif // MAINWINDOW_H
