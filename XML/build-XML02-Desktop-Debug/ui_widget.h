/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Thu Nov 14 10:58:51 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QListWidget *listWidget;
    QPushButton *pushButton_5;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(400, 300);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 60, 61, 16));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 60, 113, 20));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 90, 75, 23));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(130, 90, 75, 23));
        lineEdit_2 = new QLineEdit(Widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 130, 113, 20));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 130, 61, 16));
        lineEdit_3 = new QLineEdit(Widget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(90, 170, 113, 20));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 170, 61, 16));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(130, 210, 75, 23));
        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(30, 210, 75, 23));
        listWidget = new QListWidget(Widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(230, 20, 161, 201));
        pushButton_5 = new QPushButton(Widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(260, 250, 111, 23));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "\345\233\276\344\271\246\347\274\226\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Widget", "\346\237\245\346\211\276", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Widget", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "\344\271\246\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "\344\275\234\350\200\205\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("Widget", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("Widget", "\346\233\264\346\226\260", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("Widget", "\346\237\245\347\234\213\345\205\250\351\203\250\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
