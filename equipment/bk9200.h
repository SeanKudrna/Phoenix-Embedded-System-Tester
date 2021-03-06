#ifndef BK9200_H
#define BK9200_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "bk.h"
#include "SerialDevice.h"
#include <QList>
#include "types.h"


class BK9200 : public BK
{
    //Q_OBJECT
public:

    explicit BK9200(BK *parent = nullptr,const char *port =SERIAL_CHARGER,int baud = BK_BAUD,char terminationChar = LINE_FEED, QString idString = chargerID);


    ~BK9200(); //destructor
    // bool toVoltage(char *string,double *volt); /* convert the string to double voltage */


    void setVDC(double vdc); /* set supply to VDC */
    void setADC(double adc); /* set supply amps */
    double getVDC(void); /* read the voltage */
    double getADC(void); /* read the current */
    void remoteMode(bool set);/* remote or front panel opteration */

    void setSTEP(double step); /* set step for increase and descrease commands */
    void setSTEPA(double step); /* set step for increase and decrease commands (amps) */
    void increaseVOLTS(); /* increase volts by [STEP] */
    void decreaseVOLTS(); /* decrease volts by [STEP] */

    void increaseAMPS(); /* increase amps by [STEP] */
    void decreaseAMPS(); /* decrease amps by [STEP] */

    void setVOLTS(double voltage); /* sets output voltage to [voltage] */
    void setAMPS(double amps); /* sets amps to [AMPS] */

    void triggerVOLTS(int state); /* triggers voltage output */

    void clearErrors(); /* clears errors */

    void enableOutput(bool enable); /* enable output true */
private:



signals:

public slots:

};

#endif // BK9200_H
