#ifndef SERVER_H
#define SERVER_H
#include <QtCore>
#include <QTcpServer>
#include <QDebug>
#include <QTcpSocket>
#include <QVector>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void createServer();
    ~Server();

    bool getHasCreated();
signals:
    void debugLog(QString data);

public slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void startListen(int port);
    void closeClientConnection();

private:
    QTcpServer* tcpServer;
    QMap<int, QTcpSocket*> Clients;
//    QTextEdit*  m_ptxt;
    quint16     nextBlockSize;

    void sendToClient(QTcpSocket* pSocket, const QString& str);
    void sendToAllClients(const QString& str);
    bool hasCreated;
};

#endif // SERVER_H
