#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if(QCoreApplication::arguments().at(1) != "hidden")
        w.show();

    return a.exec();
}
