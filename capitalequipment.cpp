#include "capitalequipment.h"
#include "./equipment/types.h"
#include "probe.h"
#include "QDebug"


//Constructor
CapitalEquipment::CapitalEquipment(){

    //Non BK equipment object construction
    pCan= new Can(0x00,0x00);
    Probe = new probe();
    pDac = new Dac(0x60);
    pRelay1 = new Relay(0x20);
    pRelay2 = new Relay(0x40);
    completed = 0;

    //-------------------WORKING -> CONSTRUCT WITHOUT SERIAL DETECTION----------------------------------

    //Below are there statments needed to allow the program to run without serial detection.
    //The values SERIAL_PORT, SERIAL_MOTOR, and SERIAL CHARGER are set to default ttyUSB ports
    //ttyUSB0 = SERIAL_PORT
    //ttyUSB1 = SERIAL_MOTOR
    //ttyUSB2 = SERIAL_CHARGER


    pMeter = new BK2831E(nullptr,SERIAL_PORT,BK_BAUD,LINE_FEED, BK::meterID);

    pMotorSupply = new BK9200(nullptr,SERIAL_MOTOR,BK_BAUD,LINE_FEED, BK::supplyID);

    pCharger = new BK9200(nullptr,SERIAL_CHARGER,BK_BAUD,LINE_FEED, BK::chargerID);


    //---------------------------------------------------------------------------------------------------


    //----------------------UPDATE PORT AFTER CONSTRUCTION ATTEMPT------------------------------------

    //Below is a solution I attempted. It constructs the equipment objects using a null serial port
    //then later, in create() the serial port of these objects is updated using a setter method I've
    //created in BK. After testing with a debugger, object ports are correctly updated, yet Application
    //Output still shows the serial ports as closed.

    /*
    pMeter = new BK2831E(nullptr,"",BK_BAUD,LINE_FEED, BK::meterID); //SERIAL_PORT

    pMotorSupply = new BK9200(nullptr,"",BK_BAUD,LINE_FEED, BK::supplyID); //SERIAL_MOTOR

    pCharger = new BK9200(nullptr,"",BK_BAUD,LINE_FEED, BK::chargerID); //SERIAL_CHARGER
    */

    //---------------------------------------------------------------------------------------------------

    //----------------------CONSTRUCT AND GET PORT AT SAME TIME ATTEMPT----------------------------------

    //Below is another solution I attempted. It constructs the equipment objects using a getPort() method
    //that I wrote in hopes of being able to construct the objects at the same time as finding their ports
    //using a getPort() method that takes a QString value to signify which port you are trying to find.
    //This resulted in an application crash.

    /*
    pMeter = new BK2831E(nullptr, getPort("meter"), BK_BAUD, LINE_FEED, BK::meterID);

    pMotorSupply = new BK9200(nullptr, getPort("motor"), BK_BAUD, LINE_FEED, BK::supplyID);

    pCharger = new BK9200(nullptr, getPort("charger"), BK_BAUD, LINE_FEED, BK::chargerID);
    */

    //---------------------------------------------------------------------------------------------------
}

//Deconstructor
CapitalEquipment::~CapitalEquipment(){
    delete pCan;
    delete pMeter;
    delete pMotorSupply;
    delete pCharger;
    delete pDac;
    delete pRelay1;
    delete pRelay2;
}//EOF Deconstructor

//getPort() function. Written for purposes of "CONSTRUCT
//AND GET PORT AT SAME TIME ATTEMPT" in constructor.
char* CapitalEquipment::getPort(QString equipmentPiece)
{
    //If equipment = DMM
    if (equipmentPiece == "meter")
    {
        //Go through list of equipment pieces
        for (int i = 0; i < Probe->pieces.size(); i++)
        {
            //Find the correct piece
            if (Probe->pieces[i].equ == meter)
            {
                //Find and return the port of that equipment piece
                char* p = new char[Probe->pieces[i].port.length() + 1];
                strcpy(p, Probe->pieces[i].port.toLatin1().constData());
                return p;
            }//EOF if
        }//EOF for
    }//EOF if

    //If equipment = BK2905
    else if (equipmentPiece == "motor")
    {
        //Go through list of equipment pieces
         for (int i = 0; i < Probe->pieces.size(); i++)
         {
             //Find the correct piece
             if (Probe->pieces[i].equ == motorSupply)
             {
                 //Find and return the port of that equipment piece
                 char* p = new char[Probe->pieces[i].port.length() + 1];
                 strcpy(p, Probe->pieces[i].port.toLatin1().constData());
                 return p;
             }//EOF if
         }//EOF for
    }//EOF else if

    //If equipment = BK2901
    else if (equipmentPiece == "charger")
    {
        //Go through list of equipment pieces
        for (int i = 0; i < Probe->pieces.size(); i++)
        {
            //Find the correct piece
            if (Probe->pieces[i].equ == chargerSupply)
            {
                //Find and return the port of that equipment piece
                char* p = new char[Probe->pieces[i].port.length() + 1];
                strcpy(p, Probe->pieces[i].port.toLatin1().constData());
                return p;
            }//EOF if
        }//EOF for
    }//EOF else if
}//EOF getPort()

//create() function. Creates equipment objects after probe executes and completes.
//called from mainwindow.cpp.
void CapitalEquipment::create()
{
    //Go through the list of equipment pieces
    for (int i = 0; i < Probe->pieces.size(); i++)
    {
        //If equipment = DMM
        if (Probe->pieces[i].equ == meter)
        {
            //Get port, convert to const char* and create object.
            //If new object construction is commented out, setPort() changes
            //already created object's port for the purpose of "UPDATE PORT PRIOR TO
            //CONSTRUCTION ATTEMPT" in construtor.
            QString port =  Probe->pieces[i].port;
            char* p = new char[port.length() + 1];
            strcpy(p, port.toLatin1().constData());

            //Update port
            pMeter->setPort(p);

            //Create object
            //pMeter = new BK2831E(nullptr, p, BK_BAUD, LINE_FEED, BK::meterID);

            //Update completed to show another equipment object was created
            this->completed++;

            //Delete memory associated with port
            delete[] p;
        }//EOF if

        //If equipment = BK2905
        else if (Probe->pieces[i].equ == motorSupply)
        {
            //Get port, convert to const char* and create object.
            //If new object construction is commented out, setPort() changes
            //already created object's port for the purpose of "UPDATE PORT PRIOR TO
            //CONSTRUCTION ATTEMPT" in construtor.
            QString port =  Probe->pieces[i].port;
            char* p = new char[port.length() + 1];
            strcpy(p, port.toLatin1().constData());

            //Update port
            pMotorSupply->setPort(p);

            //Create object
            //pMotorSupply = new BK9200(nullptr, p , BK_BAUD, LINE_FEED, BK::supplyID);

            //Update completed to show another equipment object was created
            this->completed++;

            //Delete memory associated with port
            delete[] p;
        }//EOF else if

        //If equipment = BK2901
        else if (Probe->pieces[i].equ == chargerSupply)
        {
            //Get port, convert to const char* and create object.
            //If new object construction is commented out, setPort() changes
            //already created object's port for the purpose of "UPDATE PORT PRIOR TO
            //CONSTRUCTION ATTEMPT" in construtor.
            QString port =  Probe->pieces[i].port;
            char* p = new char[port.length() + 1];
            strcpy(p, port.toLatin1().constData());

            //Update port
            pCharger->setPort(p);

            //Create object
            //pCharger = new BK9200(nullptr, p, BK_BAUD, LINE_FEED, BK::chargerID);

            //Update completed to show another equipment object was created
            this->completed++;

            //Delete memory associated with port
            delete[] p;
        }//EOF else if
    }//EOF for
}//EOF Create()

//getCompletedStatus() function. Returns how many equipment
//objects have been created/had their ports updated.
int CapitalEquipment::getCompletedStatus()
{
    return completed;
}//EOF getCompletedStatus()
