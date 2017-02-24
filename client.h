#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QtWidgets>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

signals:
    void sendData(QString data);

public slots:
    void slotReadyRead   ();
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(QString data);
    void slotConnected   ();

private:
    QTcpSocket* tcpSocket;
//    QTextEdit*  m_ptxtInfo;
//    QLineEdit*  m_ptxtInput;
    quint16     nextBlockSize;
};

#endif // CLIENT_H
