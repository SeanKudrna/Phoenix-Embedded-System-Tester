#ifndef SERIALRXTHREAD_H
#define SERIALRXTHREAD_H
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QMutex>
#include <QList>
#include <QString>


class SerialRxThread: public QThread
{
public:
    SerialRxThread();
    void init(QSerialPort *pPort,QList<QString> *pList);
    void run();
    void stop();
private:
    QSerialPort *pPort;
    bool _stop;
    QList <QString> *pList;
    QByteArray byteArray;

};

#endif // SERIALRXTHREAD_H
