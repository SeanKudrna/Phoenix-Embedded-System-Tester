#include "capitalequipment.h"
#include "./equipment/types.h"
#include "probe.h"


CapitalEquipment::CapitalEquipment(){
    pCan= new Can(0x00,0x00);

    //pMeter = new BK2831E(nullptr,SERIAL_PORT,BK_BAUD,LINE_FEED, BK::meterID);
    //pMotorSupply = new BK9200(nullptr,SERIAL_MOTOR,BK_BAUD,LINE_FEED, BK::supplyID);
    //pCharger = new BK9200(nullptr,SERIAL_CHARGER,BK_BAUD,LINE_FEED, BK::chargerID);

    //Handled by constructor
    //Probe->listPorts();
    //Probe->testAll();
    Probe = new probe();
    pDac = new Dac(0x60);
    pRelay1 = new Relay(0x20);
    pRelay2 = new Relay(0x40);
    //create();

}

CapitalEquipment::~CapitalEquipment(){
    delete pCan;
    delete pMeter;
    delete pMotorSupply;
    delete pDac;
    delete pRelay1;
    delete pRelay2;
}

void CapitalEquipment::create()
{

    for (int i = 0; i < Probe->pieces.size(); i++)
    {
        if (Probe->pieces[i].equ == meter)
        {
            pMeter = new BK2831E(nullptr, Probe->pieces[i].port.toLatin1().toStdString().c_str(), BK_BAUD, LINE_FEED, BK::meterID);
            completed++;
        }
        else if (Probe->pieces[i].equ == motorSupply)
        {
            pMotorSupply = new BK9200(nullptr, Probe->pieces[i].port.toLatin1().toStdString().c_str(), BK_BAUD, LINE_FEED, BK::supplyID);
            completed++;
        }
        else if (Probe->pieces[i].equ == chargerSupply)
        {
            pCharger = new BK9200(nullptr, Probe->pieces[i].port.toLatin1().toStdString().c_str(), BK_BAUD, LINE_FEED, BK::chargerID);
            completed++;
        }
    }
}
