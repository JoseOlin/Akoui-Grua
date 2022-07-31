#include "TcpClient.hpp"

TCPClient::TCPClient(QString IP, int port)
{
    this->IP = IP;
    this->port = port;
    socket = new QTcpSocket();

    socket->connectToHost(QHostAddress(IP), port);

    if(isConnected())
    {
        qDebug() << "Conexión exitosa";
    }
    else
    {
        qDebug() << "No se logró conectar";
    }

    timer = new QTimer();
    timer->setInterval(messagesPeriod_ms);

}

TCPClient::~TCPClient()
{
    delete socket;
    delete timer;
}



void TCPClient::onReadyRead()
{
    QByteArray data = socket->readAll();
#if COMM_DEBUG
    qDebug() << data;
    socket->write(QByteArray("ok !\n"));
#endif
}


qint64 TCPClient::sendData(QByteArray data)
{
#if COMM_DEBUG
    qDebug() << data;
#endif
    qint64 bytesWrited;
    bytesWrited = socket->write(data);

    return bytesWrited;
}

void TCPClient::sendDataIteratively()
{
#if COMM_DEBUG
    //qDebug() << "iterativeData: " << iterativeData;
#endif
    sendData(iterativeData);
}


bool TCPClient::isConnected()
{
    if( socket->ConnectedState == QAbstractSocket::SocketState::ConnectedState
        || socket->ConnectedState == QAbstractSocket::SocketState::BoundState
        || socket->ConnectedState == QAbstractSocket::SocketState::ListeningState)
    {
        return true;
    }
    return false;
}
