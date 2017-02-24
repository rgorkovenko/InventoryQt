#ifndef SERVER_H
#define SERVER_H
#include <QtCore>
#include <QTcpServer>
#include <QDebug>
#include <QTcpSocket>


class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
signals:

public slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void startListen(int port);
private:
    QTcpServer* tcpServer;
//    QTextEdit*  m_ptxt;
    quint16     nextBlockSize;

    void sendToClient(QTcpSocket* pSocket, const QString& str);

};

#endif // SERVER_H
