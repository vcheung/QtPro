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
        ui->label->setText(tr("正在连接到服务器"));
    }
    if(ftp->currentCommand()==QFtp::Login)
    {
        ui->label->setText(tr("正在登陆……"));
    }
    if(ftp->currentCommand()==QFtp::Get)
    {
        ui->label->setText(tr("正在下载……"));
    }
    if(ftp->currentCommand()==QFtp::Close)
    {
        ui->label->setText(tr("正在关闭连接……"));
    }
}

void Widget::ftpCommandFinished(int, bool error)
{
    if(ftp->currentCommand()==QFtp::ConnectToHost)
    {
        if(error)
            ui->label->setText(tr("连接服务器出现错误：%1").arg(ftp->errorString()));
        else
            ui->label->setText(tr("连接到服务器成功"));
    }
    if(ftp->currentCommand()==QFtp::Login)
    {
        if(error)
            ui->label->setText(tr("登陆出现错误：%1").arg(ftp->errorString()));
        else
            ui->label->setText(tr("登陆成功"));
    }
    if(ftp->currentCommand()==QFtp::Get)
    {
        if(error)
            ui->label->setText(tr("下载出现错误：%1").arg(ftp->errorString()));
        else
        {
            ui->label->setText(tr("完成下载"));
            ui->textBrowser->setText(ftp->readAll());
        }
    }
    else if(ftp->currentCommand()==QFtp::Close)
        ui->label->setText(tr("已经关闭连接"));
}
