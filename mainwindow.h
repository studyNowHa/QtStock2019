#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetTableWidget(QStringList stringList);    //刷新表格内容
    QStringList stockStringListDecode;              //股票代码上证深圳判断后的股票池
    Ui::MainWindow *ui;
private:
    //Ui::MainWindow *ui;
    bool TableWidgeet();//绘制表格
    #define stockThemeSite      0   //股票题材在表格中的位置
    #define stockSite           1   //股票代码在表格中的位置
    #define stockNameSite       2   //股票名称在表格中的位置
    #define stockNewrangeSite   3   //股票最新涨幅在表格中的位置
    #define stockStartrangeSite 4   //股票开盘涨幅在表格中的位置
    #define stockDaySite        5   //股票涨停天数在表格中的位置
    #define stockMinrangeSite   6   //股票日内最低涨幅在表格中的位置
    #define stockBuyoneSite     7   //股票买一在表格中的位置
};

#endif // MAINWINDOW_H
