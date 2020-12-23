#include "probe.h"
#include <QSerialPortInfo>
#include <capitalequipment.h>
#include <QTimer>

static const char *IDN   = {"*IDN?\n"};

//How do I set up the constructor?
probe::probe() //BK(parent,port,baud,terminationChar,idString)
{

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(testAll()));
    timer->start(1000);
    listPorts(); // populate portList so timer can access on creation
}


void probe::listPorts()
{
    for (QSerialPortInfo serialPort : QSerialPortInfo::availablePorts())
    {
        if (serialPort.portName().contains("USB"))
            portList.append(serialPort.portName());

    }
}

enum states{
    SS_SEND,
    SS_RECIEVE,
    SS_COMPLETE
};
static states state = SS_SEND;

void probe::testAll()
{
    switch(state)
    {
        case SS_SEND:{
            char *pChar;
            for (int i = 0; i < portList.size(); i++)
            {
                pChar = (char* ) portList[i].toLatin1().toStdString().c_str();
                pSerial = new SerialDevice(nullptr, pChar, BK_BAUD, LINE_FEED);

                if(pSerial)
                {
                    //Send IDN request
                    pSerial->sendMessage("SYST:REM\n");
                    pSerial->sendMessage(IDN);

                    //Save port, and pop value off the list
                    curPort = portList[i];
                    //portList.pop_front();

                    if (portList.size() != 0){
                        state = SS_RECIEVE;
                        break;
                    }
                    else{
                        state = SS_COMPLETE;
                        break;
                    }

                 }
             }
            break;
        }
        case SS_RECIEVE:{
            QString serialString;

            pSerial->getNextData(&serialString);

            if(serialString != "")
            {
                //if(serialString.contains("B&K Precision") || serialString.contains("2831E"))
                //{
                    piece.port = curPort;

                    if (serialString.contains(BK::meterID) || serialString.contains("SYST:REM"))
                    {
                        piece.equ = meter;
                    }
                    else if (serialString.contains(BK::supplyID))
                    {
                        piece.equ = motorSupply;
                    }
                    else if (serialString.contains(BK::chargerID))
                    {
                        piece.equ = chargerSupply;
                    }

                    pieces.append(piece);
                //}
                 state = SS_SEND;
                 portList.pop_front();
            }
            break;
        }
        case SS_COMPLETE:{
           timer->stop();
           break;
        }
    }
}

