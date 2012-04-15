#include "chatwindow.h"

#include <QtGui>

ChatWindow::ChatWindow(QWidget *parent) :
	QWebView(parent)
{
	QString strExecPath = QApplication::applicationDirPath();
	QString strUrl = "file:///";
	strUrl += strExecPath;
#if defined(Q_OS_MAC)
	strUrl += "/../../../skin/chat.html";
#else
	strUrl += "/../skin/chat.html";
#endif
	QUrl startURL = QUrl(strUrl);

	// Load web content now!
	setUrl(startURL);
}
