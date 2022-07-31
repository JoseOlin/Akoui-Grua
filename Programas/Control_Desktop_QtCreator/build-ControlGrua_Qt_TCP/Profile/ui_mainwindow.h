/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *moveUp_btn;
    QPushButton *moveDown_btn;
    QSlider *verticalSlider;
    QSlider *horizontalSlider;
    QPushButton *moveLeft_btn;
    QPushButton *moveRight_btn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(343, 428);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        moveUp_btn = new QPushButton(centralwidget);
        moveUp_btn->setObjectName(QString::fromUtf8("moveUp_btn"));
        moveUp_btn->setGeometry(QRect(100, 30, 91, 101));
        moveDown_btn = new QPushButton(centralwidget);
        moveDown_btn->setObjectName(QString::fromUtf8("moveDown_btn"));
        moveDown_btn->setGeometry(QRect(100, 240, 91, 91));
        verticalSlider = new QSlider(centralwidget);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(290, 230, 16, 121));
        verticalSlider->setValue(50);
        verticalSlider->setOrientation(Qt::Vertical);
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(120, 370, 160, 16));
        horizontalSlider->setValue(50);
        horizontalSlider->setOrientation(Qt::Horizontal);
        moveLeft_btn = new QPushButton(centralwidget);
        moveLeft_btn->setObjectName(QString::fromUtf8("moveLeft_btn"));
        moveLeft_btn->setGeometry(QRect(10, 150, 111, 71));
        moveRight_btn = new QPushButton(centralwidget);
        moveRight_btn->setObjectName(QString::fromUtf8("moveRight_btn"));
        moveRight_btn->setGeometry(QRect(160, 150, 111, 71));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 343, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        moveUp_btn->setText(QApplication::translate("MainWindow", "Subir", nullptr));
        moveDown_btn->setText(QApplication::translate("MainWindow", "Bajar", nullptr));
        moveLeft_btn->setText(QApplication::translate("MainWindow", "Left", nullptr));
        moveRight_btn->setText(QApplication::translate("MainWindow", "Right", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
