#include <QtGlobal>
#include "G2Serial.h"
#include <QtSerialPort/QSerialPort>



G2Serial::G2Serial(QObject *parent) : QObject(parent),tick(0),messageIndex(0)
{

     pPort = new QSerialPort();
     ptimer = new QTimer();
     pRxThread = new SerialRxThread();

     connect(ptimer,SIGNAL(timeout()),this,SLOT(timerTimeOut()));


     Q_ASSERT(pPort != nullptr);

    if(pPort){

        pPort->setBaudRate(1200);
        pPort->setParity(QSerialPort::Parity::NoParity);
        pPort->setStopBits(QSerialPort::StopBits::OneStop);
        pPort->setDataBits(QSerialPort::DataBits::Data8);
        pPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    //    connect(pPort, &QSerialPort::readyRead , this, &G2Serial::readyReadSlot);
    }
    if(pRxThread){
        pRxThread->init(pPort,&messageList);
        pRxThread->start();
    }

    ptimer->start(1000);// 1 second tick
}

G2Serial::~G2Serial(){
      Q_ASSERT(pPort != nullptr);

    if(pPort){
        pPort->close();
        delete pPort;
        pPort = nullptr;
    }
}

void G2Serial::timerTimeOut(){
    ++tick;
}
void G2Serial::getPortName(char *p){
    strcpy(p,this->portName);
}
int G2Serial::getBaudrate(){
    return this->baudRate;
}
bool G2Serial::open(char *portName,int baudrate, char terminationChar){
    bool status = true;
      Q_ASSERT(pPort != nullptr);
    if(pPort){
         this->terminationChar = terminationChar;
         strcpy(this->portName,portName);
         this->baudRate = baudrate;
         pPort->setBaudRate(baudrate);
         pPort->setPortName(portName);
         status = pPort->open(QSerialPort::OpenModeFlag::ReadWrite);
    }
    return status;
}

/* send a message over serial port */
void G2Serial::sendMessage(char *pMessage){
      Q_ASSERT(pPort != nullptr);
    if(pPort){
        pPort->write(pMessage,strlen(pMessage));
    }
}

/* set the char that inicates end of string from device */
void G2Serial::setTerminationChar(char terminationChar){
    this->terminationChar = terminationChar;
}

int G2Serial::getTick(void){
    return tick;
}
#if(0)
void G2Serial::readyReadSlot() {
    qint64  bytesAvailable;

    bytesAvailable = pPort->bytesAvailable();

    Q_ASSERT(pPort != nullptr);

    if(pPort){ // pPort is valid

        // read chars
        while(bytesAvailable>0){
            bytesAvailable--;
            pPort->read(&message[messageIndex],1);  //  read a byte

            if(terminationChar == message[messageIndex]){
                message[messageIndex] =0;
                qDebug(message);
                emit readyReadSignal(QString(message));

                messageIndex =0;
            }
            else{
                ++messageIndex;
                if(messageIndex > MAX_BUFFER){
                    messageIndex =0;
                }
            }// while
        }
    }//  if(pPort)
}

#endif

