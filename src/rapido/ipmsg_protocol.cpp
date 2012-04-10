#include "ipmsg_protocol.h"

#include <QNetworkInterface>
#include <QHostInfo>
#include <QUdpSocket>
#include <QStringList>
#include <QDebug>

IpMsgProtocol::IpMsgProtocol(QObject *parent)
    :QObject(parent)
{

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
			continue;// != "127.0.0.1")
		{
		hostIp = NetList.at(Neti);
		break;
		}
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
	QByteArray datagram = "1:" + QByteArray::number(1) + ":apex:"+ hostName.toAscii() +":1:ApexLiu";
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
	static qint32 packet_no = 3;
	packet_no++;

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
        QString a = sender.toString();
		if(a == "192.168.1.105")
            continue;

		QString data(datagram);
        qDebug() << "sender: " << a << ":" << senderPort;
		qDebug() << "content: " << data;

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
		case IPMSG_SENDMSG:
		{
			//QByteArray datagramSend = "1:" + QByteArray::number(2) + ":apex:"+ hostName.toAscii() +":33:";
			QByteArray datagramSend = "1:" + QByteArray::number(packet_no) + ":apex:APEXPC:33:";
			//QByteArray datagram = "1_lbt2_0#128#000000000000#0#0#0:1333107614:apex:APEXPC:6291459:\261\312\274";
			m_socket.writeDatagram(datagramSend.data(), datagramSend.size(), sender, senderPort);
		}
			break;
		default:
		{
			//QString strCmd(QByteArray::number(cmd).toHex().data());
			//qDebug() << QString("Unknown command: 0x%1").arg(strCmd);
			//qDebug() << "Unknown command: 0x" << QByteArray::number(cmd).toHex();
			qDebug("Unknown command: 0x%02X", cmd);
			break;
		}
		}
    }
}
