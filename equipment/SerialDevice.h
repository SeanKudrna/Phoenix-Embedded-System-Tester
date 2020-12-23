#ifndef SERIAL_DEVICE_H
#define SERIAL_DEVICE_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "GSerial.h"
#include <QList>
#include "types.h"



class SerialDevice : public QObject
{
    Q_OBJECT
public:

    explicit SerialDevice(QObject *parent = nullptr,const char *port =SERIAL_PORT,int baud = BK_BAUD,char terminationChar = LINE_FEED);

    ~SerialDevice(); //destructor

    bool getNextData(QString *data); /* take from the data list */
    void clearDataList(void); /* clear the data list  of measurements */
    void sendMessage(char *pMessage);/* send serial message */
    void sendMessage(const char *pMessage);/* send serial message */
    void sendMessage(QString *pMessage);/* send serial message */
    void removeLast(); /* remove last entry from dataList */
    bool getMessageFlag(void); /* return the message flag */
    QThread *serialThread;
    GSerial *serialObject;

private:

    bool messageFlag;
    QList <QString>dataList;
    QString command; // this is the command that should be stripped from the reply.


signals:

public slots:
     void handleReadyReadSlot(QString res);

};

#endif // BK2831E_H
