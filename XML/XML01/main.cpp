#include <QCoreApplication>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDomDocument (doc);
    QFile file("my.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        return 0;
    }

    QString errorStr;
    int errorLine;
    int errorColumnn;

    if(!doc.setContent(&file,false,&errorStr,&errorLine,&errorColumnn))
    {
        qDebug() << "file closed";
        std::cerr << "Error: Parse error at line" << errorLine <<","
                  << "cloumn" << errorColumnn << ":"
                  << qPrintable(errorStr) << std::endl;
        file.close();
        return 0;
    }
    file.close();

    QDomNode firstNote = doc.firstChild();
    qDebug() << qPrintable(firstNote.nodeName())
                <<qPrintable(firstNote.nodeValue());

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        if(n.isElement())
        {
            QDomElement e = n.toElement();
            qDebug() << qPrintable(e.tagName())
                     << qPrintable(e.attribute("id"));

            QDomNodeList list = e.childNodes();
            for(int i=0; i<list.count();i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                    qDebug() << " " << qPrintable(node.toElement().tagName())
                             << qPrintable(node.toElement().text());

            }
        }
        n = n.nextSibling();
    }
    return a.exec();
}
