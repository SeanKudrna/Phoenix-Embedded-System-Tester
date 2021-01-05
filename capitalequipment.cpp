#include "capitalequipment.h"
#include "./equipment/types.h"
#include "probe.h"
#include "QDebug"


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
    completed = 0;
}

CapitalEquipment::~CapitalEquipment(){
    delete pCan;
    delete pMeter;
    delete pMotorSupply;
    delete pCharger;
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
            QString port =  Probe->pieces[i].port;
            char* p = new char[port.length() + 1];
            strcpy(p, port.toLatin1().constData());


            pMeter = new BK2831E(nullptr, p, BK_BAUD, LINE_FEED, BK::meterID);
            this->completed++;
            delete[] p;

        }
        else if (Probe->pieces[i].equ == motorSupply)
        {
            QString port =  Probe->pieces[i].port;

            char* p = new char[port.length() + 1];
            strcpy(p, port.toLatin1().constData());


            pMotorSupply = new BK9200(nullptr, p , BK_BAUD, LINE_FEED, BK::supplyID);
            this->completed++;
            delete[] p;

        }
        else if (Probe->pieces[i].equ == chargerSupply)
        {
            QString port =  Probe->pieces[i].port;

            char* p = new char[port.length() + 1];
            strcpy(p, port.toLatin1().constData());


            pCharger = new BK9200(nullptr, p, BK_BAUD, LINE_FEED, BK::chargerID);
            this->completed++;
            delete[] p;

        }
    }
}

int CapitalEquipment::getCompletedStatus()
{
    return completed;
}
