#include "mainwindow.h"
#include "threadstock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //运行刷新QTableWidget线程
    ThreadStock *threadStock = new ThreadStock();
    threadStock->SetMainWIndowPoing(&w);
    threadStock->start();

    return a.exec();
}
