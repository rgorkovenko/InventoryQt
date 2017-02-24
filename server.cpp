#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
  , nextBlockSize(0)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, tcpServer->newConnection, this, slotNewConnection);
}

void Server::startListen(int port){
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << QString("Server Error, Unable to start the server: %1").arg(tcpServer->errorString());
        tcpServer->close();
        return;
    }
    qDebug() << QString("Server was started in port: %1").arg(QString::number(port));
}

/*virtual*/ void Server::slotNewConnection()
{
    QTcpSocket *pClientSocket = tcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    sendToClient(pClientSocket, "Server Response: Connected!");
}

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_8);
    for (;;) {
        if (!nextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> nextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < nextBlockSize) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;

        QString strMessage =
            time.toString() + " " + "Client has sended - " + str;
//        m_ptxt->append(strMessage);
        qDebug() << strMessage;

        nextBlockSize = 0;

        sendToClient(pClientSocket,
                     "Server Response: Received \"" + str + "\""
                    );
    }
}

void Server::sendToClient(QTcpSocket *pSocket, const QString &str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
