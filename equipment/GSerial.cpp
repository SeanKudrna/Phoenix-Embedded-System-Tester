#include <QtGlobal>
#include "GSerial.h"
#include <QtSerialPort/QSerialPort>


GSerial::GSerial(QObject *parent) : QObject(parent)
{

     pPort = new QSerialPort();
     ptimer = new QTimer();


     connect(ptimer,SIGNAL(timeout()),this,SLOT(timerTimeOut()));


     Q_ASSERT(pPort != nullptr);

    if(pPort){

        pPort->setBaudRate(1200);
        pPort->setParity(QSerialPort::Parity::NoParity);
        pPort->setStopBits(QSerialPort::StopBits::OneStop);
        pPort->setDataBits(QSerialPort::DataBits::Data8);
        pPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
        connect(pPort, &QSerialPort::readyRead , this, &GSerial::readyReadSlot);
    }
    tick =0;
    messageIndex =0;

    ptimer->start(1000);// 1 second tick
}

GSerial::~GSerial(){
      Q_ASSERT(pPort != nullptr);

    if(pPort){
        pPort->close();
        delete pPort;
        pPort = nullptr;
    }
}

void GSerial::timerTimeOut(){
    ++tick;
}
void GSerial::getPortName(char *p){
    strcpy(p,this->portName);
}
int GSerial::getBaudrate(){
    return this->baudRate;
}
bool GSerial::open(const char *portName,int baudrate, char terminationChar){
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
void GSerial::sendMessage(char *pMessage){
      Q_ASSERT(pPort != nullptr);
    if(pPort){
        pPort->write(pMessage,strlen(pMessage));
    }
}
void GSerial::sendMessage(const char *pMessage){
      Q_ASSERT(pPort != nullptr);
    if(pPort){
        pPort->write(pMessage,strlen(pMessage));
    }
}
/* set the char that inicates end of string from device */
void GSerial::setTerminationChar(char terminationChar){
    this->terminationChar = terminationChar;
}

int GSerial::getTick(void){
    return tick;
}

void GSerial::readyReadSlot() {
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


