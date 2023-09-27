#include "TcpClient.hpp"

TCPClient::TCPClient(QString IP, int port)
{
    this->IP = IP;
    this->port = port;
    socket = new QTcpSocket();

    socket->connectToHost(QHostAddress(IP), port);
    connected_chk = new QCheckBox();

    if(isConnected())
    {
        qDebug() << "Conexión exitosa a " << this->IP;
    }
    else
    {
        qDebug() << "No se logró conectar " << this->IP;
    }

    timer = new QTimer();
    timer->setSingleShot(false);
    timer->setInterval(messagesPeriod_ms);

}

TCPClient::~TCPClient()
{
    socket->disconnectFromHost();
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

void TCPClient::sendHeartbeat()
{
    qint64 bytesWrited;
    bytesWrited = socket->write(hearbeatMsg);
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
    QAbstractSocket::SocketState estado;
    estado = socket->state();
    if( //socket->state() == QAbstractSocket::SocketState::ConnectedState

            estado == QTcpSocket::ConnectedState
         || estado == QTcpSocket::BoundState


        //|| socket->ConnectedState == QAbstractSocket::SocketState::ListeningState
      )
    {
        socketConnected = true;
        return true;
    }
    socketConnected = false;
    return false;
}

void TCPClient::setConnectedCheckBox(QCheckBox *connectd_chk)
{
    connected_chk = connectd_chk;
}

void TCPClient::getConnected()
{
    socketConnected = true;
    connected_chk->setChecked(true);
    qDebug() << IP << " se conectó";
}

void TCPClient::getDisconnected()
{
    socketConnected = false;
    connected_chk->setChecked(false);
    qDebug() << IP << " se desconectó";
}
