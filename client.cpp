#include "client.h"
#include <QAbstractSocket>

Client::Client(QObject *parent) : QObject(parent)
{
    hasCreated = false;
}

Client::~Client()
{
    closeConnection();
}

bool Client::getHasCreated()
{
    return hasCreated;
}

void Client::createConnection(QString ip){
    tcpSocket = new QTcpSocket(this);

    tcpSocket->connectToHost(ip, 6666);

    connect(tcpSocket, tcpSocket->connected, this, slotConnected);
    connect(tcpSocket, tcpSocket->readyRead, this, slotReadyRead);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

    connect(this, sendData, this, slotSendToServer);

    hasCreated = true;
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
        QString str;
        in >> str;

        nextBlockSize = 0;

        debugLog(str);
        parseData(str);
    }
}

void Client::parseData(QString jsonString){

    QJsonDocument document = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray array = document.array();

    //выходим если пришел не массив
    if(array.count() == 0){
        return;
    }
    debugLog(jsonString);
    //очищаем данные перед заполнением
    items.clear();
    for(int i = 0; i < array.count(); i++){
        QJsonArray row = array[i].toArray();
        QVector<Inventory::Items> itemsRow;
        for(int j = 0; j < row.count(); j++){
            QJsonObject object = row[j].toObject();
            Inventory::Items item;
            item.count = object["Count"].toInt();
            item.name = object["Name"].toString();
            itemsRow.append(item);
        }
        items.append(itemsRow);
    }

    loadInventoryFromServer(items);
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

    hasCreated = false;
    debugLog(strError);
//    qDebug() << strError;
}

void Client::slotSendToServer(QString data)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << data;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    tcpSocket->write(arrBlock);
}

void Client::slotConnected()
{
    debugLog(QString("Received the connected() signal"));
}
