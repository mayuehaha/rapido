/**
@file chatwindow.h
@brief 聊天窗口类
*/

#ifndef CHATWINDOW_H
#define CHATWINDOW_H

//#include <QMainWindow>
#include <qwebview.h>

/// @brief 聊天窗口类
///
/// 每一个与之聊天的对象，对应一个聊天窗口类的实例。所有聊天窗口由 ChatWindowManager 类进行管理。
class ChatWindow : public QWebView
{
	Q_OBJECT
public:
	explicit ChatWindow(QWidget *parent = 0);
	
signals:
	
public slots:
	
};

#endif // CHATWINDOW_H
