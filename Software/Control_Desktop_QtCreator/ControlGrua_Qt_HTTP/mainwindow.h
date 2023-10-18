#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
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


private slots:
    void on_btnSubir_clicked();
    void on_btnSubir_pressed();
    void on_btnSubir_released();
    void on_btnBajar_pressed();
    void on_btnBajar_released();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;

    QString IP;
};
#endif // MAINWINDOW_H
