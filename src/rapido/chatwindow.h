#ifndef CHATWINDOW_H
#define CHATWINDOW_H

//#include <QMainWindow>
#include <QWebView.h>

class ChatWindow : public QWebView
{
	Q_OBJECT
public:
	explicit ChatWindow(QWidget *parent = 0);
	
signals:
	
public slots:
	
};

#endif // CHATWINDOW_H
