#ifndef THREADSTOCK_H
#define THREADSTOCK_H

#include <QThread>
#include "mainwindow.h"


class ThreadStock:public QThread
{
public:
    ThreadStock();
    virtual void run();
    void SetMainWIndowPoing(MainWindow *m);
private:
    MainWindow *mWindow;
#define stockName               1       //股票名称
#define stockNowprice           3       //股票现在价格
#define stockLastprice          4       //股票昨天收盘价
#define stockstartprice         5       //股票开盘价
#define stockBuyFirstprice      9       //股票买一价
#define stockBuyFitstvolumn     10      //股票买一量
#define stockSellFitstvolumn    20      //股票买一量
#define stockMinprice           34      //股票日内最低价
#define stockLimitupprice       47      //股票涨停价
#define stockLimitdownprice     48      //股票涨停价
};

#endif // THREADSTOCK_H
