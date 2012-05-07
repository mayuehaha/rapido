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
	// 产生一个随机数，作为第一个发送的消息包的序号，在全局范围内，此序号是递增的。
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	m_packetNo = qrand() % 1024;

	// !! DO NOT use Qt::BlockingQueuedConnection, otherwise you'll got an exception.
	//connect(&m_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()), Qt::BlockingQueuedConnection);
	connect(&m_socket, SIGNAL(readyRead()), this, SLOT(_ReadPendingDatagrams()));
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

	// 通知大家我们上线了. :)
	_BroadcastOnlineMessage();
}

void IpMsgProtocol::_BroadcastOnlineMessage()
{
	//quint32 flags = IPMSG_BR_ENTRY;// | IPMSG_FILEATTACHOPT;

<<<<<<< HEAD
	//QHostAddress mytest = QHostAddress::Broadcast;
	//QHostAddress mytest = QHostAddress("192.168.4.29");
	IpMsgSendPacket *broadcast = new IpMsgSendPacket(QHostAddress::Broadcast,
						IPMSG_DEFAULT_PORT, rapido::entryMessage, "", flags);
    broadcast->send();
=======
    //QHostAddress mytest = QHostAddress::Broadcast;
	//QHostAddress mytest = QHostAddress(rapido_env().m_hostIp.toString());
	//IpMsgSendPacket *packet = new IpMsgSendPacket(QHostAddress::Broadcast, IPMSG_DEFAULT_PORT, rapido::entryMessage, "", flags);
	IpMsgSendPacket *packet = new IpMsgSendPacket(QHostAddress::Broadcast, IPMSG_BR_ENTRY);
	SendPacket(packet);
>>>>>>> 229d281586472bab07b0d529e012c0eafdf7c10d
}

void IpMsgProtocol::_ProcessSendMessage()
{
<<<<<<< HEAD
	for (int i = 0; i < rapido::sendPacketList.size(); ++i) {

		_handleMsg(rapido::sendPacketList.at(i));
=======
	QMutexLocker locker(&m_SendPacketLock);

	IpMsgSendPacket* pPacket = NULL;
	for (int i = 0; i < m_SendPackets.size(); )
	{
		pPacket = m_SendPackets.at(i);

		if(pPacket->IsSendFailed())
		{
			// 将发送失败的消息包干掉
			// TODO: 同时在对应的聊天窗口中显示对方已离线的提示
			m_SendPackets.removeAt(i);
			continue;
		}

		//handleMsg(rapido::sendPacketList.at(i));
		_SendPacket(pPacket);

		// 如果是广播消息，则无需确定对方是否收到，直接从列表中干掉。
		switch(pPacket->getCommand())
		{
		case IPMSG_BR_ENTRY:
		case IPMSG_BR_EXIT:
		case IPMSG_BR_ABSENCE:
			m_SendPackets.removeAt(i);
			continue;
		}

		pPacket->UpdateSendFlag();
		++i;
>>>>>>> 229d281586472bab07b0d529e012c0eafdf7c10d
	}
}

//can it be run without trouble with the object not the point
<<<<<<< HEAD
void IpMsgProtocol::_handleMsg(const IpMsgSendPacket* send_packet)
{
=======
//void IpMsgProtocol::handleMsg(const IpMsgSendPacket* send_packet)
void IpMsgProtocol::_SendPacket(const IpMsgSendPacket* send_packet)
{
	qDebug() << "Send Out Message:" << send_packet->getIp() << ":" <<send_packet->getPacket();
>>>>>>> 229d281586472bab07b0d529e012c0eafdf7c10d
    m_socket.writeDatagram(send_packet->getPacket().toLocal8Bit().data(), send_packet->getPacket().size(),
						   send_packet->getIpAddress(), IPMSG_DEFAULT_PORT);
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

void IpMsgProtocol::_ReadPendingDatagrams()
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

		//QString strPacket = toUnicode(datagram);
		//qDebug() << "received:" << strPacket;
		IpMsgRecvPacket* pPacket = new IpMsgRecvPacket(senderIp, datagram);

		_ProcessRecvMessage(pPacket);

		// After the packet has been processed, decrease reference count of this packet.
		// If nobody using this packet, it will be delete automatically.
<<<<<<< HEAD
		pPacket->delRef();

        //check the return value
//        if(recvPacket == NULL){
//            qDebug() << "erro formate, Packet:" <<  data;
//        }
=======
		pPacket->Release();
>>>>>>> 229d281586472bab07b0d529e012c0eafdf7c10d
    }
}

void IpMsgProtocol::_ProcessRecvMessage(const IpMsgRecvPacket* recvPacket)
{
	switch (IPMSG_GET_MODE(recvPacket->getFlags()))
	{
<<<<<<< HEAD
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
=======
	case IPMSG_BR_ENTRY:	// 有人广播说自己上线了
	{
		//rapido::userList.append(recvPacket->getPacketUser());
		IpMsgSendPacket *anserPacket = new IpMsgSendPacket(recvPacket->getIpAddress(), rapido::entryMessage, "", IPMSG_ANSENTRY);
		//anserPacket->send();
		rapido_ipmsg_thread().SendPacket(anserPacket);
		break;
	}
	case IPMSG_BR_EXIT:		// 有人广播说自己要下线了
		break;

	case IPMSG_ANSENTRY:	// 自己广播说上线了，别人回应说他已经在线了
		//rapido::userList.append(recvPacket->getPacketUser());
		break;

	case IPMSG_BR_ABSENCE:	// 有人广播说自己暂时离开了
		// XXX TODO: support it
		break;

	case IPMSG_SENDMSG:	// 收到一个对方发过来的消息
	{
		if (IPMSG_GET_OPT(recvPacket->getFlags()) & IPMSG_SENDCHECKOPT)
		{
			IpMsgSendPacket *checkOptPacket = new IpMsgSendPacket(recvPacket->getIpAddress(), recvPacket->getPacketNoString(), "",  IPMSG_RECVMSG);
			//checkOptPacket->send();
			rapido_ipmsg_thread().SendPacket(checkOptPacket);
		}

		IpMsgSendPacket *rebackTest = new IpMsgSendPacket(recvPacket->getIpAddress(),
														  recvPacket->getPacketNoString(), "", IPMSG_SENDMSG | IPMSG_SENDCHECKOPT);
		//rebackTest->send();
		rapido_ipmsg_thread().SendPacket(rebackTest);

		//            // If sender is not in our user list, add it.
		//            if (!Global::userManager->contains(msg->ip())) {
		//                emit newUserMsg(msg);
		//            }
		break;
	}
	case IPMSG_READMSG:		// 对方说如果我们查看了消息，给他一个响应。
		qDebug() << "some guys READMSG";
		//processRecvReadMsg(msg);
		break;

	case IPMSG_ANSREADMSG:	// 我们要求对方查看了消息后给个响应，这就是对方的响应。
		break;
	case IPMSG_RECVMSG:		// 对方证实收到我们发送的消息
		// TODO: 对方收到我们的消息，会将该消息的ID发回来，收到此消息后根据ID将待发送列表(m_SendPackets)中的对应的消息移除，不用再尝试发送。
		break;
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
>>>>>>> 229d281586472bab07b0d529e012c0eafdf7c10d
}

void IpMsgProtocol::SendPacket(IpMsgSendPacket *pPacket)
{
	/// locker析构时会解锁。
	QMutexLocker locker(&m_SendPacketLock);

	m_SendPackets.append(pPacket);
}
