#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if(QCoreApplication::arguments().length() >= 2)
        if(QCoreApplication::arguments().at(1) == "hidden")
            return a.exec();

    w.show();
    return a.exec();
}
