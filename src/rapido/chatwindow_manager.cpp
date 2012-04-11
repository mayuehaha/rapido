#include "chatwindow_manager.h"

ChatWindowManager::ChatWindowManager(QObject *parent) :
	QObject(parent)
{
	m_pChatWin = NULL;
}

ChatWindowManager::~ChatWindowManager()
{
	if(NULL != m_pChatWin)
		delete m_pChatWin;
}

void ChatWindowManager::newMsg()
{
	if(NULL == m_pChatWin)
	{
		m_pChatWin = new ChatWindow;
	}
	m_pChatWin->show();
}
