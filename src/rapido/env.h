#ifndef ENV_H
#define ENV_H

#include <QRegExp>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QByteArray>

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

	QString m_strHtmlBasePath;
};

#endif // ENV_H
