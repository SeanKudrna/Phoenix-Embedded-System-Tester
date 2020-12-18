#include "capitalequipment.h"
#include "./equipment/types.h"


CapitalEquipment::CapitalEquipment(){
    pCan= new Can(0x00,0x00);
    //pMeter = new BK2831E(nullptr,SERIAL_MOTORSUPPLY,BK_BAUD,LINE_FEED);
    //pMotorSupply = new BK9200(nullptr,SERIAL_PORT,BK_BAUD,LINE_FEED);

    pMeter = new BK2831E(nullptr,SERIAL_PORT,BK_BAUD,LINE_FEED);
    pMotorSupply = new BK9200(nullptr,SERIAL_MOTORSUPPLY,BK_BAUD,LINE_FEED);
    //BK9200 *pCharger;
    pDac = new Dac(0x60);
    pRelay1 = new Relay(0x20);
    pRelay2 = new Relay(0x40);
}

CapitalEquipment::~CapitalEquipment(){
    delete pCan;
    delete pMeter;
//   delete pMotorSupply;
    delete pDac;
    delete pRelay1;
    delete pRelay2;
}
