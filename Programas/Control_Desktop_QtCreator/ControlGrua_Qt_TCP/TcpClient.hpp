#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QDebug>

#define COMM_DEBUG 1

class TCPClient : public QObject // La clase debe heredar de QObject para poder hacer conexiones.
{
    Q_OBJECT // Y agregar el Q_OBJECT
public:
    TCPClient(QString IP, int port);
    ~TCPClient();

    bool isConnected();
    QTcpSocket *socket; // Needs to be public to connect
    QTimer *timer;
    QByteArray iterativeData;

public slots:
    void onReadyRead();
    //void enviarValoresTCP();
    qint64 sendData(QByteArray data);
    void sendDataIteratively();

private:
    QString IP;
    int port;
    int messagesPeriod_ms = 150;
};

#endif // TCPCLIENT_HPP
