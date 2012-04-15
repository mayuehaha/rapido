#ifndef IPMSG_USER_H
#define IPMSG_USER_H

#include <QHostAddress>

class IpMsgUser
{
public:

    IpMsgUser();
    IpMsgUser(QString packet, QHostAddress address, quint16 port);

    ~IpMsgUser();

    void setName(QString name) { myName = name; }
    QString getName() const { return myName; }

    void setGroup(QString group) { myGroup = group; }
    QString getGroup() const { return myGroup; }

    void setLoginName(QString loginName) { myLoginName = loginName; }
    QString getLoginName() const { return myLoginName; }

    void setHost(QString host) { myHost = host; }
    QString getHost() const { return myHost; }

    QString ip() const { return myIpAddress.toString(); }

    void setDisplayLevel(QString displayLevel) {
        myDisplayLevel = displayLevel;
    }
    QString displayLevel() const { return myDisplayLevel; }

private:
    // Get group name or absence string
    QString parseAdditionalInfo(QString &packet);
    void initUser(QString &packet);

    //user name
    QString myName;
    //computer login name
    QString myLoginName;
    //group name
    QString myGroup;
    //computer host name
    QString myHost;
    //ip address
    QHostAddress myIpAddress;
    //compyter mac
    QString myMac;

    quint16 myPort;
    QString myDisplayLevel;

};

#endif // IPMSG_USER_H
