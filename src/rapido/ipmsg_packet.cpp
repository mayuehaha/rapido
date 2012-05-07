#include "global.h"
#include "ipmsg_const.h"
#include "ipmsg_packet.h"

// ===================================================
// IpMsgPacket
// ===================================================

IpMsgPacket::IpMsgPacket(QHostAddress ip)
	: m_ref(1), m_ip(ip)
{
	//qDebug() << "IpMsgPacket::IpMsgPacket()" << m_ref;
}
IpMsgPacket::~IpMsgPacket()
{
	//qDebug() << "IpMsgPacket::~IpMsgPacket()";
}

qint32 IpMsgPacket::AddRef()
{
	++ m_ref;
	return m_ref;
}
qint32 IpMsgPacket::Release()
{
	m_ref--;
	qint32 _tmp = m_ref;
	if(_tmp == 0)
	{
		delete this;
	}
	return _tmp;
}

// ===================================================
// IpMsgSendPacket
// ===================================================


//IpMsgSendPacket::IpMsgSendPacket()
//{
//}

IpMsgSendPacket::IpMsgSendPacket(QHostAddress ip, QString additionalInfo,
								 QString extendedInfo, quint32 flags)
	: IpMsgPacket(ip)
{
	m_RetryCount = 0;
    this->additionalInfo = additionalInfo;
    this->extendedInfo = extendedInfo;
    this->m_flags = flags;
	qint64 random = qrand() % 1024;
    this->packetNoString = QString("%1").arg(random);

	_BuildPacket();
}

IpMsgSendPacket::IpMsgSendPacket(QHostAddress ip, quint32 command, quint32 options)
	: IpMsgPacket(ip)
{
	m_command = command;
	m_options = options;
}

IpMsgSendPacket::~IpMsgSendPacket()
{
}

void IpMsgSendPacket::_BuildPacket()
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

void IpMsgSendPacket::UpdateSendFlag(void)
{
	m_RetryCount++;
	m_SendingTime.restart();
}

bool IpMsgSendPacket::IsSendFailed(void)
{
	if(m_RetryCount <= R_IPMSG_SEND_RETRY)
		return false;
	if(m_SendingTime.elapsed() < R_IPMSG_SEND_INTERVAL)
		return false;
	return true;
}

//void IpMsgSendPacket::send()
//{
//    rapido::sendPacketList.append(this);
//}

// ===================================================
// IpMsgRecvPacket
// ===================================================

IpMsgRecvPacket::IpMsgRecvPacket(QHostAddress ip, const QByteArray& datagram)
	: IpMsgPacket(ip)
{
	QString packet = toUnicode(datagram);

	QStringList list = packet.split(R_COMMAND_SEPERATOR);

	// sanity check
	if (list.count() < R_IPMSG_NORMAL_FIELD_COUNT) {
		return;
	}

    this->m_packet = packet;
    this->extendedInfo = packet.section(QChar(R_EXTEND_INFO_SEPERATOR), 1, 1);

	//remember to add the situation of haven't the field
	this->additionalInfo = list.at(R_IPMSG_ADDITION_INFO_POS);

    this->packetNoString = list.at(R_IPMSG_PACKET_NO_POS);
    this->m_flags = list.at(R_IPMSG_FLAGS_POS).toUInt();

//	this->packetUser.NickName(this->additionalInfo);
//	this->packetUser.GroupName(this->extendedInfo);
//    this->packetUser.setHost(list.at(R_IPMSG_HOST_POS));
//	this->packetUser.setIp(ip);
//    this->packetUser.setLoginName(list.at(R_IPMSG_LOG_NAME_POS));
	//this->packetUser.setMac("aa:aa:aa:aa:aa:aa");
}

IpMsgRecvPacket::~IpMsgRecvPacket()
{
}

