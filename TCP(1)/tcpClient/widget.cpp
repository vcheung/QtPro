#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newConnect()
{
    blockSize = 0; //��ʼ����Ϊ0
    tcpSocket->abort(); //ȡ�����е�����
    tcpSocket->connectToHost(ui->hostLineEdit->text(),ui->portLineEdit->text().toInt());     //���ӵ�����������ӽ����ȡ������ַ�Ͷ˿ں�
}

void Widget::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_6);     //�����������汾������Ҫ�ͷ���������ͬ
    if(blockSize==0) //����Ǹտ�ʼ��������
    {
        //�жϽ��յ������Ƿ������ֽڣ�Ҳ�����ļ��Ĵ�С��Ϣ
        //������򱣴浽blockSize�����У�û���򷵻أ�������������
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> blockSize;
    }
        if(tcpSocket->bytesAvailable() < blockSize) return;     //���û�еõ�ȫ�������ݣ��򷵻أ�������������
        in >> message;  //�����յ������ݴ�ŵ�������
        ui->messageLabel->setText(message);     //��ʾ���յ�������
}

void Widget::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString(); //���������Ϣ
}

void Widget::on_pushButton_clicked()    //���Ӱ�ť
{
    newConnect(); //��������
}
