#include "ipmsg_db.h"

/*
rapido.db table structs:

message:
id/ip/mac/user_name/group_name/host_name/login_name
datetime/message

attach-files:
id/message_id/file_name/file_mime_type


*/

IpMsgDB::IpMsgDB(QObject *parent)
	:QObject(parent)
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");
}

bool IpMsgDB::Connect(void)
{
	//QString strExecPath = QApplication::applicationDirPath();
	//QString strDbFile = strExecPath;
	//strDbFile += "/rapido.db";
	QString strDbFile = "rapido.db";

	m_db = QSqlDatabase::addDatabase("QSQLITE", "rapido_sqlite");
	m_db.setDatabaseName(strDbFile);
	if(!m_db.open())
	{
		qDebug() << "Cannot open database.";
		return false;
	}

	QSqlQuery q(m_db);
	if(q.exec("CREATE TABLE `history` (`id` INT PRIMARY KEY, `message` VARCHAR)") == false)
	{
		qDebug() << "Cannot create table.";
	}

	q.exec("INSERT INTO `history` VALUES (1, \"I'm Rapido\")");
	q.exec("INSERT INTO `history` VALUES (2, \"Hello IpMsg and FeiQ!\")");

	m_db.close();
	return true;
}
