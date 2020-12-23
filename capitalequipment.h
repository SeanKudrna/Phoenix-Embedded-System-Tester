#ifndef CAPITALEQUIPMENT_H
#define CAPITALEQUIPMENT_H

#include "relay.h"
#include "can.h"
#include "./equipment/bk2831e.h"
#include "./equipment/bk9200.h"
#include "dac.h"


class CapitalEquipment{

public:
    CapitalEquipment();
    ~CapitalEquipment();
    Can *pCan;
    BK2831E *pMeter;
    BK9200 *pMotorSupply;
    BK9200 *pCharger;
    Dac *pDac;
    Relay *pRelay1;
    Relay *pRelay2;
  private:
};

extern  CapitalEquipment *pce;
#endif
