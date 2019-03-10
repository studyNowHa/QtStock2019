#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QMessageBox>
#include <QStandardItem>
#include <QTableWidget>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->TableWidgeet();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetTableWidget(QStringList stringList)
{
    int stockStep = 8;
    for (int i=0; i<stringList.length()/8; i++) {
        QTableWidgetItem *tableWidgetItemName = new QTableWidgetItem(stringList[i*stockStep+0]);
        QTableWidgetItem *tableWidgetItemNewrange = new QTableWidgetItem(stringList[i*stockStep+1]);
        if(stringList[i*stockStep+2] == "red"){
            tableWidgetItemNewrange->setBackgroundColor(QColor(255,0,0));//设置单元格背景色
        }else if(stringList[i*stockStep+2] == "blue"){
            tableWidgetItemNewrange->setBackgroundColor(QColor(0,255,0));//设置单元格背景色
        }
        QTableWidgetItem *tableWidgetItemStartrange = new QTableWidgetItem(stringList[i*stockStep+3]);
        if(stringList[i*stockStep+4] == "red"){
            tableWidgetItemStartrange->setBackgroundColor(QColor(255,0,0));//设置单元格背景色
        }
        else if(stringList[i*stockStep+4] == "blue"){
            tableWidgetItemStartrange->setBackgroundColor(QColor(0,255,0));//设置单元格背景色
        }
        QTableWidgetItem *tableWidgetItemMinrange = new QTableWidgetItem(stringList[i*stockStep+5]);
        if(stringList[i*stockStep+6] == "red"){
            tableWidgetItemMinrange->setBackgroundColor(QColor(255,0,0));//设置单元格背景色
        }else if(stringList[i*stockStep+6] == "blue"){
            tableWidgetItemMinrange->setBackgroundColor(QColor(0,255,0));//设置单元格背景色
        }
        ui->tableWidget->setItem(i,stockNameSite,tableWidgetItemName);
        ui->tableWidget->setItem(i,stockNewrangeSite,tableWidgetItemNewrange);
        ui->tableWidget->setItem(i,stockStartrangeSite,tableWidgetItemStartrange);
        ui->tableWidget->setItem(i,stockMinrangeSite,tableWidgetItemMinrange);
        ui->tableWidget->setItem(i,stockBuyoneSite,new QTableWidgetItem(stringList[i*stockStep+7]));
    }
    ui->tableWidget->viewport()->update();//立即刷新界面
}

bool MainWindow::TableWidgeet()
{
    //static QStringList stockStringListDecode;      //股票代码上证深圳判断后的股票池
    QStringList stockStringList;            //股票代码池
    QStringList stockStringListTheme;       //股票题材
    QStringList stockStringListDay;         //股票涨停天数
    //获取文本文件内容
    QFile f("./stock.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox msgBox;
        msgBox.setText("没有找到文件！");
        msgBox.exec();
        return false;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine().toUtf8();
        QStringList stringList = lineStr.split("\t");//获取文本中的股票代码
        //判断是否为股票代码
        if(stringList[stockSite].toInt()>0){
            stockStringList.append(stringList[stockSite]);//记录股票代码
            stockStringListTheme.append(stringList[stockThemeSite]);//记录股票概念
            if(stringList[stockSite].toInt()>0 && stringList[stockSite].toInt()<600000){
                this->stockStringListDecode.append("sz"+stringList[stockSite]+",");//深圳的票
            }else{this->stockStringListDecode.append("sh"+stringList[stockSite]+",");}//上海的票
        }

    }
    f.close();

    //设置行列数
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(8);
    //设置表头
    QStringList head;
    head<<QStringLiteral("题材概念");
    head<<QStringLiteral("证券代码");
    head<<QStringLiteral("证券名称");
    head<<QStringLiteral("最新涨幅");
    head<<QStringLiteral("开盘涨幅");
    head<<QStringLiteral("第几板");
    head<<QStringLiteral("最小涨幅");
    head<<QStringLiteral("买一金额(万)");
    ui->tableWidget->setHorizontalHeaderLabels(head);
    //行列大小与内容匹配
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();


    //根据文本文件添加内容
    for (int i=0; i<stockStringList.length(); i++) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(stockStringListTheme[i]));//第一列
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(stockStringList[i]));//第二列
    }

}
