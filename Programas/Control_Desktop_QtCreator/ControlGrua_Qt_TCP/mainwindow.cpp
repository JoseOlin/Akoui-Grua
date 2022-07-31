#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QString IP_akouiVer = "192.168.1.69";
    QString IP_akouiHor = "192.168.1.70";
    int port = 8888;

    akoui_hor = new TCPClient(IP_akouiHor, port);
    //akoui_ver = new TCPClient(IP_akouiVer, port);

    //manager = new QNetworkAccessManager();
    connect(akoui_hor->socket,  SIGNAL(readyRead()),
            akoui_hor,          SLOT(onReadyRead())    );

    connect(akoui_hor->timer,   SIGNAL(timeout()),
            akoui_hor,          SLOT(sendDataIteratively())  );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_moveLeft_btn_pressed()
{
    if(akoui_hor->isConnected())
    {
        qDebug() << "Moving left...";
        QByteArray data = "<l>";
        akoui_hor->iterativeData = data;
        //qint64 bytesW = akoui_hor->sendData(data);
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
    akoui_hor->timer->stop();
    qDebug() << "timer stopped";
}

void MainWindow::on_moveRight_btn_pressed()
{
    if(akoui_hor->isConnected())
    {
        qDebug() << "Moving right...";
        QByteArray data = "<r>";
        //qint64 bytesW = akoui_hor->sendData(data);
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
    akoui_hor->timer->stop();
    qDebug() << "timer stopped";
}




void MainWindow::on_moveUp_btn_pressed()
{
    //QString url = IP + "/subir/1";

    //manager->get(QNetworkRequest(QUrl("http://192.168.1.69/subir/1")));
    //manager->get(QNetworkRequest(QUrl(url)));
    //cout << "Subiendo..." << endl;
    if(akoui_ver->isConnected())
    {
        qDebug() << "Moving up..." << endl;
        QByteArray data = "u";
        akoui_ver->sendData(data);
    }
    else
    {
         qDebug() << "Akoui vertical not connected" << endl;
    }
}

void MainWindow::on_moveUp_btn_released()
{

    //QString url = IP + "/subir/0";

    //manager->get(QNetworkRequest(QUrl("http://192.168.1.69/subir/0")));
    //manager->get(QNetworkRequest(QUrl(url)));
    //manager->get(QNetworkRequest(QUrl(url)));
    //cout << "Deteniendo subida..." << endl;
}

void MainWindow::on_moveDown_btn_pressed()
{
    /*QString url = IP + "/bajar/1";

    manager->get(QNetworkRequest(QUrl(url)));
    cout << "Bajar..." << endl;*/

    qDebug() << "Moving down..." << endl;
    QByteArray data = "d";
    akoui_ver->sendData(data);

}

void MainWindow::on_moveDown_btn_released()
{
    /*QString url = IP + "/bajar/0";
    manager->get(QNetworkRequest(QUrl(url)));
    manager->get(QNetworkRequest(QUrl(url)));

    cout << "Detener bajada..." << endl;*/
}




