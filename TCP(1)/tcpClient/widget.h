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
    QTcpSocket *tcpSocket;
    QString message;  //��Ŵӷ��������յ����ַ���
    quint16 blockSize;  //����ļ��Ĵ�С��Ϣ

private slots:
    void newConnect(); //���ӷ�����
    void readMessage();  //��������
    void displayError(QAbstractSocket::SocketError);  //��ʾ����
    void on_pushButton_clicked();
};

#endif // WIDGET_H
