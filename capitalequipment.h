#ifndef CAPITALEQUIPMENT_H
#define CAPITALEQUIPMENT_H

#include "relay.h"
#include "can.h"
#include "./equipment/bk2831e.h"
#include "./equipment/bk9200.h"
#include "dac.h"
#include "probe.h"


class CapitalEquipment{


public:
    //Constructor-Deconstructor
    CapitalEquipment();
    ~CapitalEquipment();

    //Probe
    probe *Probe;

    //Equipment
    BK2831E *pMeter;
    BK9200 *pMotorSupply;
    BK9200 *pCharger;
    Dac *pDac;
    Relay *pRelay1;
    Relay *pRelay2;
    Can *pCan;

    //getPort (unused)
    char* getPort(QString piece);

    //Object creation
    void create();
    int getCompletedStatus();

  private:
    int completed;
};

extern  CapitalEquipment *pce;
#endif
