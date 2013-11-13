#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage image("philip.png");
    QMap<QString,QColor> map;
    map.insert("red",Qt::red);
    map.insert("green",Qt::green);
    map.insert("blue",Qt::blue);

    QFile file("facts.dat");
    if(!file.open(QIODevice::WriteOnly))
    {
        std::cerr << "Cannot open file for writing:"
                  << qPrintable(file.errorString()) << std::endl;
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);

    out << quint32(0x12345678) << image << map;
    qDebug() << "outed" ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
