#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFtp>

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
    QFtp *ftp;

private slots:
    void ftpCommandStarted(int);
    void ftpCommandFinished(int,bool);
};

#endif // WIDGET_H
