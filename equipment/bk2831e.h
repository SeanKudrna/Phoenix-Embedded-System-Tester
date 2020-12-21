#ifndef BK2831E_H
#define BK2831E_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QList>
#include "bk.h"

#include "types.h"
class BK2831E : public BK
{

    Q_OBJECT
public:

    /*explicit */ BK2831E(BK *parent = nullptr,const char *port =SERIAL_PORT,int baud = BK_BAUD,char terminationChar = LINE_FEED, QString idString = meterID);
    ~BK2831E(); //destructor
    void trigger(void); /* send the trigger caommand */
    void setVDC(void); /* set meter to VDC */
    void setVAC(void); /* set meter to VAC */
    void setOHMS(void); /* set meter to OHMS */
    void setReference(bool enable); /* enable/disable reference reading */
 
    void measure(void); /* make a reading */
   private:



signals:

public slots:


};

#endif // BK2831E_H
