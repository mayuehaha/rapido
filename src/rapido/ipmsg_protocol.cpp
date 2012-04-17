#include "ipmsg_protocol.h"

#include <QNetworkInterface>
#include <QHostInfo>
#include <QUdpSocket>
#include <QStringList>
#include <QDebug>

#include "global.h"
#include "ipmsg_packet.h"

/*
command:
  1:123:apex:APEXPC:1:ApexLiu
format:
  unknown : packet-number : login-name : computer-name (or host-name) : command : user-name
*/

IpMsgProtocol::IpMsgProtocol(QObject *parent)
    :QObject(parent)
{
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	// Set init package number as random.
	m_packetNo = qrand() % 1024;

	// !! DO NOT use Qt::BlockingQueuedConnection, otherwise you'll got an exception.
	//connect(&m_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()), Qt::BlockingQueuedConnection);
	connect(&m_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void IpMsgProtocol::start()
{
	if(!m_db.Connect())
	{
		qDebug() << "Cannot load db.";
		//return;
	}

	//if(!m_socket.bind(QHostAddress::Any, IPMSG_DEFAULT_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
	if(!m_socket.bind(rapido_env().m_hostIp, IPMSG_DEFAULT_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
	{
        qDebug() << "Cannot bind.";
        return;
    }
	broadcastLogin();
	// broadcast that I'm online. :)
    //QByteArray datagram = "1:" + QByteArray::number(1) + ":apex:A-PC:1:ApexLiu";
	//QByteArray datagram = "1:" + QByteArray::number(++m_packetNo) + ":apex:"+ hostName.toAscii() +":1:ApexLiu";
	QByteArray datagram = "1:" + QByteArray::number(++m_packetNo) + ":apex:"+ rapido_env().m_strHostName.toAscii() +":1:" + rapido_env().m_strLoginName.toAscii();
    //QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
	qDebug() << "send:" << QString(datagram);
    m_socket.writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, IPMSG_DEFAULT_PORT);
}

void IpMsgProtocol::broadcastLogin()
{

	qDebug() << "broadcastLogin";

	quint32 flags = 0;
	flags |= IPMSG_BR_ENTRY | IPMSG_FILEATTACHOPT;

	QString entryMessage = QString("%1%2%3%4").arg("ÕÅ´óÂÌ")
			.arg(QChar('\0'))
			.arg("À­µÇ")
			.arg(QChar('\0'));
	IpMsgSendPacket ipMsgSendPacket(QHostAddress::Null, 0/* port */,
					entryMessage, ""/* extendedInfo */, flags);

	qDebug() << "hehe" <<ipMsgSendPacket.m_packet;
	//rapido::sendPacketList
	//rapido::sendPacketList.append(ipMsgSendPacket);
	//Global::msgThread->addSendMsg(Msg(sendMsg));

	//if(!m_socket.bind(QHostAddress::Any, IPMSG_DEFAULT_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
	if(!m_socket.bind(rapido_env().m_hostIp, IPMSG_DEFAULT_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
	{
		qDebug() << "Cannot bind.";
		return;
	}

	// broadcast that I'm online. :)
	//QByteArray datagram = "1:" + QByteArray::number(1) + ":apex:A-PC:1:ApexLiu";
	//QByteArray datagram = "1:" + QByteArray::number(++m_packetNo) + ":apex:"+ hostName.toAscii() +":1:ApexLiu";
	QByteArray datagram = "1:" + QByteArray::number(++m_packetNo) + ":apex:"+ rapido_env().m_strHostName.toAscii() +":1:" + rapido_env().m_strLoginName.toAscii();
	//QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
	qDebug() << "send:" << QString(datagram);
	m_socket.writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, IPMSG_DEFAULT_PORT);
}
void IpMsgProtocol::readPendingDatagrams()
{
//	static qint32 ii = 0;
//	if(0 == ii)
//	{
//		ii = 1;
//		emit newMsg();
//	}
	//static qint32 packet_no = 3;
	//packet_no++;

	while (m_socket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_socket.pendingDatagramSize());
		QHostAddress senderIp;
        quint16 senderPort;

		if(-1 == m_socket.readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort))
            continue;

		QString strSenderIp = senderIp.toString();

		// skip broadcast to myself.
		if(senderIp == rapido_env().m_hostIp)
		{
			qDebug() << "message from myself, skip.";
			continue;
		}

		QString data(datagram);
		//qDebug() << "sender: " << senderIp << ":" << senderPort;
		//qDebug() << "content: " << data;

		QStringList cmdList = data.split(R_IPMSG_COMMAND_SEPERATOR);

		// check
		if (cmdList.count() < R_IPMSG_NORMAL_FIELD_COUNT)
		{
			qDebug() << "Invalid IpMsg message format.";
			continue;
		}

		qint32 flags = cmdList.at(R_IPMSG_FLAGS_POS).toUInt();
		qint32 cmd = IPMSG_GET_MODE(flags);
		switch(cmd)
		{
		case IPMSG_NOOPERATION:
			break;
		case IPMSG_BR_ENTRY:
		{
			// add this one into user list.
			qDebug() << "somebody online now." << strSenderIp;

			// told he/she/it I'm already online. :)

			//QByteArray datagramSend = "1:" + QByteArray::number(2) + ":apex:"+ hostName.toAscii() +":33:";
			QByteArray datagramSend = "1:" + QByteArray::number(++m_packetNo) + ":apex:" + rapido_env().m_strHostName.toAscii() + ":" + QByteArray::number(qint32(IPMSG_ANSENTRY)) + ":";
			//QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
			m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), senderIp, senderPort);
			break;
		}


			break;
		case IPMSG_BR_EXIT:
			// remove this one from user list.
			qDebug() << "somebody leave." << strSenderIp;
			break;
		case IPMSG_GETINFO:
			qDebug() << "TODO: got command: IPMSG_GETINFO." << strSenderIp;
			break;
		case IPMSG_ANSENTRY:
		{
			// add this one into user list.
			qDebug() << "Ok, somebody says online already." << strSenderIp;

			QString userName = cmdList.at(5);
			QTextCodec *codec = QTextCodec::codecForName("GBK");
			//QTextCodec *codec = QTextCodec::codecForLocale();
			QByteArray tmp(cmdList.at(5).toAscii());//.toLocal8Bit());
			userName = codec->toUnicode(tmp);
			qDebug() << "==> " << codec->toUnicode(tmp);

			break;
		}
		case IPMSG_SENDMSG:
		{
			qDebug() << "content: " << data;
			//QByteArray datagramSend = "1:" + QByteArray::number(2) + ":apex:"+ hostName.toAscii() +":33:";
			QByteArray datagramSend = "1:" + QByteArray::number(++m_packetNo) + ":apex:" + rapido_env().m_strHostName.toAscii() + ":"+QByteArray::number(qint32(IPMSG_RECVMSG))+":";
			//QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
			m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), senderIp, senderPort);

			IpMsgRecvPacket* pPacket = new IpMsgRecvPacket(senderIp, senderPort, datagramSend);
            emit newMsg(pPacket);

			break;
		}
		case IPMSG_RECVMSG:
			qDebug() << "Ok, he/she/it got my message." << strSenderIp;
			break;
		case IPMSG_READMSG:
		{
			qDebug() << "send to" << strSenderIp << "I have read it.";
			//QByteArray datagramSend = "1:" + QByteArray::number(2) + ":apex:"+ hostName.toAscii() +":33:";
			QByteArray datagramSend = "1:" + QByteArray::number(++m_packetNo) + ":apex:" + rapido_env().m_strHostName.toAscii() + ":"+QByteArray::number(qint32(IPMSG_ANSREADMSG))+":";
			//QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
			m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), senderIp, senderPort);
			break;
		}
		case IPMSG_FEIQ_REMOTE_START_TYPING:	// FeiQ special.
			qDebug() << strSenderIp << "is typing to you...";
			break;
		case IPMSG_FEIQ_REMOTE_KEEP_TYPING:
			qDebug() << strSenderIp << "is still typing to you...";
			break;
		default:
		{
			qDebug() << "sender: " << strSenderIp << ":" << senderPort;
			qDebug() << "content: " << data;
			QTextCodec *codec = QTextCodec::codecForName("GBK");
			QByteArray tmp(cmdList.at(5).toAscii());
			qDebug() << "==> " << codec->toUnicode(tmp);
			qDebug("Unknown command: 0x%02X", cmd);
			break;
		}
		}
    }
}


void IpMsgProtocol::processSendMsg()
{
	//qDebug()<<"mayuehehe";
}
