#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    loadSize = 4*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    tcpClient = new QTcpSocket(this);
    connect(tcpClient,SIGNAL(connected()),this,SLOT(startTransfer()));  //�����ӷ������ɹ�ʱ������connected()�źţ����ǿ�ʼ�����ļ�
    connect(tcpClient,SIGNAL(bytesWritten(qint64)),this, SLOT(updateClientProgress(qint64)));     //�������ݷ��ͳɹ�ʱ�����Ǹ��½�����
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    ui->sendButton->setEnabled(false);     //��ʼʹ�����͡���ť������
}

Widget::~Widget()
{
    delete ui;
}

void Widget::openFile()   //���ļ�
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        ui->sendButton->setEnabled(true);
        ui->clientStatusLabel->setText(tr("���ļ� %1 �ɹ�!").arg(fileName));
    }
}

void Widget::send()   //���ӵ���������ִ�з���
{
    ui->sendButton->setEnabled(false);
    bytesWritten = 0;     //��ʼ���ѷ����ֽ�Ϊ0
    ui->clientStatusLabel->setText(tr("�����С���"));
    tcpClient->connectToHost(ui->hostLineEdit->text(),ui->portLineEdit->text().toInt());    //����
}

void Widget::startTransfer()  //ʵ���ļ���С����Ϣ�ķ���
{
    localFile = new QFile(fileName);
    if(!localFile->open(QFile::ReadOnly))
    {
        qDebug() << "open file error!";
        return;
    }
    totalBytes = localFile->size();     //�ļ��ܴ�С
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_6);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
    sendOut << qint64(0) << qint64(0) << currentFileName;     //����д���ܴ�С��Ϣ�ռ䣬�ļ�����С��Ϣ�ռ䣬�ļ���
    totalBytes += outBlock.size();     //������ܴ�С���ļ�����С����Ϣ��ʵ���ļ���С���ܺ�
    sendOut.device()->seek(0);
    sendOut<<totalBytes<<qint64((outBlock.size() - sizeof(qint64)*2));     //����outBolock�Ŀ�ʼ����ʵ�ʵĴ�С��Ϣ��������qint64(0)�ռ�
    bytesToWrite = totalBytes - tcpClient->write(outBlock);     //������ͷ���ݺ�ʣ�����ݵĴ�С
    ui->clientStatusLabel->setText(tr("������"));
    outBlock.resize(0);
}

void Widget::updateClientProgress(qint64 numBytes) //���½�������ʵ���ļ��Ĵ���
{
    bytesWritten += (int)numBytes;     //�Ѿ��������ݵĴ�С
    if(bytesToWrite > 0) //����Ѿ�����������
    {
        outBlock = localFile->read(qMin(bytesToWrite,loadSize));
        //ÿ�η���loadSize��С�����ݣ���������Ϊ4KB�����ʣ������ݲ���4KB��
        //�ͷ���ʣ�����ݵĴ�С
        bytesToWrite -= (int)tcpClient->write(outBlock);        //������һ�����ݺ�ʣ�����ݵĴ�С
        outBlock.resize(0);         //��շ��ͻ�����
    }
    else
    {
        localFile->close(); //���û�з����κ����ݣ���ر��ļ�
    }
    ui->clientProgressBar->setMaximum(totalBytes);
    ui->clientProgressBar->setValue(bytesWritten);     //���½�����
    if(bytesWritten == totalBytes) //�������
    {
        ui->clientStatusLabel->setText(tr("�����ļ� %1 �ɹ�").arg(fileName));
        localFile->close();
        tcpClient->close();
    }
}

void Widget::displayError(QAbstractSocket::SocketError) //��ʾ����
{
    qDebug() << tcpClient->errorString();
    tcpClient->close();
    ui->clientProgressBar->reset();
    ui->clientStatusLabel->setText(tr("�ͻ��˾���"));
    ui->sendButton->setEnabled(true);
}


void Widget::on_openButton_clicked()
{
    openFile();
}

void Widget::on_sendButton_clicked()
{
    send();
}
