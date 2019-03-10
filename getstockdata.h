#ifndef GETSTOCKDATA_H
#define GETSTOCKDATA_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QTimer>

class GetStockData
{
public:
    GetStockData(QStringList stringList);
    QString GetStringListStock();//返回网上获取的股票数据
private:
    QString stringListReturn;
};

#endif // GETSTOCKDATA_H
