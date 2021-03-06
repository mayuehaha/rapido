﻿#include <QtGui>

#include "mainwindow.h"
#include "global.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	if(!rapido_initialize())
	{
	    qDebug() << "Rapido initialize failed.";
	    return 1;
	}

	QTranslator qtTranslator;
	qtTranslator.load("rapido_zh_CN.qm");
	app.installTranslator(&qtTranslator);

	MainWindow win;

	// Internationalization support (look at .pro file:  TRANSLATIONS = rapido_zh_CN.ts)
	// Use "lupdate" (locate at tools menu) to generate and update .ts file, then use "QT linguist" to translate.
	// Finally use "lrelease" to generate .qm file, which will be load by QTranslator (see above lines).
	win.setWindowTitle(QObject::tr("Rapido - MyIM"));

	// icon for this execute file (look at .pro file: RC_FILE = resources/rapido.rc)

	// we can modify the window icon in run-time (for this example, we compile a .png file into execute file):
	win.setWindowIcon(QIcon(":images/runing_icon.png"));
	// and load graphic file dynamiclly as the icon (usually transprant .png file):
	//win.setWindowIcon(QIcon("resources/images/rapido.png"));

	// Set initialize size and min/max size of window.
	win.setFixedSize(300, 560);
	win.setMinimumSize(300, 500);
	win.setMaximumSize(600, 800);

	win.show();

	// 系统托盘图标，各个平台（Win/Linux/Mac）均支持
	win.InitTrayIcon();
	win.ShowTrayIcon();

	// 不用在程序启动时就启动IpMsg监听线程，而是等到登录之后再启动。
	// Start the IpMsg handler thread.
	//rapido_ipmsg_thread().start();

	int iRet = app.exec();

	rapido_finalize();

	return iRet;
}


