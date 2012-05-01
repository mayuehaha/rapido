#ifndef IPMSG_USER_H
#define IPMSG_USER_H

#include <QHostAddress>


class IpMsgUser
{
public:

    IpMsgUser();

	void setName(QString name) { ipmsgName = name; }
	QString getName() const { return ipmsgName; }

	void setLoginName(QString login_name) { loginName = login_name; }
	QString getLoginName() const { return loginName; }

	void setGroup(QString group) { groupName = group; }
	QString getGroup() const { return groupName; }

	void setHost(QString host) { hostName = host; }
	QString getHost() const { return hostName; }

	void setIp(QHostAddress ip) { ipAddress = ip; }
	QString getIp() const { return ipAddress.toString(); }

	void setMac(QString mac) { macAddress = mac; }
	QString getMac() const { return macAddress; }

//	void setDisplayLevel(QString displayLevel) {
//		m_displayLevel = displayLevel;
//	}
//	QString displayLevel() const { return m_displayLevel; }


    ~IpMsgUser();

private:

	// user name
	QString ipmsgName;
	// computer login name
	QString loginName;
	// group name
	QString groupName;
	// computer host name
	QString hostName;
	// ip address
	QHostAddress ipAddress;
	// computer mac
	QString macAddress;

	quint16 listeningPort;
	QString displayLevel;

};

#endif // IPMSG_USER_H
