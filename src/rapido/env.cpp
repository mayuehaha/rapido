#include "env.h"

#include <QProcess>
#include <QFile>
//#include <QStringList>

Env::Env()
{
}

bool Env::Initialize(void)
{
	_getLoginName();

	if(!_getNetworkInfo())
		return false;

	return true;
}

void Env::_getLoginName()
{
	// I don't know how to get login name on each OS, so I try to pick it from environment variables.
#if defined(Q_OS_WIN)
	m_strLoginName = _getEnvironmentVariable(QRegExp("USERNAME.*"));
#elif defined(Q_OS_LINUX)
	m_strLoginName = _getEnvironmentVariable(QRegExp("LOGNAME.*"));
#elif defined(Q_OS_MAC)
	m_strLoginName = _getEnvironmentVariable(QRegExp("LOGNAME.*"));
#endif
	if(m_strLoginName.isEmpty())
		m_strLoginName = "UNKNOWN-USERNAME";
}

bool Env::_getNetworkInfo(void)
{
	QString strIp;

	// enum all network interface.
	QList<QNetworkInterface> niList = QNetworkInterface::allInterfaces();
	foreach(QNetworkInterface ni, niList)
	{
		if(ni.hardwareAddress().isEmpty())
			continue;

		//qDebug() << ni.allAddresses();
		//qDebug() << ni;
		QList<QNetworkAddressEntry> naeList = ni.addressEntries();
		if(0 == naeList.count())
			continue;

		//qDebug() << ni.hardwareAddress();
		foreach(QNetworkAddressEntry nae, naeList)
		{
			strIp = nae.ip().toString();

			// skip IPV6
			if(nae.ip().protocol() == QAbstractSocket::IPv6Protocol)
				continue;
			// skip local loop as 127.0.0.1.
			if(strIp.startsWith("127."))
				continue;

			// Ok we found it.
			m_strHostMAC = ni.hardwareAddress();
			m_hostIp = nae.ip();
			break;
		}

		// Stop finding once we found one.
		if(!m_hostIp.isNull())
			break;
	}

	if(m_hostIp.isNull())
		return false;

	// I don't know how to get login name on each OS, so I try to pick it from environment variables.
#if defined(Q_OS_WIN)
	// QHostInfo::localHostName() works fine on Windows7.
	m_strHostName = QHostInfo::localHostName();
	if(m_strHostName.isEmpty())
		m_strHostName = _getEnvironmentVariable(QRegExp("COMPUTERNAME.*"));
#elif defined(Q_OS_LINUX)
	m_strHostName = _getEnvironmentVariable(QRegExp("HOSTNAME.*"));

	// if no HOSTNAME environment variable is set, read it from /etc/hostname,
	// for distribution like ubuntu.
	if (m_strHostName.isEmpty()) {
		QFile file("/etc/hostname");
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			m_strHostName.append(file.readLine());
			m_strHostName.remove(QChar('\n'));
		}
	}

#elif defined(Q_OS_MAC)
	// QHostInfo::localHostName() will add ".local" after the host name, so use env. varb.
	m_strHostName = _getEnvironmentVariable(QRegExp("HOSTNAME.*"));
#endif

	if (m_strHostName.isEmpty())
		m_strHostName = "UNKNOWN-HOSTNAME";

	qDebug() << "IP   : " << m_hostIp.toString();
	qDebug() << "MAC  : " << m_strHostMAC;
	qDebug() << "Host : " << m_strHostName;

	return true;
}


QString Env::_getEnvironmentVariable(QRegExp regExp)
{
	QStringList envList = QProcess::systemEnvironment();

	int index = envList.indexOf(regExp);
	if (index != -1)
	{
		// Just like "USERNAME=Apex"
		QStringList sl = envList.at(index).split("=");
		if (sl.size() == 2)
			return sl.at(1).toUtf8();
	}

	return QString("");
}
