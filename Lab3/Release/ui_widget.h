/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QCustomPlot *widget;
    QGroupBox *groupBox_Lagra;
    QLabel *label_2;
    QPushButton *pushButtonLagra;
    QLineEdit *lineEditLagraStart;
    QLineEdit *lineEditLagraPointsCount;
    QLineEdit *lineEditLagraFinish;
    QLabel *label_6;
    QLabel *label_7;
    QGroupBox *groupBox_Gauss;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_6;
    QLabel *label_3;
    QLineEdit *lineEdit_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_8;
    QLabel *label_10;
    QLineEdit *lineEdit_9;
    QLabel *label_5;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(582, 609);
        widget = new QCustomPlot(Widget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 561, 331));
        groupBox_Lagra = new QGroupBox(Widget);
        groupBox_Lagra->setObjectName(QStringLiteral("groupBox_Lagra"));
        groupBox_Lagra->setGeometry(QRect(10, 350, 561, 111));
        label_2 = new QLabel(groupBox_Lagra);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 20, 31, 16));
        label_2->setTextFormat(Qt::AutoText);
        pushButtonLagra = new QPushButton(groupBox_Lagra);
        pushButtonLagra->setObjectName(QStringLiteral("pushButtonLagra"));
        pushButtonLagra->setGeometry(QRect(10, 80, 81, 21));
        lineEditLagraStart = new QLineEdit(groupBox_Lagra);
        lineEditLagraStart->setObjectName(QStringLiteral("lineEditLagraStart"));
        lineEditLagraStart->setGeometry(QRect(110, 40, 51, 20));
        lineEditLagraPointsCount = new QLineEdit(groupBox_Lagra);
        lineEditLagraPointsCount->setObjectName(QStringLiteral("lineEditLagraPointsCount"));
        lineEditLagraPointsCount->setGeometry(QRect(230, 40, 51, 20));
        lineEditLagraFinish = new QLineEdit(groupBox_Lagra);
        lineEditLagraFinish->setObjectName(QStringLiteral("lineEditLagraFinish"));
        lineEditLagraFinish->setGeometry(QRect(170, 40, 51, 20));
        label_6 = new QLabel(groupBox_Lagra);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(170, 20, 31, 16));
        label_6->setTextFormat(Qt::AutoText);
        label_7 = new QLabel(groupBox_Lagra);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(230, 20, 31, 16));
        label_7->setTextFormat(Qt::AutoText);
        groupBox_Gauss = new QGroupBox(Widget);
        groupBox_Gauss->setObjectName(QStringLiteral("groupBox_Gauss"));
        groupBox_Gauss->setEnabled(false);
        groupBox_Gauss->setGeometry(QRect(10, 470, 561, 111));
        pushButton_2 = new QPushButton(groupBox_Gauss);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 20, 81, 21));
        lineEdit_6 = new QLineEdit(groupBox_Gauss);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(220, 40, 51, 20));
        label_3 = new QLabel(groupBox_Gauss);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 20, 31, 16));
        label_3->setTextFormat(Qt::AutoText);
        lineEdit_7 = new QLineEdit(groupBox_Gauss);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(160, 40, 51, 20));
        label_8 = new QLabel(groupBox_Gauss);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(220, 20, 31, 16));
        label_8->setTextFormat(Qt::AutoText);
        label_9 = new QLabel(groupBox_Gauss);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(160, 20, 31, 16));
        label_9->setTextFormat(Qt::AutoText);
        lineEdit_8 = new QLineEdit(groupBox_Gauss);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(100, 40, 51, 20));
        label_10 = new QLabel(groupBox_Gauss);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(280, 20, 31, 16));
        label_10->setTextFormat(Qt::AutoText);
        lineEdit_9 = new QLineEdit(groupBox_Gauss);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(280, 40, 51, 20));
        label_5 = new QLabel(groupBox_Gauss);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 70, 301, 16));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\320\230\320\275\321\202\320\265\321\200\320\277\320\276\320\273\321\217\321\206\320\270\320\276\320\275\320\275\321\213\320\271 \320\274\320\275\320\276\320\263\320\276\321\207\320\273\320\265\320\275 \320\233\320\260\320\263\321\200\320\260\320\275\320\266\320\260", 0));
        groupBox_Lagra->setTitle(QApplication::translate("Widget", "\320\233\320\260\320\263\321\200\320\260\320\275\320\266", 0));
        label_2->setText(QApplication::translate("Widget", "Start:", 0));
        pushButtonLagra->setText(QApplication::translate("Widget", "Draw", 0));
        lineEditLagraStart->setText(QApplication::translate("Widget", "0.1", 0));
        lineEditLagraStart->setPlaceholderText(QApplication::translate("Widget", "Start", 0));
        lineEditLagraPointsCount->setText(QApplication::translate("Widget", "3", 0));
        lineEditLagraPointsCount->setPlaceholderText(QApplication::translate("Widget", "Unit", 0));
        lineEditLagraFinish->setText(QApplication::translate("Widget", "3.1", 0));
        lineEditLagraFinish->setPlaceholderText(QApplication::translate("Widget", "Finish", 0));
        label_6->setText(QApplication::translate("Widget", "Finish:", 0));
        label_7->setText(QApplication::translate("Widget", "Unit:", 0));
        groupBox_Gauss->setTitle(QApplication::translate("Widget", "\320\223\320\260\321\203\321\201\321\201", 0));
        pushButton_2->setText(QApplication::translate("Widget", "Calculate", 0));
        lineEdit_6->setText(QApplication::translate("Widget", "3", 0));
        lineEdit_6->setPlaceholderText(QApplication::translate("Widget", "Unit", 0));
        label_3->setText(QApplication::translate("Widget", "Start:", 0));
        lineEdit_7->setText(QApplication::translate("Widget", "3", 0));
        lineEdit_7->setPlaceholderText(QApplication::translate("Widget", "Finish", 0));
        label_8->setText(QApplication::translate("Widget", "Unit:", 0));
        label_9->setText(QApplication::translate("Widget", "Finish:", 0));
        lineEdit_8->setText(QApplication::translate("Widget", "0.1", 0));
        lineEdit_8->setPlaceholderText(QApplication::translate("Widget", "Start", 0));
        label_10->setText(QApplication::translate("Widget", "Value:", 0));
        lineEdit_9->setText(QApplication::translate("Widget", "0", 0));
        lineEdit_9->setPlaceholderText(QApplication::translate("Widget", "Value", 0));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
