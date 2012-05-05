/**
@file chatwindow_manager.h
@brief 聊天窗口管理类
*/

#ifndef CHATWINDOW_MANAGER_H
#define CHATWINDOW_MANAGER_H

//#include "ipmsg_packet.h"

#include <QObject>
#include <QMap>
//#include <QHostAddress>

class IpMsgRecvPacket;
class ChatWindow;

// 定义一个基于QMap的数据类型，对应关系为 发送者IP(字符串形式) => 聊天窗口实例指针
typedef QMap<QString, ChatWindow*> IpMsgChatWindows;

/// @brief 聊天窗口管理类
///
/// 用于管理所有聊天窗口实例，包括创建、销毁等操作。
class ChatWindowManager : public QObject
{
	Q_OBJECT
public:
	explicit ChatWindowManager(QObject* pParent = 0);
	~ChatWindowManager();
	
signals:
	
public slots:
private slots:
	void _onReceiveMessage(IpMsgRecvPacket* packet);

private:
    void _destroyAllChatWindow(void);

private:
	IpMsgChatWindows m_IpMsgChatWindows;
};

#endif // CHATWINDOW_MANAGER_H
