#ifndef MYWORKER2_H
#define MYWORKER2_H

#include <QObject>
#include <QDebug>

#include <QtSerialPort/QSerialPort>
#include <QList>
#include <string>
#include <QString>
#include <QTimer>

class GSerial : public QObject
{
#define MAX_BUFFER (64)
#define MAX_LIST (32)
#define MAX_PORT_NAME (32)
    Q_OBJECT
public:
    explicit GSerial(QObject *parent = nullptr );
    bool open(const char *portName,int baudrate,char terminationChar);
    void getPortName(char *p);
    int  getBaudrate(void);
    void sendMessage(char *pMessage);
    void sendMessage(const char *pMessage);
    void setTerminationChar(char terminationChar);
    int getTick();// return the tick value
    ~GSerial();

signals:
    void doneProcessSignal();     // signal
    void readyReadSignal(QString res); // signal

public slots:
    void readyReadSlot();// slot
    void timerTimeOut();

private:
    QSerialPort *pPort;
    QList <QString> messageList;
    char portName[MAX_PORT_NAME];
    int  baudRate;
    char message[MAX_BUFFER];
    int  messageIndex;
    char terminationChar;
    QTimer *ptimer;
    int tick;
};

#endif // MYWORKER_H
