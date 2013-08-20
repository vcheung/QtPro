#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    connect(&tcpServer,SIGNAL(newConnection()),this, SLOT(acceptConnection()));
    //������������ʱ����newConnection()�ź�
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start() //��ʼ����
{
    ui->startButton->setEnabled(false);
    bytesReceived =0;
    if(!tcpServer.listen(QHostAddress::LocalHost,6666))
    {
        qDebug() << tcpServer.errorString();
        close();
        return;
    }
    ui->serverStatusLabel->setText(tr("����"));
}

void Widget::acceptConnection()  //��������
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    connect(tcpServerConnection,SIGNAL(readyRead()),this, SLOT(updateServerProgress()));
    connect(tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    ui->serverStatusLabel->setText(tr("��������"));
    tcpServer.close();
}

void Widget::updateServerProgress()  //���½���������������
{
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_4_6);
    if(bytesReceived <= sizeof(qint64)*2)
    {
        //������յ�������С��16���ֽڣ���ô�Ǹտ�ʼ�������ݣ����Ǳ��浽//����ͷ�ļ���Ϣ
        if((tcpServerConnection->bytesAvailable() >= sizeof(qint64)*2)&&(fileNameSize == 0))
        {
            //���������ܴ�С��Ϣ���ļ�����С��Ϣ
            in >> totalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64) * 2;
        }
        if((tcpServerConnection->bytesAvailable() >= fileNameSize)&&(fileNameSize != 0))
        {
            //�����ļ������������ļ�
            in >> fileName;
            ui->serverStatusLabel->setText(tr("�����ļ� %1����").arg(fileName));
            bytesReceived += fileNameSize;
            localFile = new QFile(fileName);
            if(!localFile->open(QFile::WriteOnly))
            {
                qDebug() << "open file error!";
                return;
            }
        }
        else return;
    }
    if(bytesReceived < totalBytes)
    {
        //������յ�����С�������ݣ���ôд���ļ�
        bytesReceived += tcpServerConnection->bytesAvailable();
        inBlock = tcpServerConnection->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    ui->serverProgressBar->setMaximum(totalBytes);
    ui->serverProgressBar->setValue(bytesReceived);    //���½�����
    if(bytesReceived == totalBytes)
    {
        //�����������ʱ
        tcpServerConnection->close();
        localFile->close();
        ui->startButton->setEnabled(true);
        ui->serverStatusLabel->setText(tr("�����ļ� %1 �ɹ���").arg(fileName));
    }
}

void Widget::displayError(QAbstractSocket::SocketError) //������
{
    qDebug() << tcpServerConnection->errorString();
    tcpServerConnection->close();
    ui->serverProgressBar->reset();
    ui->serverStatusLabel->setText(tr("����˾���"));
    ui->startButton->setEnabled(true);
}

void Widget::on_startButton_clicked()
{
    start();
}
