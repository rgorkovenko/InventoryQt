#include "client.h"
#include <QAbstractSocket>

Client::Client(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);

    tcpSocket->connectToHost(QString("localhost"), 6666);

    connect(tcpSocket, tcpSocket->connected, this, slotConnected);
    connect(tcpSocket, tcpSocket->readyRead, this, slotReadyRead);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

    connect(this, sendData, this, slotSendToServer);
}

void Client::slotReadyRead()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_8);
    for (;;) {
        if (!nextBlockSize) {
            if (tcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> nextBlockSize;
        }

        if (tcpSocket->bytesAvailable() < nextBlockSize) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;

//        m_ptxtInfo->append(time.toString() + " " + str);
        nextBlockSize = 0;
        qDebug() << time << str;
    }
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError = QString("Error: ") + (err == QAbstractSocket::HostNotFoundError ?
             QString("The host was not found.") :
             err == QAbstractSocket::RemoteHostClosedError ?
             QString("The remote host is closed.") :
             err == QAbstractSocket::ConnectionRefusedError ?
             QString("The connection was refused.") :
             QString(tcpSocket->errorString())
            );
    qDebug() << strError;
}

void Client::slotSendToServer(QString data)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << QTime::currentTime() << data;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    tcpSocket->write(arrBlock);
}

void Client::slotConnected()
{
    qDebug() << QString("Received the connected() signal");
}
