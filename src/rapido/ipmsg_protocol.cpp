#include "ipmsg_protocol.h"

#include <QNetworkInterface>
#include <QHostInfo>
#include <QUdpSocket>
#include <QStringList>
#include <QDebug>

#include "global.h"
#include "ipmsg_const.h"
#include "ipmsg_packet.h"

/*
command:
  1:123:apex:APEXPC:1:ApexLiu
format:
  packet-version : packet-number : login-name : computer-name (or host-name) : command : user-name
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

    //why can't get message with the first message
    //if(!m_socket.bind(rapido_env().m_hostIp, IPMSG_DEFAULT_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
    if(!m_socket.bind(QHostAddress::Any, IPMSG_DEFAULT_PORT))
	{
        qDebug() << "Cannot bind.";
        return;
    }

    // broadcast that I'm online. :)
	_broadcastOnlineMessage();
}

void IpMsgProtocol::_broadcastOnlineMessage()
{
    quint32 flags = 0;
	flags |= IPMSG_BR_ENTRY | IPMSG_FILEATTACHOPT;

	//QHostAddress mytest = QHostAddress::Broadcast;
	//QHostAddress mytest = QHostAddress("192.168.4.29");
	IpMsgSendPacket *broadcast = new IpMsgSendPacket(QHostAddress::Broadcast,
						IPMSG_DEFAULT_PORT, rapido::entryMessage, "", flags);
    broadcast->send();
}

void IpMsgProtocol::processSendMsg()
{
	for (int i = 0; i < rapido::sendPacketList.size(); ++i) {

		_handleMsg(rapido::sendPacketList.at(i));
	}
	rapido::sendPacketList.clear();
}

//can it be run without trouble with the object not the point
void IpMsgProtocol::_handleMsg(const IpMsgSendPacket* send_packet)
{
    m_socket.writeDatagram(send_packet->getPacket().toLocal8Bit().data(), send_packet->getPacket().size(),
                           send_packet->getIpAddress(), send_packet->getPort());
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

		// skip message which broadcast from myself.
		if(senderIp == rapido_env().m_hostIp)
		{
			qDebug() << "message from myself, skip.";
			continue;
		}

		QString strPacket = toUnicode(datagram);
		qDebug() << "resive:" << strPacket;
		IpMsgRecvPacket* pPacket = new IpMsgRecvPacket(senderIp, senderPort, strPacket);
		_processRecvMessage(pPacket);

		// After the packet has been processed, decrease reference count of this packet.
		// If nobody using this packet, it will be delete automatically.
		pPacket->delRef();

        //check the return value
//        if(recvPacket == NULL){
//            qDebug() << "erro formate, Packet:" <<  data;
//        }
    }
}

void IpMsgProtocol::_processRecvMessage(const IpMsgRecvPacket* recvPacket)
{
	switch (IPMSG_GET_MODE(recvPacket->getFlags()))
	{
        case IPMSG_BR_ENTRY:
        {
			rapido::userList.append(recvPacket->getPacketUser());
			IpMsgSendPacket *anserPacket = new IpMsgSendPacket(recvPacket->getIpAddress(), recvPacket->getPort(),
									rapido::entryMessage, "", IPMSG_ANSENTRY);
			anserPacket->send();
			//emit onUserOnline(recvPacket->getPacketUser().getLoginName(), recvPacket->getIp());
			break;
        }
		case IPMSG_BR_EXIT:
			break;

		case IPMSG_ANSENTRY:
		{
			//emit onUserOnline(recvPacket->getPacketUser().getName(), recvPacket->getIp());
			rapido::userList.append(recvPacket->getPacketUser());
			//qDebug() << recvPacket->getPacketUser().getName()<< ":" << recvPacket->getIp();
			qDebug() << recvPacket->getIp();
			QString strUserNam1("hehehe");
			QString strUserNam2("11111");
			emit onUserOnline(strUserNam1 ,strUserNam2);
			break;
		}
        case IPMSG_BR_ABSENCE:
            // XXX TODO: support it
            break;

        case IPMSG_SENDMSG:
        {
			if (IPMSG_GET_OPT(recvPacket->getFlags()) & IPMSG_SENDCHECKOPT) {
				IpMsgSendPacket *checkOptPacket = new IpMsgSendPacket(recvPacket->getIpAddress(), recvPacket->getPort(),recvPacket->getPacketNoString(), "",  IPMSG_RECVMSG);
                checkOptPacket->send();
            }

			IpMsgSendPacket *rebackTest = new IpMsgSendPacket(recvPacket->getIpAddress(), recvPacket->getPort(),
												   recvPacket->getPacketNoString(), "", IPMSG_SENDMSG | IPMSG_SENDCHECKOPT);
            rebackTest->send();

//            // If sender is not in our user list, add it.
//            if (!Global::userManager->contains(msg->ip())) {
//                emit newUserMsg(msg);
//            }
            break;
        }
        case IPMSG_READMSG:
            qDebug() << "some guys READMSGr";
            //processRecvReadMsg(msg);
            break;

        case IPMSG_ANSREADMSG:
        case IPMSG_RECVMSG:
        case IPMSG_DELMSG:
            // do nothing
            // XXX TODO: do something?????????
            break;

        case IPMSG_RELEASEFILES:
            //processRecvReleaseFilesMsg(msg);
            break;

        default:
        {
          //  qDebug() << "sender: " << recvPacket.getIp() << ":" << recvPacket.getPort();
          //  qDebug() << "content: " << recvPacket.getPacket();
            break;
        }
    }
}

void IpMsgProtocol::AddForSend(IpMsgSendPacket *pPacket)
{
	m_SendPacketLocker.lock();
	m_SendPackets.append(pPacket);
}
