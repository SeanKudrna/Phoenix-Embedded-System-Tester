#ifndef SERIAL_DEVICE_H
#define SERIAL_DEVICE_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "G2Serial.h"
#include <QList>
#include "./PC/types.h"

class Serial2Device : public QObject
{
    Q_OBJECT
public:
#ifdef Q_OS_LINUX
    explicit Serial2Device(QObject *parent = nullptr,char *port ="/dev/ttyUSB0",int baud = 9600,char terminationChar = 0x0a);
#else
    explicit Serial2Device(QObject *parent = nullptr,char *port ="COM26",int baud = 9600,char terminationChar = 0x0a);
#endif
    ~Serial2Device(); //destructor

    bool getNextData(QString *data); /* take from the data list */
    void clearDataList(void); /* clear the data list  of measurements */
    void sendMessage(char *pMessage);/* send serial message */
    void sendMessage(QString *pMessage);/* send serial message */
    bool getMessageFlag(void); /* return the message flag */
    //QThread *serialThread;
    G2Serial *serialObject;

private:

    bool messageFlag;
    QList <QString>dataList;
    QString command; // this is the command that should be stripped from the reply.


signals:

public slots:
     void handleReadyReadSlot(QString res);

};

#endif // BK2831E_H
