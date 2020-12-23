#include "SerialDevice.h"


SerialDevice::~SerialDevice(){
    // fixme send the quit thread signal
    //  serialThread->quit();
    //  while(serialThread->isRunning());
    //  serialObject->deleteLater();
    // serialThread->deleteLater();


    // delete the thread
    // delete the port
}

void SerialDevice::sendMessage(const char *pMessage){
    //clearDataList(); // clear the reply on a send

    this->command = QString(pMessage);
    this->messageFlag = false;
    serialObject->sendMessage(pMessage);
}

void SerialDevice::sendMessage(char *pMessage){
    //clearDataList(); // clear the reply on a send

    this->command = QString(pMessage);
    this->messageFlag = false;
    serialObject->sendMessage(pMessage);
}

void SerialDevice::sendMessage(QString *pMessage){

    char *pChar;
    QByteArray byteArray;

    // save the command so you can strip it from the reply
    this->command = *pMessage;

    // convert from QString to char pointer
    byteArray = pMessage->toLocal8Bit();
    pChar = byteArray.data();

    // send the message out the serial port
    serialObject->sendMessage(pChar);

}



SerialDevice::SerialDevice(QObject *parent, const char *port,int baud,char terminationChar) : QObject(parent)
{
    serialThread = new QThread; // create the new thread
    serialObject = new GSerial(); // create new object, no parent allowed

    messageFlag = false;

    if((serialObject != nullptr) && (serialThread != nullptr)){
       //fixme send in the baud and the port
        serialObject->open(port,baud,terminationChar);


        serialObject->moveToThread(serialThread);

        // START
        connect(serialThread, &QThread::started, serialObject, &GSerial::readyReadSlot);

        // DONE
        connect(serialObject, &GSerial::doneProcessSignal, serialThread, &QThread::quit);
        connect(serialObject, &GSerial::doneProcessSignal, serialObject, &GSerial::deleteLater);

        connect(serialThread, &QThread::finished, serialObject, &GSerial::deleteLater);

        // TRANSMIT
        connect(serialObject, &GSerial::readyReadSignal, this, &SerialDevice::handleReadyReadSlot);

        serialThread->start();
    }
}

/* take from the data list */
bool SerialDevice::getNextData(QString *data){
    bool status = false;
    if(dataList.size()){
        *data = dataList.front();
         dataList.pop_front();
         status = true;
    }
    return status;
}

void SerialDevice::removeLast(){
    if(dataList.size())
    {
        dataList.pop_front();
    }
}
/* clear the data list  of measurements*/
void SerialDevice::clearDataList(void){
    dataList.clear();
}

void SerialDevice::handleReadyReadSlot(QString res) {
    if(!this->command.contains(res)){
        dataList.push_back(res);
        this->messageFlag = true;
    }
}

bool SerialDevice::getMessageFlag(void){
    return messageFlag;
}
