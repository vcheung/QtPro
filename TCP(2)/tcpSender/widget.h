#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private:
    Ui::Widget *ui;
    QTcpSocket *tcpClient;
    QFile *localFile;  //Ҫ���͵��ļ�
    qint64 totalBytes;  //�����ܴ�С
    qint64 bytesWritten;  //�Ѿ��������ݴ�С
    qint64 bytesToWrite;   //ʣ�����ݴ�С
    qint64 loadSize;   //ÿ�η������ݵĴ�С
    QString fileName;  //�����ļ�·��
    QByteArray outBlock;  //���ݻ������������ÿ��Ҫ���͵�����

private slots:
    void send();  //���ӷ�����
    void startTransfer();  //�����ļ���С����Ϣ
    void updateClientProgress(qint64); //�������ݣ����½�����
    void displayError(QAbstractSocket::SocketError); //��ʾ����
    void openFile();  //���ļ�
    void on_openButton_clicked();
    void on_sendButton_clicked();
};

#endif // WIDGET_H
