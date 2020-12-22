#include "probe.h"
#include <QSerialPortInfo>
#include <capitalequipment.h>
#include <QTimer>



//How do I set up the constructor?
probe::probe() //BK(parent,port,baud,terminationChar,idString)
{

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(testAll()));
}

void probe::listPorts()
{
    for (QSerialPortInfo serialPort : QSerialPortInfo::availablePorts())
    {
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
                    pSerial->sendMessage("*IDN>\n");

                    //Save port, and pop value off the list
                    curPort = portList[i];
                    portList.pop_front();

                    if (portList.size() != 0)
                        state = SS_RECIEVE;
                    else
                        state = SS_COMPLETE;

                    break;
                 }
             }
        }
        case SS_RECIEVE:{
            QString serialString;

            pSerial->getNextData(&serialString);

            if(serialString != "")
            {
                piece.port = curPort;

                if (serialString.contains(BK::meterID))
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
                state = SS_SEND;
                break;
            }
        }
        case SS_COMPLETE:{
           break;
        }
    }
}
