#include "widget.h"
#include "ui_widget.h"
#include <QtXml/qdom.h>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QFile file("my.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement(tr("���"));
    doc.appendChild(root);

    QDomElement book = doc.createElement(tr("ͼ��"));
    QDomAttr id = doc.createAttribute(tr("���"));
    QDomElement title = doc.createElement(tr("����"));
    QDomElement author = doc.createElement(tr("����"));
    QDomText text;
    id.setValue(tr("1"));
    book.setAttributeNode(id);
    text = doc.createTextNode(tr("Qt"));
    title.appendChild(text);
    text = doc.createTextNode(tr("shiming"));
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    book = doc.createElement(tr("ͼ��"));
    id = doc.createAttribute(tr("���"));
    title = doc.createElement(tr("����"));
    author = doc.createElement(tr("����"));
    id.setValue(tr("2"));
    book.setAttributeNode(id);
    text = doc.createTextNode(tr("Linux"));
    title.appendChild(text);
    text = doc.createTextNode(tr("yafei"));
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_5_clicked()  //�鿴ȫ����Ϣ
{
    ui->listWidget->clear();
    QFile file("my.xml");
    if(!file.open(QIODevice::ReadOnly))
        return;
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        if(n.isElement())
        {
            QDomElement e = n.toElement();
            ui->listWidget->addItem(e.tagName()+e.attribute(tr("���")));
            QDomNodeList list = e.childNodes();
            for(int i=0;i<list.count();i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                    ui->listWidget->addItem(" "+node.toElement().tagName()
                                            +":"+node.toElement().text());
            }
        }
        n=n.nextSibling();
    }
}

void Widget::on_pushButton_3_clicked()  //���
{
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("�޷���ӣ�"));
    QFile file("my.xml");
    if(!file.open(QIODevice::ReadOnly))
        return;
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomElement book = doc.createElement(tr("ͼ��"));
    QDomAttr id = doc.createAttribute(tr("���"));
    QDomElement title = doc.createElement(tr("����"));
    QDomElement author = doc.createElement(tr("����"));
    QDomText text;

    QString num = root.lastChild().toElement().attribute(tr("���"));
    int count = num.toInt()+1;
    id.setValue(QString::number(count));
    book.setAttributeNode(id);
    text = doc.createTextNode(ui->lineEdit_2->text());
    title.appendChild(text);
    text = doc.createTextNode(ui->lineEdit_3->text());
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("��ӳɹ�"));
}

void Widget::doXml(const QString operate)
{
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("û���ҵ�������ݣ�"));
    QFile file("my.xml");
    if(!file.open(QIODevice::ReadOnly))
        return;
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    QDomNodeList list = doc.elementsByTagName(tr("ͼ��"));

    for(int i=0;i<list.count();i++)
    {
        QDomElement e = list.at(i).toElement();
        if(e.attribute(tr("���")) == ui->lineEdit->text())
        {
            if(operate == "delete")
            {
                QDomElement root = doc.documentElement();
                root.removeChild(list.at(i));
                QFile file("my.xml");
                if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return;
                QTextStream out(&file);
                doc.save(out,4);
                file.close();

                ui->listWidget->clear();
                ui->listWidget->addItem(tr("ɾ���ɹ�"));
            }
            else if(operate=="update")
            {
                QDomNodeList child = list.at(i).childNodes();
                child.at(0).toElement().firstChild().setNodeValue(ui->lineEdit_2->text());
                child.at(1).toElement().firstChild().setNodeValue(ui->lineEdit_3->text());
                QFile file("my.xml");
                if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return;
                QTextStream out(&file);
                doc.save(out,4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(tr("���³ɹ�"));
            }
            else if(operate=="find")
            {
                ui->listWidget->clear();
                ui->listWidget->addItem(e.tagName()+e.attribute(tr("���")));
                QDomNodeList list = e.childNodes();
                for(int i=0;i<list.count();i++)
                {
                    QDomNode node = list.at(i);
                    if(node.isElement())
                        ui->listWidget->addItem(" "+node.toElement().tagName()
                                                +":"+node.toElement().text());
                }
            }
        }
    }
}

void Widget::on_pushButton_clicked()    //����
{
    doXml("find");
}

void Widget::on_pushButton_2_clicked()  //ɾ��
{
    doXml("delete");
}

void Widget::on_pushButton_4_clicked()  //����
{
    doXml("update");
}
