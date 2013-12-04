#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QFile>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void startRequest(QUrl url);    //«Î«Û¡¥Ω”

private:
    Ui::Widget *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;
    QFile *file;

private slots:
    void replyFinished(QNetworkReply *);
    void on_pushButton_clicked();
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64,qint64);
};

#endif // WIDGET_H
