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

    Dac *pDac;
    Relay *pRelay1;
    Relay *pRelay2;
    int completed;
    void create();
  private:
};

extern  CapitalEquipment *pce;
#endif
