#include "probe.h"
#include <QSerialPortInfo>
#include <capitalequipment.h>
#include <QTimer>

static const char *IDN   = {"*IDN?\n"};
static const char *REMOTE = {"SYST:REM\n"};

//Constructor
probe::probe()
{
    //Set defaults
    complete = false;

    //Setup timer, gather ports, and link timer with testAll() method
    timer = new QTimer(this);
    listPorts();
    connect(timer, SIGNAL(timeout()), this, SLOT(testAll()));
    timer->start(1000);
}

//listPorts() method. Creates a list of all available relevant serial ports
void probe::listPorts()
{
    //Loop through all available ports
    for (QSerialPortInfo serialPort : QSerialPortInfo::availablePorts())
    {

        //See if the available port is a USB serial port
        if (serialPort.portName().contains("USB"))

            //If it is, append it to the port list
            portList.append(serialPort.portName());

    }
}

//getStatus() method. Returns true when probe has finished.
bool probe::getStatus()
{
    return complete;
}

//List of different states in testAll()
enum states{
    SS_SEND,
    SS_RECIEVE,
    SS_COMPLETE
};

//Set starting state
static states state = SS_SEND;


//testAll() executes every second
void probe::testAll()
{

    //Switch based on current state
    switch(state)
    {

        //If SEND state
        case SS_SEND:{

            //Create a pointer to a char
            char *pChar;

            //Loop through availble port list created from listPorts()
            for (int i = 0; i < portList.size(); i++)
            {
                //Set pChar = char equivalent of port in portlist
                pChar = (char* ) portList[i].toLatin1().toStdString().c_str();

                //Create a new serial device with aquired port
                pSerial = new SerialDevice(nullptr, pChar, BK_BAUD, LINE_FEED);

                //If serial device was properly created
                if(pSerial)
                {
                    //Send IDN request
                    pSerial->sendMessage(REMOTE);
                    pSerial->sendMessage(IDN);

                    //Save port
                    curPort = portList[i];
                    //portList.pop_front();

                    //If there are still ports to check in port list
                    if (portList.size() != 0){

                        //Move on to next state
                        state = SS_RECIEVE;
                        break;
                    }
                 }
             }

             //If all ports in port list have been checked
             if (portList.size() == 0){

                 //Complete state machine
                 state = SS_COMPLETE;
             }

            break;
        }

        //If RECIEVE state
        case SS_RECIEVE:{

            //Create a string to store IDN result
            QString serialString;

            //Retrieve IDN result
            pSerial->getNextData(&serialString);

            //If result is found
            if(serialString != "")
            {
                //Set port = port we are currently working with
                piece.port = curPort;

                //If ID string contains known ID string for meter, or returns remote command
                if (serialString.contains(BK::meterID) || serialString.contains("SYST:REM"))
                {
                    //Set equipment type = meter
                    piece.equ = meter;
                }

                //If ID string contains known ID string for motor supply
                else if (serialString.contains(BK::supplyID))
                {
                    //Set equipment type = motor supply
                    piece.equ = motorSupply;
                }

                //If ID String contains known ID string for charger
                else if (serialString.contains(BK::chargerID))
                {
                    //Set equipment type = charger
                    piece.equ = chargerSupply;
                }

                //Now that piece.port and piece.equ have been aquired, append to pieces list
                pieces.append(piece);

                //Return to first state
                state = SS_SEND;

                 //remove port we have just processed from temp port list
                 portList.pop_front();
            }
            break;
        }

        //if COMPLETE state
        case SS_COMPLETE:{

           //Set complete bool = true to signal go ahead for equipment construction
           complete = true;

           //End timer
           timer->stop();
           break;
        }
    }
}

