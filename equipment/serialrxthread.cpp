#include "serialrxthread.h"

SerialRxThread::SerialRxThread(){

}
void SerialRxThread::init(QSerialPort *pPort,QList <QString> *pList){
    this->pPort = pPort;
    this->pList = pList;
    this->_stop = false;
    qDebug()<< "THREAD INit";
}
void SerialRxThread::run(){

    QMutex mutex;
    qDebug()<< "THREAD run";

    while(1){

        mutex.lock();
        if(this->_stop){
           break;
        }
        mutex.unlock();

        if(pPort->bytesAvailable()){
          this->msleep(10);
          byteArray =  pPort->readAll();
          pList->push_back(QString(byteArray));
          qDebug()<< "PUSH MSG";
        }

        this->msleep(100);
    }
          qDebug()<< "exit ";

}
void SerialRxThread::stop(){
    _stop = true;
    qDebug()<< "THREAD STOP";
}
