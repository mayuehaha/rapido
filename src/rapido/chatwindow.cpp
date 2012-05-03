#include "chatwindow.h"

#include <QtGui>
#include "global.h"

ChatWindow::ChatWindow(QWidget *parent) :
	QWebView(parent)
{
	QString strUrl = rapido_env().m_strHtmlBasePath;
	strUrl += "chat.html";
	QUrl startURL = QUrl(strUrl);

	// Load web content now!
	setUrl(startURL);
}
