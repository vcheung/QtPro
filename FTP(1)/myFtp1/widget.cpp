#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ftp = new QFtp(this);
    ftp->connectToHost("ftp.qt.nokia.com");
    ftp->login();
    ftp->cd("qt/source");
    ftp->get("INSTALL");
    ftp->close();

    connect(ftp,SIGNAL(commandStarted(int)),this,SLOT(ftpCommandStarted(int)));
    connect(ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(ftpCommandFinished(int,bool)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ftpCommandStarted(int)
{
    if(ftp->currentCommand()==QFtp::ConnectToHost)
    {
        ui->label->setText(tr("�������ӵ�������"));
    }
    if(ftp->currentCommand()==QFtp::Login)
    {
        ui->label->setText(tr("���ڵ�½����"));
    }
    if(ftp->currentCommand()==QFtp::Get)
    {
        ui->label->setText(tr("�������ء���"));
    }
    if(ftp->currentCommand()==QFtp::Close)
    {
        ui->label->setText(tr("���ڹر����ӡ���"));
    }
}

void Widget::ftpCommandFinished(int, bool error)
{
    if(ftp->currentCommand()==QFtp::ConnectToHost)
    {
        if(error)
            ui->label->setText(tr("���ӷ��������ִ���%1").arg(ftp->errorString()));
        else
            ui->label->setText(tr("���ӵ��������ɹ�"));
    }
    if(ftp->currentCommand()==QFtp::Login)
    {
        if(error)
            ui->label->setText(tr("��½���ִ���%1").arg(ftp->errorString()));
        else
            ui->label->setText(tr("��½�ɹ�"));
    }
    if(ftp->currentCommand()==QFtp::Get)
    {
        if(error)
            ui->label->setText(tr("���س��ִ���%1").arg(ftp->errorString()));
        else
        {
            ui->label->setText(tr("�������"));
            ui->textBrowser->setText(ftp->readAll());
        }
    }
    else if(ftp->currentCommand()==QFtp::Close)
        ui->label->setText(tr("�Ѿ��ر�����"));
}
