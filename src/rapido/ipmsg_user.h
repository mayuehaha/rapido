#ifndef IPMSG_USER_H
#define IPMSG_USER_H

#include <QHostAddress>

#include "chatwindow.h"

class IpMsgUser
{
public:
    IpMsgUser();
	IpMsgUser(const QString& strNickName, const QString& strLoginName, QHostAddress ip);
	virtual ~IpMsgUser();


	void setName(QString name) { m_strNickName = name; }
	QString getName() const { return m_strNickName; }
	void NickName(const QString& strNickName){m_strNickName = strNickName;}
	const QString& NickName(void) const {return m_strNickName;}

	void setLoginName(QString login_name) { m_strLoginName = login_name; }
	QString getLoginName() const { return m_strLoginName; }

	//void setGroup(QString group) { groupName = group; }
	//QString getGroup() const { return groupName; }
	void GroupName(const QString& strGroupName){m_strGroupName = strGroupName;}
	const QString& GroupName(void) const {return m_strGroupName;}

	void setHost(QString host) { m_strHostName = host; }
	QString getHost() const { return m_strHostName; }

	void setIp(QHostAddress ip) { m_ip = ip; }
	QString getIp() const { return m_ip.toString(); }

	//void setMac(QString mac) { macAddress = mac; }
	//QString getMac() const { return macAddress; }

//	void setDisplayLevel(QString displayLevel) {
//		m_displayLevel = displayLevel;
//	}
//	QString displayLevel() const { return m_displayLevel; }


private:

    //user name
	QString ipmsgName;
    //computer login name
	QString loginName;
    //group name
	QString groupName;
    //computer host name
	QString hostName;
    //ip address
	QHostAddress ipAddress;
    //compyter mac
	QString macAddress;

    quint8 status;
    ChatWindow* pChatWin;

	quint16 listeningPort;
	// name for display
	QString m_strNickName;
	// user name when login the system, if not set nick name, use login name for display.
	QString m_strLoginName;

	// group name
	QString m_strGroupName;

	// computer host name, or computer name.
	QString m_strHostName;
	// ip address
	QHostAddress m_ip;
	// computer mac
	//QString macAddress;

	//quint16 listeningPort;
	QString displayLevel;

};

#endif // IPMSG_USER_H
