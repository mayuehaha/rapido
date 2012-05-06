#ifndef CHATWINDOW_MANAGER_H
#define CHATWINDOW_MANAGER_H

#include "chatwindow.h"
//#include "ipmsg_packet.h"

#include <QObject>
#include <QMap>
#include <QHostAddress>

class IpMsgRecvPacket;

// sender ip <==> chat window
typedef QMap<QString, ChatWindow*> IpMsgChatWindows;

class ChatWindowManager : public QObject
{
	Q_OBJECT
public:
	explicit ChatWindowManager(QObject *parent = 0);
	~ChatWindowManager();
	
signals:
	
public slots:
private slots:
    void newMsg(IpMsgRecvPacket* packet);

private:
    void _destroyAllChatWindow(void);

private:
	IpMsgChatWindows m_IpMsgChatWindows;
};

#endif // CHATWINDOW_MANAGER_H
