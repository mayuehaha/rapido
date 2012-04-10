#include "ipmsg_protocol.h"

#include <QNetworkInterface>
#include <QHostInfo>
#include <QUdpSocket>
#include <QStringList>
#include <QDebug>

IpMsgProtocol::IpMsgProtocol(QObject *parent)
    :QObject(parent)
{
	m_packetNo = 1;
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
    //QMessageBox::information(NULL, "Title", "Content", QMessageBox, QMessageBox::Yes);
    //qDebug() << "Hello";

    //hostName = socket.gethostname()
    //ip = socket.gethostbyname(hostName)
    //QString hostName = QNetworkInterface::name();

    //QMessageBox::information(NULL, "Title", hostName, QMessageBox, QMessageBox::Yes);
    //qDebug() << hostName;

    QString strIp;
    QHostAddress hostIp;

	//QHostInfo hostInfo;
	QString hostName = QHostInfo::localHostName();//hostInfo.localHostName ();
	QHostInfo hostinfo = QHostInfo::fromName(hostName);;

	QList<QHostAddress> NetList = hostinfo.addresses();//QNetworkInterface::allAddresses();

    for(int Neti = 0; Neti < NetList.count(); Neti++)
    {
        strIp = NetList.at(Neti).toString();

		// skip IPV6
		if(-1 != strIp.indexOf("::"))
			continue;
		qDebug() << strIp;

		if(strIp.startsWith("127."))
            continue;

        hostIp = NetList.at(Neti);
		break;
    }

    if(hostIp.isNull())
	{
		qDebug() << "hostIp is Null.";
		return;
	}


    qDebug() << "My IP: " << hostIp.toString();

    qDebug() << "My Host Name: " << hostName;

    // Now we send some message to show me online.
    //m_pSocket = new QUdpSocket();
    //connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()), Qt::BlockingQueuedConnection);

    if(!m_socket.bind(hostIp, IPMSG_DEFAULT_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
    {
        qDebug() << "Cannot bind.";
        //delete m_pSocket;
        return;
    }

    //QByteArray datagram = "1:" + QByteArray::number(1) + ":apex:A-PC:1:ApexLiu";
	QByteArray datagram = "1:" + QByteArray::number(++m_packetNo) + ":apex:"+ hostName.toAscii() +":1:ApexLiu";
    //QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
    m_socket.writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, IPMSG_DEFAULT_PORT);

    //exec();

/*
    while (m_pSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_pSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_pSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        //processTheDatagram(datagram);
        QString a = sender.toString();
        QString b(datagram);
        qDebug() << "sender: " << a << ":" << senderPort;
        qDebug() << "content: " << b;
    }
*/
    //int a = 0;
}

void IpMsgProtocol::readPendingDatagrams()
{
	//static qint32 packet_no = 3;
	//packet_no++;

	while (m_socket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_socket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        if(-1 == m_socket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort))
            continue;

        //processTheDatagram(datagram);
        //qDebug() << "<<< " << sender.toString() << ":" << senderPort;
		QString strSenderIp = sender.toString();
		if(strSenderIp == "192.168.1.104")
            continue;

		QString data(datagram);
		//qDebug() << "sender: " << a << ":" << senderPort;
		//qDebug() << "content: " << data;

		QStringList cmdList = data.split(":");
//        for(int ci = 0; ci < c.count(); ci++)
//        {
//			QString d = c.at(ci);
//            qDebug() << c.at(ci);
//        }
		// sanity check
		if (cmdList.count() < R_IPMSG_NORMAL_FIELD_COUNT)
		{
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
			QByteArray datagramSend = "1:" + QByteArray::number(++m_packetNo) + ":apex:APEXPC:"+QByteArray::number(qint32(IPMSG_ANSENTRY))+":";
			//QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
			m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), sender, senderPort);
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
			//QTextCodec *codec = QTextCodec::codecForName("GBK");
			QTextCodec *codec = QTextCodec::codecForLocale();
			QByteArray tmp(cmdList.at(5).toAscii());//.toLocal8Bit());
			userName = codec->toUnicode(tmp);
			qDebug() << "==> " << codec->toUnicode(tmp);

			break;
		}
		case IPMSG_SENDMSG:
		{
			qDebug() << "content: " << data;
			//QByteArray datagramSend = "1:" + QByteArray::number(2) + ":apex:"+ hostName.toAscii() +":33:";
			QByteArray datagramSend = "1:" + QByteArray::number(++m_packetNo) + ":apex:APEXPC:"+QByteArray::number(qint32(IPMSG_RECVMSG))+":";
			//QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
			m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), sender, senderPort);
			break;
		}
		case IPMSG_RECVMSG:
			qDebug() << "Ok, he/she/it got my message." << strSenderIp;
			break;
		case IPMSG_READMSG:
		{
			//QByteArray datagramSend = "1:" + QByteArray::number(2) + ":apex:"+ hostName.toAscii() +":33:";
			QByteArray datagramSend = "1:" + QByteArray::number(++m_packetNo) + ":apex:APEXPC:"+QByteArray::number(qint32(IPMSG_ANSREADMSG))+":";
			//QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
			m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), sender, senderPort);
			break;
		}
		case IPMSG_FEIQ_REMOTE_START_TYPING:	// FeiQ special.
			qDebug() << strSenderIp << "is typing to you...";
			break;
		default:
		{
			//QString strCmd(QByteArray::number(cmd).toHex().data());
			//qDebug() << QString("Unknown command: 0x%1").arg(strCmd);
			//qDebug() << "Unknown command: 0x" << QByteArray::number(cmd).toHex();
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
