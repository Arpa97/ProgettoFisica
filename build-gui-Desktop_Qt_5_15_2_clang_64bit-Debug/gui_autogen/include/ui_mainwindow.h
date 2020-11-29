/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
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
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSlider *windSpeed;
    QLabel *label_3;
    QDial *windDir;
    QLabel *label_4;
    QLineEdit *xfire;
    QLineEdit *yfire;
    QLabel *xfirelabel;
    QLabel *yfirelabel;
    QLabel *windSpeedLabel;
    QLabel *windDirLabel;
    QMenuBar *menubar;
    QMenu *menuMainwindow;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 40, 400, 400));
        label->setAutoFillBackground(false);
        label->setFrameShape(QFrame::Panel);
        label->setPixmap(QPixmap(QString::fromUtf8(":/white.png")));
        label->setScaledContents(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 450, 91, 23));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 210, 161, 23));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(430, 450, 121, 16));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(190, 450, 201, 23));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(190, 520, 401, 23));
        windSpeed = new QSlider(centralwidget);
        windSpeed->setObjectName(QString::fromUtf8("windSpeed"));
        windSpeed->setGeometry(QRect(610, 410, 160, 22));
        windSpeed->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(650, 380, 71, 16));
        windDir = new QDial(centralwidget);
        windDir->setObjectName(QString::fromUtf8("windDir"));
        windDir->setGeometry(QRect(660, 280, 50, 64));
        windDir->setMinimum(-314);
        windDir->setMaximum(314);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(640, 270, 91, 16));
        xfire = new QLineEdit(centralwidget);
        xfire->setObjectName(QString::fromUtf8("xfire"));
        xfire->setGeometry(QRect(50, 250, 51, 20));
        yfire = new QLineEdit(centralwidget);
        yfire->setObjectName(QString::fromUtf8("yfire"));
        yfire->setGeometry(QRect(50, 280, 51, 20));
        xfirelabel = new QLabel(centralwidget);
        xfirelabel->setObjectName(QString::fromUtf8("xfirelabel"));
        xfirelabel->setGeometry(QRect(20, 250, 47, 13));
        yfirelabel = new QLabel(centralwidget);
        yfirelabel->setObjectName(QString::fromUtf8("yfirelabel"));
        yfirelabel->setGeometry(QRect(20, 280, 47, 13));
        windSpeedLabel = new QLabel(centralwidget);
        windSpeedLabel->setObjectName(QString::fromUtf8("windSpeedLabel"));
        windSpeedLabel->setGeometry(QRect(630, 440, 101, 16));
        windDirLabel = new QLabel(centralwidget);
        windDirLabel->setObjectName(QString::fromUtf8("windDirLabel"));
        windDirLabel->setGeometry(QRect(630, 340, 121, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuMainwindow = new QMenu(menubar);
        menuMainwindow->setObjectName(QString::fromUtf8("menuMainwindow"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMainwindow->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Single step", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Add fire", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Time: 0s", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Wind speed", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Wind direction", nullptr));
        xfire->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        yfire->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        xfirelabel->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        yfirelabel->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        windSpeedLabel->setText(QCoreApplication::translate("MainWindow", "Speed: 0 m/s", nullptr));
        windDirLabel->setText(QCoreApplication::translate("MainWindow", "Angle: 0 Radianti", nullptr));
        menuMainwindow->setTitle(QCoreApplication::translate("MainWindow", "Mainwindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
