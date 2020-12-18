#include "Serial2Device.h"


Serial2Device::~Serial2Device(){
    // fixme send the quit thread signal
  //  serialThread->quit();
  //  while(serialThread->isRunning());
  //  serialObject->deleteLater();
  // serialThread->deleteLater();

  //
    // delete the thread
    // delete the port
}

void Serial2Device::sendMessage(char *pMessage){
    //clearDataList(); // clear the reply on a send

    this->command = QString(pMessage);
    this->messageFlag = false;
    serialObject->sendMessage(pMessage);



}

void Serial2Device::sendMessage(QString *pMessage){

    char *pChar;
    QByteArray byteArray;

    // save the command so you can strip it from the reply
    this->command = *pMessage;

    // convert from QString to char pointer
    byteArray = pMessage->toLocal8Bit();
    pChar = byteArray.data();

    // clear the list of replies
    clearDataList(); // clear the reply on a send

    // send the message out the serial port
    serialObject->sendMessage(pChar);

}



Serial2Device::Serial2Device(QObject *parent, char *port,int baud,char terminationChar) : QObject(parent)
{
    //serialThread = new QThread; // create the new thread
    serialObject = new G2Serial(); // create new object, no parent allowed

    messageFlag = false;

    if((serialObject != nullptr) ){
    //if((serialObject != nullptr) && (serialThread != nullptr)){
       //fixme send in the baud and the port
        serialObject->open((char *)port,baud,terminationChar);


     //   serialObject->moveToThread(serialThread);

        // START
      //  connect(serialThread, &QThread::started, serialObject, &G2Serial::readyReadSlot);

        // DONE
       // connect(serialObject, &G2Serial::doneProcessSignal, serialThread, &QThread::quit);
        connect(serialObject, &G2Serial::doneProcessSignal, serialObject, &G2Serial::deleteLater);

        //connect(serialThread, &QThread::finished, serialObject, &G2Serial::deleteLater);

        // TRANSMIT
        //connect(serialObject, &G2Serial::readyReadSignal, this, &Serial2Device::handleReadyReadSlot);

       // serialThread->start();
    }
}

/* take from the data list */
bool Serial2Device::getNextData(QString *data){
    if(dataList.size()){
        *data = dataList.front();
         dataList.pop_front();
    }
}
/* clear the data list  of measurements */
void Serial2Device::clearDataList(void){
    dataList.clear();
}

void Serial2Device::handleReadyReadSlot(QString res) {

#if(0)
    // the commands to the DMM are echoed back, strip them off.
    if(!this->command.contains(res)){
        dataList.push_back(res);
        this->messageFlag = true;
    }
#endif
}

bool Serial2Device::getMessageFlag(void){
    return messageFlag;
}
