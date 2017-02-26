#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QtWidgets>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <inventory.h>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();
    bool getHasCreated();
    void createConnection(QString ip);
signals:
    void closeConnection();
    void sendData(QString data);

    void debugLog(QString data);

    void loadInventoryFromServer(QVector<QVector<Inventory::Items> > items);

public slots:
    void slotReadyRead   ();
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(QString data);
    void slotConnected   ();

private slots:
    void parseData(QString jsonString);
private:
    QTcpSocket* tcpSocket;
    quint16     nextBlockSize;
    bool hasCreated;

    QVector<QVector<Inventory::Items> > items;
};

#endif // CLIENT_H
