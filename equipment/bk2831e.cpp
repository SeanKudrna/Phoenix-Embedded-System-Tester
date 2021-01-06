#include "bk2831e.h"

#define CC_CHAR const_cast<char*>

static const char *FETCH = {"FETCH?\n"};

#if(0)
static const char *RESET = {"*RST\n"};
static const char *VDC   = {"VOLT:DC:RANGE:AUTO:1\n"};
static const char *VAC   = {"VOLT:AC:RANGE:AUTO:1\n"};

#endif
static const char *VDC   = {":FUNC VOLT:DC\n"};
static const char *VAC   = {":FUNC VOLT:AC\n"};
static const char *OHMS  = {":FUNC RES\n"};

static const char *TRIG  = {"*TRG\n"};
static const char *NO_REF= {"VOLT:DC:REF:STATE 0"};
static const char *REF   = {"VOLT:DC:REF:STATE 1"};


class SleeperThread:public QThread{
public:
    static void msleep(unsigned long msecs){
        QThread::msleep(msecs);
    }
};


//Deconstructor
BK2831E::~BK2831E(){
}

//Constructor
BK2831E::BK2831E(BK *parent, const char *port,int baud,char terminationChar, QString idString):BK(parent,port,baud,terminationChar, idString)
{
}


//Send the trigger command
void BK2831E::trigger(void){
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(TRIG));
    }
}

//Set the meter to VAC
void BK2831E::setVAC(void){
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(VAC));
    }
}

//Set the meter to OHMS
void BK2831E::setOHMS(void){
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(OHMS));
    }
}

//Set the meter to VDC
void BK2831E::setVDC(void){
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(VDC));
    }
}

//Enable/disable reference reading
void BK2831E::setReference(bool enable){
    if(pSerialDevice){
        if(enable)
            pSerialDevice->sendMessage(CC_CHAR(REF));

        else
            pSerialDevice->sendMessage(CC_CHAR(NO_REF));
    }
}

#if(0)
void BK2831E::reset(void){ /* reset the meter */
    QString reply;
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(RESET));
    }
}

#endif

//Make a meter reading
void BK2831E::measure(void){
    QString data;
    if(pSerialDevice){
         pSerialDevice->sendMessage(CC_CHAR(FETCH));
    }
}
#undef CC_CHAR

