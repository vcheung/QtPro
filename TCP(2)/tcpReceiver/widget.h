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
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
    qint64 totalBytes;  //����ܴ�С��Ϣ
    qint64 bytesReceived;  //���յ����ݵĴ�С
    qint64 fileNameSize;  //�ļ����Ĵ�С��Ϣ
    QString fileName;   //����ļ���
    QFile *localFile;   //�����ļ�
    QByteArray inBlock;   //���ݻ�����

private slots:
    void on_startButton_clicked();
    void start();   //��ʼ����
    void acceptConnection();  //��������
    void updateServerProgress();  //���½���������������
    void displayError(QAbstractSocket::SocketError socketError);  //��ʾ����
};

#endif // WIDGET_H
