#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
  , nextBlockSize(0)
{
    hasCreated = false;
}
void Server::createServer(){
    tcpServer = new QTcpServer(this);
    connect(tcpServer, tcpServer->newConnection, this, slotNewConnection);
    hasCreated = true;
}

Server::~Server()
{
    foreach(int i,Clients.keys()){
        Clients[i]->close();
        Clients.remove(i);
    }
    tcpServer->close();
    qDebug() << QString("Сервер остановлен!!!");
}

bool Server::getHasCreated()
{
    return hasCreated;
}

void Server::startListen(int port){
    if (!tcpServer->listen(QHostAddress::Any, port)) {
//        qDebug() << QString("Server Error, Unable to start the server: %1").arg(tcpServer->errorString());
        debugLog(QString("Server Error, Unable to start the server: %1").arg(tcpServer->errorString()));
        tcpServer->close();
        return;
    }
    debugLog(QString("Server was started in port: %1").arg(QString::number(port)));
    qDebug() << QString("Server was started in port: %1").arg(QString::number(port));
}

void Server::closeClientConnection()
{
    QTcpSocket *pClientSocket = (QTcpSocket*)sender();
    int idusersocs=pClientSocket->socketDescriptor();

    int removeId;
    //находим индекс клиента по его дескриптору
    foreach(int i,Clients.keys()){
        if (Clients[i]->socketDescriptor() == idusersocs){
            removeId = i;
            break;
        }
    }

    pClientSocket->close();
    Clients.remove(removeId);
    debugLog(QString::number(Clients.count()));
}

/*virtual*/ void Server::slotNewConnection()
{
    QTcpSocket *pClientSocket = tcpServer->nextPendingConnection();
    int idusersocs=pClientSocket->socketDescriptor();

    Clients[idusersocs]=pClientSocket;
    connect(Clients[idusersocs],SIGNAL(readyRead()),this, SLOT(slotReadClient()));
    connect(Clients[idusersocs], SIGNAL(disconnected()), this, SLOT(closeClientConnection()));

    sendToClient(pClientSocket, "Server Response: Connected! You id: " + QString::number(idusersocs));
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
        //получили данные от клиента
        QString str;
        in >> str;
        nextBlockSize = 0;
        //рассылаем данные клиентам
        sendToAllClients(str);
    }
}

void Server::sendToClient(QTcpSocket *pSocket, const QString &str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
    pSocket->flush();
    qDebug() << str;
}

void Server::sendToAllClients(const QString &str)
{
    debugLog(QString::number(Clients.count()));
    foreach (int id, Clients.keys()) {
        sendToClient(Clients[id], str);
    }
}
