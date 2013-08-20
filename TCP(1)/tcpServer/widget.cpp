#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::LocalHost,6666))
    {
        //��������������6666�˿ڣ������������������Ϣ�����ر�
        qDebug() << tcpServer->errorString();
        close();
    }
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
    //�����źź���Ӧ�ۺ���
    //���캯����ʹ��tcpServer��listen()�������м�����Ȼ�������newConnection()�������Լ���sendMessage()������
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMessage()
{
    QByteArray block; //�����ݴ�����Ҫ���͵�����
    QDataStream out(&block,QIODevice::WriteOnly);     //ʹ��������д������
    out.setVersion(QDataStream::Qt_4_6);      //�����������İ汾���ͻ��˺ͷ�������ʹ�õİ汾Ҫ��ͬ
    out<<(quint16) 0;
    out<<tr("hello Tcp!!!");
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();     //���ǻ�ȡ�Ѿ����������ӵ����׽���
    connect(clientConnection,SIGNAL(disconnected()),clientConnection,SLOT(deleteLater()));
    clientConnection->write(block);
    clientConnection->disconnectFromHost();
    ui->statusLabel->setText("send message successful!!!");     //�������ݳɹ�����ʾ��ʾ
}
