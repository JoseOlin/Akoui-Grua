#include "mainwindow.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    /*QWidget* w = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    QPushButton* up = new QPushButton("Arriba");
    QPushButton* down = new QPushButton("Abajo");
    layout->addWidget(up);
    layout->addWidget(down);
    w->setLayout(layout);

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QObject::connect(up, &QPushButton::pressed,
                         [manager](){
            manager->get(QNetworkRequest(QUrl("http://192.168.1.69/bajar/1")));
            cout << "Subiendo..." << endl;
        });

    QObject::connect(up, &QPushButton::released,
                         [manager](){
            manager->get(QNetworkRequest(QUrl("http://192.168.1.69/bajar/0")));
            cout << "Bajando..." << endl;
        });
    w->show();*/
    w.show();
    return a.exec();
}


void desplegar()
{

}
