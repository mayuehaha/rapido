#ifndef ENV_H
#define ENV_H

#include <QRegExp>
#include <QNetworkInterface>
#include <QHostInfo>

class Env
{
public:
	Env();

	bool Initialize(void);

protected:
	bool _getNetworkInfo(void);
	void _getLoginName(void);
	QString _getEnvironmentVariable(QRegExp regExp);

public:
	QHostAddress m_hostIp;
	QString m_strHostMAC;
	QString m_strHostName;
	QString m_strLoginName;

};

#endif // ENV_H