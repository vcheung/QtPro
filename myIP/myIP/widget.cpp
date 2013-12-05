#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
////    /* ��ȡ������ */
////    QString localHostName = QHostInfo::localHostName();
////    qDebug()<<"localHostName:"<<localHostName;

////    /* ��ȡ����IP */
////    QHostInfo info = QHostInfo::fromName(localHostName);
////    qDebug()<<"IP Address:"<<info.addresses();
////    foreach(QHostAddress address,info.addresses())
////    {
////        if(address.protocol()==QAbstractSocket::IPv4Protocol)
////            qDebug()<<address.toString();
////    }

//    /* ����������ȡIP */
//    QHostInfo::lookupHost("www.baidu.com",this,SLOT(lookedUp(QHostInfo)));

    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface interface, list)
    {
        qDebug()<<"Device:"<<interface.name();
        qDebug()<<"HardwareAddress"<<interface.hardwareAddress();
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        foreach (QNetworkAddressEntry entry, entryList)
        {
            qDebug()<<"IP Address:"<<entry.ip().toString();
            qDebug()<<"Netmask:"<<entry.netmask().toString();
            qDebug()<<"Broadcast:"<<entry.broadcast().toString();
        }
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::lookedUp(const QHostInfo &host)
{
    qDebug()<<host.addresses().first().toString();
}
