#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TcpClient.hpp"

#define CASA 1

//#include <QTcpSocket>
//#include <QNetworkAccessManager>
//#include <QNetworkRequest>

#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *heartbeatTimer;
    int heartbeatPeriod_ms = 2000;

private slots:
    //    void on_btnSubir_clicked();
    void on_moveUp_btn_clicked();
    void on_moveUp_btn_pressed();
    void on_moveUp_btn_released();

    void on_moveDown_btn_pressed();
    void on_moveDown_btn_released();

    void on_moveLeft_btn_clicked();
    void on_moveLeft_btn_pressed();
    void on_moveLeft_btn_released();

    void on_moveRight_btn_clicked();
    void on_moveRight_btn_pressed();
    void on_moveRight_btn_released();


private:
    Ui::MainWindow *ui;
    //QNetworkAccessManager *manager = new QNetworkAccessManager();
    //QNetworkRequest request;


    TCPClient *akoui_hor;
    TCPClient *akoui_ver;

};
#endif // MAINWINDOW_H
