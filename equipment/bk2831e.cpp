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


BK2831E::~BK2831E(){
    // fixme send the quit thread signal
  //  serialThread->quit();
  //  while(serialThread->isRunning());
  //  serialObject->deleteLater();
  // serialThread->deleteLater();

  //
    // delete the thread
    // delete the port
}


 
BK2831E::BK2831E(BK *parent, const char *port,int baud,char terminationChar):BK(parent,port,baud,terminationChar)
{
}



void BK2831E::trigger(void){ /* send the trigger caommand */
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(TRIG));
    }
}
void BK2831E::setVAC(void){ /* set meter to VAC */
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(VAC));
    }
}
void BK2831E::setOHMS(void){ /* set meter to OHMS */
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(OHMS));
    }
}
void BK2831E::setVDC(void){ /* set meter to VDC */
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(VDC));
    }
}
void BK2831E::setReference(bool enable){ /* enable/disable reference reading */
    if(pSerialDevice){
        if(enable){
         pSerialDevice->sendMessage(CC_CHAR(REF));
        }
        else{
         pSerialDevice->sendMessage(CC_CHAR(NO_REF));
        }
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
void BK2831E::measure(void){ /* make a reading */
    QString data;
    if(pSerialDevice){
         pSerialDevice->sendMessage(CC_CHAR(FETCH));
    }
}
#undef CC_CHAR

