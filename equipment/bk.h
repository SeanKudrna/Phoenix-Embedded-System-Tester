#ifndef BK_H
#define BK_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "SerialDevice.h"
#include <QList>
#include "types.h"



class BK : public QObject
{
    Q_OBJECT
public:

    explicit BK(QObject *parent = nullptr,const char *port =SERIAL_PORT,int baud = BK_BAUD,char terminationChar = LINE_FEED);

    ~BK(); //destructor
    bool toVoltage(char *string,double *volt); /* convert the string to double voltage */
    int getBaud(void);
    char getTerminationChar(void);
    void getPort(char *pPort);

    void getId(void); /* request the identification of the meter */
    void reset(void); /* reset the BK instrument */

    void appendValue(QString *pString,double value);
    void appendValue(QString *pString,int value);

    bool getNextData(double *data); /* take from the data list */
    bool getNextData(QString *data);
    bool getNextData(int *data);

    void clearDataList(void); /* clear the data list  of measurements */
    SerialDevice *pSerialDevice;

private:
    char terminationChar;
    int baud;
    char port[32];
    int counter;



signals:

public slots:

};

#endif // BK9200_H
