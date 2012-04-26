#include "chatwindow_manager.h"
#include "ipmsg_packet.h"

ChatWindowManager::ChatWindowManager(QObject *parent) :
	QObject(parent)
{
}

ChatWindowManager::~ChatWindowManager()
{
    _destroyAllChatWindow();
}

void ChatWindowManager::newMsg(IpMsgRecvPacket *packet)
{
	// find the chat window by sender ip. If not found, create one.
    IpMsgChatWindows::iterator it = m_IpMsgChatWindows.find(packet->getIp());
	if(m_IpMsgChatWindows.end() != it)
	{
		it.value()->show();
	}
	else
	{
		ChatWindow* pChatWin = new ChatWindow;
        m_IpMsgChatWindows.insert(packet->getIp(), pChatWin);
		pChatWin->show();
	}

	delete packet;

}

void ChatWindowManager::_destroyAllChatWindow(void)
{
	IpMsgChatWindows::iterator it = m_IpMsgChatWindows.begin();
	for(; it != m_IpMsgChatWindows.end(); ++it)
	{
		delete it.value();
	}
	m_IpMsgChatWindows.clear();
}
