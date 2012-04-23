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
	//not yet
	/*if(!m_db.Connect())
	{
		qDebug() << "Cannot load db.";
		//return;
	}*/

	if(!m_socket.bind(rapido_env().m_hostIp, IPMSG_DEFAULT_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
	{
        qDebug() << "Cannot bind.";
        return;
    }

    // broadcast that I'm online. :)
    broadcastLogin();

}

void IpMsgProtocol::broadcastLogin()
{
    quint32 flags = 0;
	flags |= IPMSG_BR_ENTRY | IPMSG_FILEATTACHOPT;

	QString entryMessage = QString("%1%2%3%4").arg(rapido::myself.getName())
			.arg(QChar(R_EXTEND_INFO_SEPERATOR))
			.arg(rapido::myself.getGroup())
			.arg(QChar(R_EXTEND_INFO_SEPERATOR));

	//QHostAddress::Broadcast
	QHostAddress mytest = QHostAddress("192.168.4.29");
	IpMsgSendPacket ipMsgSendPacket(mytest, IPMSG_DEFAULT_PORT/* port */,
					entryMessage, ""/* extendedInfo */, flags);

    rapido::sendPacketList.append(ipMsgSendPacket);
    qDebug() << "broadcast:  " <<ipMsgSendPacket.m_packet;
}


void IpMsgProtocol::processSendMsg()
{
	for (int i = 0; i < rapido::sendPacketList.size(); ++i) {
		handleMsg(rapido::sendPacketList.at(i));
	}
	rapido::sendPacketList.clear();
}

//can it be run without trouble with the object not the point
void IpMsgProtocol::handleMsg(IpMsgSendPacket IpMsgPkt)
{
	m_socket.writeDatagram(IpMsgPkt.m_packet.toLocal8Bit().data(), IpMsgPkt.m_packet.size(), IpMsgPkt.m_ipAddress, IpMsgPkt.m_port);
//    // Delete msg
//    if (msg->state() == MsgBase::SendAckOk) {
//        Global::msgThread->removeSendMsgNotLock(msg->packetNoString());
//    }

//    // Delete msg
//    if (msg->sendTimes() >= MAX_RE_SEND_TIMES) {
//        Global::msgThread->removeSendMsgNotLock(msg->packetNoString());
//    }

//    // Send msg
//    if (msg->state() == MsgBase::NotSend
//        || isResendNeeded(msg)) {

//        msg->setState(MsgBase::Sending);
//        msg->incrementSendTimes();

//        switch (GET_MODE(msg->flags())) {
//        case IPMSG_BR_ENTRY:
//        case IPMSG_BR_EXIT:
//        case IPMSG_BR_ABSENCE:
//            broadcastUserMsg(msg);
//            Global::msgThread->removeSendMsgNotLock(msg->packetNoString());
//            break;

//        case IPMSG_ANSENTRY:
//        case IPMSG_ANSREADMSG:
//        case IPMSG_RELEASEFILES:
//            broadcastMsg(msg);
//            Global::msgThread->removeSendMsgNotLock(msg->packetNoString());
//            break;


//        case IPMSG_READMSG:
//            broadcastMsg(msg);
//            // XXX TODO: If IPMSG_READCHECKOPT is on, we need to check if
//            // sucessfully sended.
//            break;

//        case IPMSG_RECVMSG:
//            broadcastMsg(msg);
//            // XXX TODO: need to check if sucessfully sended.
//            break;

//        case IPMSG_SENDMSG:
//            broadcastMsg(msg);
//            // XXX TODO: need to check if sucessfully sended.
//            break;

//        default:
//            Global::msgThread->removeSendMsgNotLock(msg->packetNoString());
//            break;
//        }
//    }
}

void IpMsgProtocol::readPendingDatagrams()
{
	while (m_socket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_socket.pendingDatagramSize());
		QHostAddress senderIp;
        quint16 senderPort;

		if(-1 == m_socket.readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort))
            continue;

		// skip broadcast to myself.
		if(senderIp == rapido_env().m_hostIp)
		{
			qDebug() << "message from myself, skip.";
			continue;
		}

		QString packet = toUnicode(datagram);
		IpMsgRecvPacket recvPacket = IpMsgRecvPacket(senderIp, senderPort, packet);
		processRecvMsg(recvPacket);

		//check the return value
//        if(recvPacket == NULL){
//            qDebug() << "erro formate, Packet:" <<  data;
//        }

//		QStringList cmdList = data.split(R_IPMSG_COMMAND_SEPERATOR);
    }
}

void IpMsgProtocol::processRecvMsg(IpMsgRecvPacket recvPacket)
{

	qDebug() << "MsgServer::" << IPMSG_GET_MODE(recvPacket.m_flags);
	switch (IPMSG_GET_MODE(recvPacket.m_flags)) {
		case IPMSG_BR_ENTRY:
			qDebug() << "some guys entry";
			rapido::userList1.append(recvPacket.m_ipMsgUser);
		//	processEntryMsg(msg);
			break;

		case IPMSG_BR_EXIT:
			//emit newExitMsg(msg);
			break;

		case IPMSG_ANSENTRY:
			qDebug() << "some guys answer";
			rapido::userList1.append(recvPacket.m_ipMsgUser);
			//emit newUserMsg(msg);
			break;
	}

//    case IPMSG_BR_ABSENCE:
//        // XXX TODO: support it
//        break;

//    case IPMSG_SENDMSG:
//        processRecvSendMsg(msg);
//        break;

//    case IPMSG_READMSG:
//        processRecvReadMsg(msg);
//        break;

//    case IPMSG_ANSREADMSG:
//    case IPMSG_RECVMSG:
//    case IPMSG_DELMSG:
//        // do nothing
//        // XXX TODO: do something?????????
//        break;

//    case IPMSG_RELEASEFILES:
//        processRecvReleaseFilesMsg(msg);
//        break;

//    default:
//        break;
//    }

//    // check
//    if (cmdList.count() < R_IPMSG_NORMAL_FIELD_COUNT)
//    {
//        qDebug() << "Invalid IpMsg message format.";
//        continue;
//    }

//    qint32 flags = cmdList.at(R_IPMSG_FLAGS_POS).toUInt();
//    qint32 cmd = IPMSG_GET_MODE(flags);
//    switch(cmd)
//    {
//        case IPMSG_NOOPERATION:
//            break;
//        //somebody is online message
//        case IPMSG_BR_ENTRY:
//        {
//            // add this one into user list.
//           // qDebug() << "somebody online now." << strSenderIp;

//            // told he/she/it I'm already online. :)

//            //QByteArray datagramSend = "1:" + QByteArray::number(2) + ":apex:"+ hostName.toAscii() +":33:";
//            QByteArray datagramSend = "1:" + QByteArray::number(++m_packetNo) + ":apex:" + rapido_env().m_strHostName.toAscii() + ":" + QByteArray::number(qint32(IPMSG_ANSENTRY)) + ":";
//            //QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
//            m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), senderIp, senderPort);
//            break;
//        }


//        break;
//    case IPMSG_BR_EXIT:
//        // remove this one from user list.
//        qDebug() << "somebody leave." << strSenderIp;
//        break;
//    case IPMSG_GETINFO:
//        qDebug() << "TODO: got command: IPMSG_GETINFO." << strSenderIp;
//        break;
//    case IPMSG_ANSENTRY:
//    {
//        // add this one into user list.
//        qDebug() << "Ok, somebody says online already." << strSenderIp;

//        QString userName = cmdList.at(5);
//        QTextCodec *codec = QTextCodec::codecForName("GBK");
//        //QTextCodec *codec = QTextCodec::codecForLocale();
//        QByteArray tmp(cmdList.at(5).toAscii());//.toLocal8Bit());
//        userName = codec->toUnicode(tmp);
//        qDebug() << "==> " << codec->toUnicode(tmp);

//        break;
//    }
//    case IPMSG_SENDMSG:
//    {
//        qDebug() << "content: " << data;
//        //QByteArray datagramSend = "1:" + QByteArray::number(2) + ":apex:"+ hostName.toAscii() +":33:";
//        QByteArray datagramSend = "1:" + QByteArray::number(++m_packetNo) + ":apex:" + rapido_env().m_strHostName.toAscii() + ":"+QByteArray::number(qint32(IPMSG_RECVMSG))+":";
//        //QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
//        m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), senderIp, senderPort);

//        IpMsgRecvPacket* pPacket = new IpMsgRecvPacket(senderIp, senderPort, datagramSend);
//        emit newMsg(pPacket);

//        break;
//    }
//    case IPMSG_RECVMSG:
//        qDebug() << "Ok, he/she/it got my message." << strSenderIp;
//        break;
//    case IPMSG_READMSG:
//    {
//        qDebug() << "send to" << strSenderIp << "I have read it.";
//        //QByteArray datagramSend = "1:" + QByteArray::number(2) + ":apex:"+ hostName.toAscii() +":33:";
//        QByteArray datagramSend = "1:" + QByteArray::number(++m_packetNo) + ":apex:" + rapido_env().m_strHostName.toAscii() + ":"+QByteArray::number(qint32(IPMSG_ANSREADMSG))+":";
//        //QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
//        m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), senderIp, senderPort);
//        break;
//    }
//    case IPMSG_FEIQ_REMOTE_START_TYPING:	// FeiQ special.
//        qDebug() << strSenderIp << "is typing to you...";
//        break;
//    case IPMSG_FEIQ_REMOTE_KEEP_TYPING:
//        qDebug() << strSenderIp << "is still typing to you...";
//        break;
//    default:
//    {
//        qDebug() << "sender: " << strSenderIp << ":" << senderPort;
//        qDebug() << "content: " << data;
//        QTextCodec *codec = QTextCodec::codecForName("GBK");
//        QByteArray tmp(cmdList.at(5).toAscii());
//        qDebug() << "==> " << codec->toUnicode(tmp);
//        qDebug("Unknown command: 0x%02X", cmd);
//        break;
//    }
//    }
}


