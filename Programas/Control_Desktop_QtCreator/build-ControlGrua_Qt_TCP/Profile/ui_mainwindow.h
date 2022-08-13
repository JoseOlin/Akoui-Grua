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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGridLayout *gridLayout;
    QPushButton *moveUp_btn;
    QPushButton *moveDown_btn;
    QPushButton *moveRight_btn;
    QPushButton *moveLeft_btn;
    QCheckBox *hostHor_connected_chk;
    QCheckBox *hostVer_connected_chk;
    QSlider *horizontalSlider;
    QPushButton *emergencyStop_btn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(331, 439);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pushButton);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        formLayout->setWidget(3, QFormLayout::FieldRole, pushButton_2);


        verticalLayout->addLayout(formLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        moveUp_btn = new QPushButton(centralwidget);
        moveUp_btn->setObjectName(QString::fromUtf8("moveUp_btn"));
        moveUp_btn->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(moveUp_btn, 1, 1, 1, 1);

        moveDown_btn = new QPushButton(centralwidget);
        moveDown_btn->setObjectName(QString::fromUtf8("moveDown_btn"));
        moveDown_btn->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(moveDown_btn, 3, 1, 1, 1);

        moveRight_btn = new QPushButton(centralwidget);
        moveRight_btn->setObjectName(QString::fromUtf8("moveRight_btn"));
        moveRight_btn->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(moveRight_btn, 2, 2, 1, 1);

        moveLeft_btn = new QPushButton(centralwidget);
        moveLeft_btn->setObjectName(QString::fromUtf8("moveLeft_btn"));
        moveLeft_btn->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(moveLeft_btn, 2, 0, 1, 1);

        hostHor_connected_chk = new QCheckBox(centralwidget);
        hostHor_connected_chk->setObjectName(QString::fromUtf8("hostHor_connected_chk"));

        gridLayout->addWidget(hostHor_connected_chk, 0, 2, 1, 1);

        hostVer_connected_chk = new QCheckBox(centralwidget);
        hostVer_connected_chk->setObjectName(QString::fromUtf8("hostVer_connected_chk"));

        gridLayout->addWidget(hostVer_connected_chk, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setValue(50);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        emergencyStop_btn = new QPushButton(centralwidget);
        emergencyStop_btn->setObjectName(QString::fromUtf8("emergencyStop_btn"));
        emergencyStop_btn->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(emergencyStop_btn);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 331, 22));
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
        label->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        moveUp_btn->setText(QApplication::translate("MainWindow", "Subir", nullptr));
        moveDown_btn->setText(QApplication::translate("MainWindow", "Bajar", nullptr));
        moveRight_btn->setText(QApplication::translate("MainWindow", "Right", nullptr));
        moveLeft_btn->setText(QApplication::translate("MainWindow", "Left", nullptr));
        hostHor_connected_chk->setText(QApplication::translate("MainWindow", "Host Hor Con", nullptr));
        hostVer_connected_chk->setText(QApplication::translate("MainWindow", "Host Ver Con", nullptr));
        emergencyStop_btn->setText(QApplication::translate("MainWindow", "Emergency Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
