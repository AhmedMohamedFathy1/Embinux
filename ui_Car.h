/********************************************************************************
** Form generated from reading UI file 'Car.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAR_H
#define UI_CAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *obstacle;
    QLabel *OverHeat;
    QLabel *Fuel;
    QLabel *LowBattery;
    QLabel *Speed;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 361, 41));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        obstacle = new QLabel(centralwidget);
        obstacle->setObjectName("obstacle");
        obstacle->setGeometry(QRect(20, 140, 250, 40));
        obstacle->setFont(font);
        OverHeat = new QLabel(centralwidget);
        OverHeat->setObjectName("OverHeat");
        OverHeat->setGeometry(QRect(20, 200, 250, 40));
        OverHeat->setFont(font);
        Fuel = new QLabel(centralwidget);
        Fuel->setObjectName("Fuel");
        Fuel->setGeometry(QRect(20, 310, 250, 40));
        Fuel->setFont(font);
        LowBattery = new QLabel(centralwidget);
        LowBattery->setObjectName("LowBattery");
        LowBattery->setGeometry(QRect(20, 250, 250, 40));
        LowBattery->setFont(font);
        Speed = new QLabel(centralwidget);
        Speed->setObjectName("Speed");
        Speed->setGeometry(QRect(20, 80, 250, 40));
        Speed->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Vehcile Speed ", nullptr));
        obstacle->setText(QString());
        OverHeat->setText(QString());
        Fuel->setText(QString());
        LowBattery->setText(QString());
        Speed->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAR_H
