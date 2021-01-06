#include "../equipment/bk.h"
#include <QtGlobal>
#include <QString>


#define CC_CHAR const_cast<char*>

static const char *IDN   = {"*IDN?\n"};
static const char *RESET = {"*RST\n"};


const QString BK::meterID = {"2831E  Multimeter"};
const QString BK::supplyID = {"B&K Precision, 9205"};
const QString BK::chargerID  = {"B&K Precision, 9201"};

BK::~BK(){
#if(0)
    // fixme send the quit thread signal
    serialThread->quit();
    while(serialThread->isRunning());
    serialObject->deleteLater();
    serialThread->deleteLater();
#endif
}

//Get port
void BK::getPort(char *pPort){
    strcpy(pPort,this->port);
}

//Get baud
int BK::getBaud(void){
    return this->baud;
}

//get termination char
char BK::getTerminationChar(void){
    return this->terminationChar;
}

//Set this->port
void BK::setPort(char *pPort){
     strcpy(port, pPort);
}

//Constructor
BK::BK(QObject *parent, const char *port,int baud,char terminationChar, QString idString) : QObject(parent)
{
    strcpy(this->port,port);
    this->baud = baud;
    this->terminationChar = terminationChar;
    this->idString = idString;

    pSerialDevice = new SerialDevice(nullptr,port,baud,terminationChar);
}

//Validates equipment with idStrings
bool BK::equipmentValidation(QString idString)
{
    //If idString contains a known idString, return true
    if (idString.contains(this->idString))
        return true;

    //Otherwise, return false
    return false;
}

//Request the identification of the meter
void BK::getId(void){
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(IDN));
    }
}

//Force reset of device
void BK::reset(void){
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(RESET));
    }
}


/**
 * @brief getNumber
 * Remove any text command that follows the meter reading.
 *
 * @param pTarget - pointer to the QString with meter message
 * @param pSource - pointer to the QString with only meter reading
 */
void getNumber(QString *pTarget,QString *pSource){
    int n;
    pSource->contains('\r',Qt::CaseSensitive);
    n= pSource->indexOf('\r',0);
    *pTarget = pSource->left(n);
}

//Get data returned from command call given a string
bool BK::getNextData(QString *data){
    bool status = true;
    QString message;

    if(pSerialDevice){
        if( pSerialDevice->getNextData(&message)){
            getNumber(data,&message);
        }
    }

    if(0 == data->length()){
        status = false;
    }

    return status;
}

//Get data returned from command call given an int
bool BK::getNextData(int *data){
    bool ok = false;
    QString message;
    QString left;

    if(pSerialDevice){
        if( pSerialDevice->getNextData(&message)){
            getNumber(&left,&message);
            *data = message.toInt(&ok);
        }
    }

    else{
        ok = false;
    }

    return ok;
}


//Take from the data list
bool BK::getNextData(double *data){
    bool ok = false;
    QString message;
    QString left;

    if(pSerialDevice){
        if( pSerialDevice->getNextData(&message)){
            getNumber(&left,&message);
            *data = left.toDouble(&ok);

            if(0.0 == *data)
                return false;

            else
                return true ;
        }

        else
            return false;
    }

    else
        return false;
}

//Clear the data list  of measurements
void BK::clearDataList(void){
    if(pSerialDevice)
        pSerialDevice->clearDataList();
}

//Add a double
void  BK::appendValue(QString *pString,double value){
    QString val;
    val = QString::number(value);
    pString->append(val);
    pString->append("\n");
}

//Add a int
void  BK::appendValue(QString *pString,int value){
    QString val;
    val = QString::number(value,10);
    pString->append(val);
    pString->append("\n");
}

//Convert the string to double voltage
bool BK::toVoltage(char *string,double *volt){
    bool ok;
    *volt = QString(string).toDouble(&ok);
    return true;
}

#undef CC_CHAR
