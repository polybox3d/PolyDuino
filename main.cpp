#include <stdlib.h>
#include <stdio.h>

#include <cstdlib>
#include <cstdio>

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
