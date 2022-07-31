#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    IP = "http://192.168.1.76";

    manager = new QNetworkAccessManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSubir_clicked()
{

}

void MainWindow::on_btnSubir_pressed()
{
    QString url = IP + "/subir/1";

    //manager->get(QNetworkRequest(QUrl("http://192.168.1.69/subir/1")));
    manager->get(QNetworkRequest(QUrl(url)));
    cout << "Subiendo..." << endl;
}

void MainWindow::on_btnSubir_released()
{
    QString url = IP + "/subir/0";

    //manager->get(QNetworkRequest(QUrl("http://192.168.1.69/subir/0")));
    manager->get(QNetworkRequest(QUrl(url)));
    manager->get(QNetworkRequest(QUrl(url)));
    cout << "Deteniendo subida..." << endl;
}

void MainWindow::on_btnBajar_pressed()
{
    QString url = IP + "/bajar/1";

    manager->get(QNetworkRequest(QUrl(url)));
    cout << "Bajar..." << endl;
}

void MainWindow::on_btnBajar_released()
{
    QString url = IP + "/bajar/0";
    manager->get(QNetworkRequest(QUrl(url)));
    manager->get(QNetworkRequest(QUrl(url)));

    cout << "Detener bajada..." << endl;
}
