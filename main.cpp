#include "mainwindow.h"

#include <QApplication>
#include "protocol.h"


int main(int argc, char *argv[])
{
    qDebug() << "1" <<endl;
    QApplication a(argc, argv);
    MainWindow w;
    qDebug()<< getMacAddress();
    w.show();

    return a.exec();
}
