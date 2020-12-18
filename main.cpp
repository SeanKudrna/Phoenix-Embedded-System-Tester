#include "mainwindow.h"
#include <QApplication>
#include "capitalequipment.h"
CapitalEquipment *pce;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    pce = new CapitalEquipment();
    w.show();

    return a.exec();
}


