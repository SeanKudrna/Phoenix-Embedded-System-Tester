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
    CapitalEquipment();
    ~CapitalEquipment();
    probe *Probe;
    Can *pCan;

    BK2831E *pMeter;
    BK9200 *pMotorSupply;
    BK9200 *pCharger;

    //For test purposes
    //BK2831E *pTestMeter;
    //BK9200 *pTestMotorSupply;
    //BK9200 *pTestCharger;

    QString getPort(QString piece);

    char *meterPort;
    char *motorPort;
    char *chargerPort;
    //-----

    Dac *pDac;
    Relay *pRelay1;
    Relay *pRelay2;
    void create();
    int getCompletedStatus();

  private:
    int completed;
};

extern  CapitalEquipment *pce;
#endif
