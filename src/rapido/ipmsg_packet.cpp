#include "global.h"
#include "ipmsg_const.h"
#include "ipmsg_packet.h"

// ===================================================
// IpMsgPacket
// ===================================================

IpMsgPacket::IpMsgPacket(QHostAddress ip, quint16 port)
	: m_ref(1), m_ip(ip), m_port(port)
{
	qDebug() << "IpMsgPacket::IpMsgPacket()" << m_ref;
}
IpMsgPacket::~IpMsgPacket()
{
	qDebug() << "IpMsgPacket::~IpMsgPacket()";
}

void IpMsgPacket::addRef()
{
	++ m_ref;
}
void IpMsgPacket::delRef()
{
	if(--m_ref == 0)
	{
		delete this;
	}
}

// ===================================================
// IpMsgSendPacket
// ===================================================


//IpMsgSendPacket::IpMsgSendPacket()
//{
//}

IpMsgSendPacket::IpMsgSendPacket(QHostAddress ip, quint16 port, QString additionalInfo,
								 QString extendedInfo, quint32 flags)
	: IpMsgPacket(ip, port)
{
    this->additionalInfo = additionalInfo;
    this->extendedInfo = extendedInfo;
    this->m_flags = flags;
	qint64 random = qrand() % 1024;
    this->packetNoString = QString("%1").arg(random);

	constructPacket();
}

void IpMsgSendPacket::constructPacket()
{
    this->m_packet.append(QString("%1%2").arg(IPMSG_VERSION).arg(R_COMMAND_SEPERATOR));

    this->m_packet.append(QString("%1%2").arg(this->packetNoString)
					.arg(R_COMMAND_SEPERATOR));

    this->m_packet.append(rapido::myself.getLoginName().toAscii());
    this->m_packet.append(R_COMMAND_SEPERATOR);
    this->m_packet.append(rapido::myself.getHost().toAscii());
    this->m_packet.append(R_COMMAND_SEPERATOR);
    this->m_packet.append(QString("%1%2").arg(this->m_flags).arg(R_COMMAND_SEPERATOR));
    this->m_packet.append(this->additionalInfo);
}

void IpMsgSendPacket::send()
{
    rapido::sendPacketList.append(this);
}

IpMsgSendPacket::~IpMsgSendPacket()
{
}

// ===================================================
// IpMsgRecvPacket
// ===================================================

//IpMsgRecvPacket::IpMsgRecvPacket(){}

IpMsgRecvPacket::IpMsgRecvPacket(QHostAddress ip, quint16 port, QString packet)
	: IpMsgPacket(ip, port)
{
	QStringList list = packet.split(R_COMMAND_SEPERATOR);

	// sanity check
	if (list.count() < R_IPMSG_NORMAL_FIELD_COUNT) {
		return;
	}

    this->m_packet = packet;
    this->extendedInfo = packet.section(QChar(R_EXTEND_INFO_SEPERATOR), 1, 1);

	//remember to add the situation of haven't the field
    this->additionalInfo = toUnicode(list.at(R_IPMSG_ADDITION_INFO_POS).toAscii());

    this->packetNoString = list.at(R_IPMSG_PACKET_NO_POS);
    this->m_flags = list.at(R_IPMSG_FLAGS_POS).toUInt();

	this->packetUser.NickName(this->additionalInfo);
	this->packetUser.GroupName(this->extendedInfo);
    this->packetUser.setHost(list.at(R_IPMSG_HOST_POS));
	this->packetUser.setIp(ip);
    this->packetUser.setLoginName(list.at(R_IPMSG_LOG_NAME_POS));
	//this->packetUser.setMac("aa:aa:aa:aa:aa:aa");
}

IpMsgRecvPacket::~IpMsgRecvPacket()
{
}

