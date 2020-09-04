#include "mainwindow.h"
#include <QApplication>
#include<QPushButton>
#include<QLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.centerAndResize();

    return a.exec();
}
