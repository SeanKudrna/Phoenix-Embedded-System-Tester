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

class probe : public QObject
{
    Q_OBJECT

public:
    //Constructor
     probe();

    //Equipment structure
    struct equipmentAssignment
    {
        //Serial port
        QString port;

        //Equipment type
        equipment equ;
    };

    //List of equipment objects
    QList<equipmentAssignment> pieces;

    //Find available ports
    void listPorts();
    bool getStatus();

public slots:
        void testAll();

private:
    SerialDevice *pSerial;
    QList<QString> portList;
    QTimer *timer;
    bool complete;
    QString curPort;
    equipmentAssignment piece;



};

#endif // PROBE_H
