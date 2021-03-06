#include "../equipment/bk9200.h"
#include <QtGlobal>

#define CC_CHAR const_cast<char*>

#if(0)
static const char *IDN   = {"*IDN?\n"};
static const char *RESET = {"*RST\n"};
#endif

static const char *REMOTE = {"SYST:REM\n"};



static const char *FETCH = {"FETCH?\n"};
static const char *SET_REMOTE   = {"SYST:REM\n"}; /* remote mode */
static const char *SET_LOCK   = {"SYST:LOC\n"}; /* front panel operation */

static const char *GET_VDC   = {"MEAS:VOLT?\n"}; /* append with the double voltage value */
static const char *GET_ADC  = {"MEAS:CURR?\n"}; /* append with the double current value */

static const char *SET_VDC  = {"SOUR:VOLT "}; /* append with the double voltage value */
static const char *SET_ADC = {"SOUR:CUR "}; /* append with the double current value */
static const char *OUTPUT = {"SOUR:OUTP "}; /* append with 1/0 for enable disable */

static const char *SET_STEP = {"VOLT:STEP "}; /* set [STEP] for volage UP and DOWN */
static const char *SET_STEPA = {"CURR:STEP "}; /* set [STEP] for volage UP and DOWN */

static const char *UP = {"VOLT UP\n"}; /* increase voltage by [STEP] */
static const char *DOWN = {"VOLT DOWN\n"}; /* decrease voltage by [STEP] */

static const char *UPA = {"CURR UP\n"}; /* increase amps by [STEP] */
static const char *DOWNA = {"CURR DOWN\n"}; /* decrease amps by [STEP] */

static const char *SET_VOLT = {"VOLT "}; /* set output voltage */
static const char *SET_AMP = {"CURR "}; /* set amps to [AMPS] */

static const char *TRIG_VOLT = {"OUTP:STAT "}; /* trigger voltage output */


static const char *TRIG  = {"*TRG\n"};
static const char *CLEAR = {"*CLS\n"}; /* clear errors */
static const char *NO_REF ={"VOLT:DC:REF:STATE 0"};


//Deconstructor
BK9200::~BK9200(){
}

//Constructor
BK9200::BK9200(BK *parent, const char *port,int baud,char terminationChar, QString idString) : BK(parent,port,baud,terminationChar,idString){
}

//Enable voltage output (on/off)
void BK9200::enableOutput(bool enable){
    QString msg = QString(OUTPUT);
    appendValue(&msg, (int)enable);

    Q_ASSERT(pSerialDevice != nullptr);
    if(pSerialDevice){
        pSerialDevice->sendMessage(&msg);
    }
}

//Remote or fronttextEdit panel opteration
void BK9200::remoteMode(bool set){
    if(pSerialDevice){
        if(set)
            pSerialDevice->sendMessage(CC_CHAR(SET_REMOTE));

        else
            pSerialDevice->sendMessage(CC_CHAR(SET_LOCK));
    }
}

//Get ADC
double BK9200:: getADC(void){
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(GET_ADC));
    }
    return 0;
}

//Get VDC
double BK9200::getVDC(void){
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(GET_VDC));
    }

    return 0;
}

//Set ADC
void BK9200::setADC(double val){
    QString msg = QString(SET_ADC);

    appendValue(&msg, val);

    if(pSerialDevice){
        pSerialDevice->sendMessage(&msg);
    }
}

//Set VDC
void BK9200::setVDC(double val){
    QString msg = QString(SET_VDC);

    appendValue(&msg, val);

    if(pSerialDevice){
        pSerialDevice->sendMessage(&msg);
    }
}

//Set voltage step
void BK9200::setSTEP(double val){
    QString msg = QString(SET_STEP);

    appendValue(&msg, val);

    if(pSerialDevice){
        pSerialDevice->sendMessage(&msg);
    }
}

//Set amp step
void BK9200::setSTEPA(double val){
    QString msg = QString(SET_STEPA);

    appendValue(&msg, val);

    if(pSerialDevice){
        pSerialDevice->sendMessage(&msg);
    }
}

//Increase volts
void BK9200::increaseVOLTS()
{
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(UP));
    }
}

//Decrease volts
void BK9200::decreaseVOLTS()
{
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(DOWN));
    }
}

//Increase amps
void BK9200::increaseAMPS()
{
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(UPA));
    }
}

//Decrease amps
void BK9200::decreaseAMPS()
{
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(DOWNA));
    }
}

//Set volts
void BK9200::setVOLTS(double voltage)
{
    QString msg = QString(SET_VOLT);

    appendValue(&msg, voltage);

    if(pSerialDevice){
        pSerialDevice->sendMessage(&msg);
    }
}

//Set amps
void BK9200::setAMPS(double amps)
{
    QString msg = QString(SET_AMP);

    appendValue(&msg, amps);

    if(pSerialDevice){
        pSerialDevice->sendMessage(&msg);
    }
}

//Trigger volts
void BK9200::triggerVOLTS(int state)
{
    QString msg = QString(TRIG_VOLT);
    appendValue(&msg, state);

    if(pSerialDevice){
        pSerialDevice->sendMessage(&msg);
    }

}

//Clear logged errors
void BK9200::clearErrors()
{
    if(pSerialDevice){
        pSerialDevice->sendMessage(CC_CHAR(CLEAR));
    }
}

#undef CC_CHAR
