#ifndef CAN_H
#define CAN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>
//#include <j1939.h>
#include <QQueue>
#include <QString>
//fixme remove this and replace with non QT types

// W A R N I N G do not change order of this list.
typedef enum{
    C_DISABLE_BROADCAST,
    C_REQUEST_VERSION,
    C_RESET1,
    C_RESET2,
    C_READ_CAN_RATE,
    C_SET_CAN_1M,
    C_SET_CAN_500K,
    C_SET_CAN_250K,
    C_SET_CAN_125k,
    C_READ_0x10,
    C_DISABLE_STATUS,
    C_ENABLE_STATUS,
    C_READ_REG_0X14,
    C_MAX_MSG
}CanMsg_e;

extern "C"{
#include "lib.h"
}


class Can
{
public:
    Can();
    Can(canid_t can_id, canid_t can_mask);
    ~Can();

    // functions
    void clearRxBuffer(void);
    void setRxFilter(void);
    int getNextFrame(can_frame *p);
    void _close(void);
    int _write(char *canFrame);
    int _write(can_frame *frame);
    int _read(void);
    void setRxFilter(canid_t can_id, canid_t can_mask);
    void toString(can_frame *p,QString *pReply);
    int _writeMsg(CanMsg_e index,canid_t can_id);


    //variables
    int error;

private:
    //functions
    int helper(void);

    //variables
    struct can_filter rfilter[1]; // fixme this could be an array
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;
    int s; /* can raw socket */
    QQueue <can_frame> frameQueue;

};
 #endif // CAN_H
