
#include "getstockdata.h"
#include "threadstock.h"

ThreadStock::ThreadStock()
{

}

void ThreadStock::run()
{
    while(true){
        QStringList stringList;
        //获取网络上的股票数据
        GetStockData *stockDate = new GetStockData(mWindow->stockStringListDecode);
        QString stringStock = stockDate->GetStringListStock();
        QStringList stringListSplitOne = stringStock.split(";");//一个股票的一组数据
        for(int i=0; i<stringListSplitOne.length()-1; i++){
            QStringList stringListTmp = stringListSplitOne.at(i).split("~");//一个股票数据的每一项内容
            stringList.append(stringListTmp.at(stockName));//股票名称
            float intTmp = stringListTmp.at(stockNowprice).toFloat()/stringListTmp.at(stockLastprice).toFloat()-1;
            QString sTmp = QString::number(intTmp*100,'f',2);
            stringList.append(sTmp);//股票现在涨幅
            //判断是否真实涨停
            if((stringListTmp.at(stockNowprice).toFloat() == stringListTmp.at(stockLimitupprice).toFloat())&&
                    (stringListTmp.at(stockSellFitstvolumn).toFloat() == 0.0)){
                stringList.append("red");
            }else if((stringListTmp.at(stockNowprice).toFloat() == stringListTmp.at(stockLimitdownprice).toFloat())&&
                     (stringListTmp.at(stockBuyFitstvolumn).toFloat() == 0.0)){
                stringList.append("blue");}else {stringList.append("white");}
            intTmp = stringListTmp.at(stockstartprice).toFloat()/stringListTmp.at(stockLastprice).toFloat()-1;
            sTmp = QString::number(intTmp*100,'f',2);
            stringList.append(sTmp);//股票开盘涨幅
            //判断是否真实涨停
            if((stringListTmp.at(stockstartprice).toFloat() == stringListTmp.at(stockLimitupprice).toFloat())&&
                    (stringListTmp.at(stockSellFitstvolumn).toFloat() == 0.0)){
                stringList.append("red");
            }else if((stringListTmp.at(stockstartprice).toFloat() == stringListTmp.at(stockLimitdownprice).toFloat())&&
                     (stringListTmp.at(stockBuyFitstvolumn).toFloat() == 0.0)){
                stringList.append("blue");}else {stringList.append("white");}
            intTmp = stringListTmp.at(stockMinprice).toFloat()/stringListTmp.at(stockLastprice).toFloat()-1;
            sTmp = QString::number(intTmp*100,'f',2);
            stringList.append(sTmp);//股票日内最低涨幅
            //判断是否真实涨停
            if((stringListTmp.at(stockMinprice).toFloat() == stringListTmp.at(stockLimitupprice).toFloat())&&
                    (stringListTmp.at(stockSellFitstvolumn).toFloat() == 0.0)){
                stringList.append("red");
            }else if((stringListTmp.at(stockMinprice).toFloat() == stringListTmp.at(stockLimitdownprice).toFloat())&&
                     (stringListTmp.at(stockBuyFitstvolumn).toFloat() == 0.0)){
                stringList.append("blue");}else {stringList.append("white");}
            intTmp = stringListTmp.at(stockBuyFirstprice).toFloat()*stringListTmp.at(stockBuyFitstvolumn).toFloat();
            sTmp = QString::number(intTmp*100/10000,'f',2);
            stringList.append(sTmp);//股票买一金额（万）
        }

        mWindow->SetTableWidget(stringList);//刷新表格
        //显示系统时间
        QDateTime current_time = QDateTime::currentDateTime();
        qDebug()<< current_time.toString("yyyy-MM-dd hh:mm:ss:zzz ddd")<<endl;
    }
}

void ThreadStock::SetMainWIndowPoing(MainWindow *m)
{
    mWindow = m;
}
