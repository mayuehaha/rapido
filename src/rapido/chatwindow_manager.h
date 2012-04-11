#ifndef CHATWINDOW_MANAGER_H
#define CHATWINDOW_MANAGER_H

#include "chatwindow.h"

#include <QObject>

class ChatWindowManager : public QObject
{
	Q_OBJECT
public:
	explicit ChatWindowManager(QObject *parent = 0);
	~ChatWindowManager();
	
signals:
	
public slots:
private slots:
	void newMsg(void);

private:
	ChatWindow* m_pChatWin;
};

#endif // CHATWINDOW_MANAGER_H
