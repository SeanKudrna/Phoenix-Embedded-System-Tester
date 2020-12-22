#ifndef PROBE_H
#define PROBE_H
#include "./equipment/bk.h"
#include <QList>
#include <QTimer>
#include "./equipment/bk2831e.h"
#include "./equipment/bk9200.h"

typedef enum {
    meter,
    motorSupply,
    chargerSupply
}equipment;

class probe
{
public:
    explicit probe(BK *parent, const char *port,int baud,char terminationChar, QString idString);
    probe();

    struct equipmentAssignment
    {
        QString port;
        equipment equ;
    };
    QList<equipmentAssignment> pieces;
    void listPorts();
    void testAll();

    //void listPorts();
    //void testAll();


private:
    SerialDevice *pSerial;
    QList<QString> portList;
    QTimer *timer;
    QString curPort;

    //struct equipmentConfig
    //{
    //    QString serialPort;
    //    equipment piece;
    //};
    equipmentAssignment piece;



};

#endif // PROBE_H
