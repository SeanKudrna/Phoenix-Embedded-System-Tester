#include "../equipment/bk.h"
#include <QtGlobal>
#include <QString>


#define CC_CHAR const_cast<char*>

static const char *IDN   = {"*IDN?\n"};
static const char *RESET = {"*RST\n"};

BK::~BK(){
#if(0)
    // fixme send the quit thread signal
    serialThread->quit();
    while(serialThread->isRunning());
    serialObject->deleteLater();
    serialThread->deleteLater();
#endif

    // delete the thread

    // delete the port
}

void BK::getPort(char *pPort){
    strcpy(pPort,this->port);
}

int BK::getBaud(void){
    return this->baud;
}

char BK::getTerminationChar(void){
    return this->terminationChar;
}


/*
BK::BK(QObject *parent, const char *port,int baud,char terminationChar) : QObject(parent)
{
    strcpy(this->port,port);
    this->baud = baud;
    this->terminationChar = terminationChar;

    pSerialDevice = new SerialDevice(nullptr,port,baud,terminationChar);
}
*/

BK::BK(QObject *parent, const char *port,int baud,char terminationChar, QString idString) : QObject(parent)
{
    strcpy(this->port,port);
    this->baud = baud;
    this->terminationChar = terminationChar;
    this->idString = idString;

    pSerialDevice = new SerialDevice(nullptr,port,baud,terminationChar);
}

bool BK::equipmentValidation(QString idString)
{
    if (idString.contains(this->idString))
        return true;

    return false;
}


void BK::getId(void){ /* request the identification of the meter */
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(IDN));
    }
}

void BK::reset(void){ /* force reset of device */
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


/* take from the data list */
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
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
/* clear the data list  of measurements */
void BK::clearDataList(void){
    if(pSerialDevice)
        pSerialDevice->clearDataList();
}


void  BK::appendValue(QString *pString,double value){
    QString val;
    val = QString::number(value);
    pString->append(val);
    pString->append("\n");
}

void  BK::appendValue(QString *pString,int value){
    QString val;
    val = QString::number(value,10);
    pString->append(val);
    pString->append("\n");
}

bool BK::toVoltage(char *string,double *volt){  /* convert the string to double voltage */
    bool ok;
    *volt = QString(string).toDouble(&ok);
    return true;
}

#undef CC_CHAR
