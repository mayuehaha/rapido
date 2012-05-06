#ifndef IPMSG_DB_H
#define IPMSG_DB_H

#include <QObject>
#include <QtSql>

class IpMsgDB : public QObject
{
	Q_OBJECT
public:
	IpMsgDB(QObject *parent = 0);

	bool Connect(void);

protected:
	QSqlDatabase m_db;
};

#endif // IPMSG_DB_H
