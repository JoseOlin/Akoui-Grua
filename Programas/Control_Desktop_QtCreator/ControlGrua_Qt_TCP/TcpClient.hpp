#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QDebug>
#include <QCheckBox>

#define COMM_DEBUG 1

class TCPClient : public QObject // La clase debe heredar de QObject para poder hacer conexiones.
{
    Q_OBJECT // Y agregar el Q_OBJECT
public:
    TCPClient(QString IP, int port);
    ~TCPClient();

    QTcpSocket *socket; // Needs to be public to connect
    QTimer *timer;
    QByteArray iterativeData;

    bool isConnected();
public slots:
    void setConnectedCheckBox(QCheckBox* connectd_chk);
    void onReadyRead();
    //void enviarValoresTCP();
    qint64 sendData(QByteArray data);
    void sendDataIteratively();
    void getConnected();
    void getDisconnected();
private:
    QString IP;
    int port;
    int messagesPeriod_ms = 80;
    bool socketConnected = false;
    QCheckBox *connected_chk;
};

#endif // TCPCLIENT_HPP
