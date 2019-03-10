#include "getstockdata.h"

GetStockData::GetStockData(QStringList stringList)
{
    QString stringStock;
    for (int i=0; i<stringList.length(); i++) {
        stringStock.append(stringList.at(i));
    }
    QNetworkReply *replys;
    QNetworkAccessManager netWork;
    QEventLoop eventLoop;
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()),&eventLoop,SLOT(quit()));
    QObject::connect(&netWork, SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));
    timer.start(1000);
    replys =netWork.get(QNetworkRequest(QUrl("http://qt.gtimg.cn/q="+stringStock )));
    eventLoop.exec();
    this->stringListReturn = QString::fromLocal8Bit(replys->readAll());
    delete replys;
}

QString GetStockData::GetStringListStock()
{
    return stringListReturn;
}
