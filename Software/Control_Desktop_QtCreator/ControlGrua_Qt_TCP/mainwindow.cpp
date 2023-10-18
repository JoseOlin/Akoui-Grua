#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    heartbeatTimer = new QTimer();
    heartbeatTimer->setSingleShot(false);
    heartbeatTimer->setInterval(heartbeatPeriod_ms);
    heartbeatTimer->start();

#if CASA
    QString IP_akouiVert = "192.168.1.69"; //ESP-01
    QString IP_akouiHor = "192.168.1.70"; //NodeMCU Mini D1
#else
    QString IP_akouiHor  = "192.168.8.98";
    QString IP_akouiVert = "192.168.8.69";
#endif

    int port = 8888;

#if CASA
    akoui_ver = new TCPClient(IP_akouiVert, port);
    akoui_ver->setConnectedCheckBox(ui->hostVer_connected_chk);

    /*if(akoui_ver->isConnected())
    {
        ui->hostVer_connected_chk->setChecked(true);
        //ui->hostHor_connected_chk->set
    } else {
        ui->hostVer_connected_chk->setChecked(false);
    }*/

    connect(akoui_ver->socket,  SIGNAL(readyRead()),
            akoui_ver,          SLOT(onReadyRead())    );

    connect(akoui_ver->timer,   SIGNAL(timeout()),
            akoui_ver,          SLOT(sendDataIteratively())  );

     connect(akoui_ver->socket,  SIGNAL(connected()),
             akoui_ver, SLOT(getConnected())    );

     connect(akoui_ver->socket,  SIGNAL(disconnected()),
             akoui_ver, SLOT(getDisconnected())    );

     connect(heartbeatTimer, SIGNAL(timeout()),
             akoui_ver, SLOT(sendHeartbeat())    );

#endif

    akoui_hor = new TCPClient(IP_akouiHor, port);
    akoui_hor->setConnectedCheckBox(ui->hostHor_connected_chk);

    connect(akoui_hor->socket,  SIGNAL(readyRead()),
            akoui_hor,          SLOT(onReadyRead())    );

    connect(akoui_hor->timer,   SIGNAL(timeout()),
            akoui_hor,          SLOT(sendDataIteratively())  );

    connect(akoui_hor->socket,  SIGNAL(connected()),
            akoui_hor, SLOT(getConnected())    );

    connect(akoui_hor->socket,  SIGNAL(disconnected()),
            akoui_hor, SLOT(getDisconnected())    );

    connect(heartbeatTimer, SIGNAL(timeout()),
            akoui_hor, SLOT(sendHeartbeat())    );





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_moveLeft_btn_clicked()
{
    // Clicked = Pressed & Released.
}

void MainWindow::on_moveLeft_btn_pressed()
{
    if(akoui_hor->isConnected())
    {
        qDebug() << "Moving left...";
        QByteArray data = "<l>";
        akoui_hor->iterativeData = data;
        //qint64 bytesW = akoui_hor->sendData(data);
        //akoui_hor->timer->setTimerType(Qt::TimerType::PreciseTimer);
        akoui_hor->timer->start();
#if COMM_DEBUG
        //qDebug() << "Bytes writed" << bytesW;
#endif
    }
    else
    {
        qDebug() << "Akoui horizontal not connected";
    }
}
void MainWindow::on_moveLeft_btn_released()
{

    QByteArray data = "<S>";
    akoui_hor->iterativeData = data;
    if(akoui_hor->isConnected())
    {
        qDebug() << "moveLeft released. Stoping...";
        //QByteArray data = "<S>";
        akoui_hor->iterativeData = data;
        qint64 bytesW = akoui_hor->sendData(data);
    }
    else
    {
        qDebug() << "Akoui horizontal not connected on_moveLeft_btn_released()";
    }

    akoui_hor->timer->stop();
    qDebug() << "timer stopped";
}


void MainWindow::on_moveRight_btn_clicked()
{

}
void MainWindow::on_moveRight_btn_pressed()
{
    if(akoui_hor->isConnected())
    {
        qDebug() << "Moving right...";
        QByteArray data = "<r>";
        qint64 bytesW = akoui_hor->sendData(data); // Send the first time
        akoui_hor->iterativeData = data;
        akoui_hor->timer->start();
        //qDebug() << "Bytes writed" << bytesW;
    }
    else
    {
        qDebug() << "Akoui horizontal not connected";
    }
}
void MainWindow::on_moveRight_btn_released()
{
    if(akoui_hor->isConnected())
    {
        qDebug() << "Stoping...";
        QByteArray data = "<S>";
        akoui_hor->iterativeData = data;
        qint64 bytesW = akoui_hor->sendData(data);
    } else
    {

        qDebug() << "Akoui horizontal not connected on_moveRight_btn_released()";
    }
    akoui_hor->timer->stop();
    qDebug() << "timer stopped";
}


void MainWindow::on_moveUp_btn_clicked()
{
    // Clicked = Pressed & Released
}
void MainWindow::on_moveUp_btn_pressed()
{
    QByteArray data = "<u>";

    if(akoui_ver->isConnected())
    {
        qint64 bytesW = akoui_ver->sendData(data);
        akoui_ver->iterativeData = data;
        akoui_ver->timer->start();
    }
    else
    {
        qDebug() << "Akoui horizontal not connected moveUp_btn_pressed()";
    }
}
void MainWindow::on_moveUp_btn_released()
{
    if(akoui_ver->isConnected())
    {
        qDebug() << "Stoping...";
        QByteArray data = "<S>";
        akoui_ver->iterativeData = data;
        qint64 bytesW = akoui_ver->sendData(data);
    }
    else
    {
        qDebug() << "Akoui vertical not connected on_moveUp_btn_released()";
    }

    akoui_ver->timer->stop();
    qDebug() << "akoui_ver->timer stopped";

}


void MainWindow::on_moveDown_btn_pressed()
{
    QByteArray data = "<d>";

    if(akoui_ver->isConnected())
    {
        qint64 bytesW = akoui_ver->sendData(data);
        akoui_ver->iterativeData = data;
        akoui_ver->timer->start();
    }
    else
    {
        qDebug() << "Akoui vertical not connected";
    }

}
void MainWindow::on_moveDown_btn_released()
{
    if( akoui_ver->isConnected() )
    {
        qDebug() << "Stoping...";
        QByteArray data = "<S>";
        akoui_ver->iterativeData = data;
        qint64 bytesW = akoui_ver->sendData(data);
    }
    else
    {
        qDebug() << "Akoui vertical not connected on_moveUp_btn_released()";
    }

    akoui_ver->timer->stop();
    qDebug() << "akoui_ver->timer stopped";
}









