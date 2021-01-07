#include "can.h"
#include <string>
#include <fcntl.h>

#define MAX_CAN_BYTES (8)
// W A R N I N G do not change order of this list.
uint8_t canMsg[][MAX_CAN_BYTES]={
    {0x49,0x2b,0x14,0x06,0x00,0x00,0x00,0x00},// disable UUT broadcasts of ff00 - ff06
    {0x49,0x43,0x02,0x00,0x00,0x00,0x00,0x00},// request firmware version
    {0x47,0xf8,0x00,0x00,0x00,0x00,0x00,0x00},// reset controller 1
    {0x47,0xfb,0x00,0x00,0x00,0x00,0x00,0x00},// reset controller 2
    {0x49,0x43,0x06,0x00,0x00,0x00,0x00,0x00},// read CAN rate
    {0x49,0x2b,0x06,0x00,0x03,0x00,0x00,0x00},// write CAN write rate 1M
    {0x49,0x2b,0x06,0x00,0x02,0x00,0x00,0x00},// write CAN rate 500k
    {0x49,0x2b,0x06,0x00,0x01,0x00,0x00,0x00},// write CAN write rate 250k
    {0x49,0x2b,0x06,0x00,0x00,0x00,0x00,0x00},// write CAN write rate 125k
    {0x45,0x00,0x00,0x10,0x00,0x00,0x00,0x00},// read from 0x10
    {0x49,0x2b,0x14,0x00,0x00,0x00,0x00,0x00},// disable status messages
    {0x49,0x2b,0x14,0x00,0xff,0x00,0x00,0x00},// enable status messages
    {0x49,0x43,0x14,0x00,0x00,0x00,0x00,0x00},//  read reg 0x14
};





Can::~Can(){

}

/* CAN constructor will open socket */
 Can::Can(canid_t can_id, canid_t can_mask){
    rfilter[0].can_id   = can_id;
    rfilter[0].can_mask = can_mask;
    helper();
 }
Can::Can(){
    rfilter[0].can_id   = 0x0;
    rfilter[0].can_mask = 0x000;
    helper();
 }

int  Can::helper(void)
{
    char ifrName[50] = "can0";// interface name for CAN
    error=0;

    /* open socket */ if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) { // row socket protocol
            error += 0x02;
    }

    if(error) return error ;

    fcntl(s,F_SETFL,O_NONBLOCK); /* change socket to non-blocking */

    addr.can_family = AF_CAN;

    strcpy(ifr.ifr_name, ifrName); // put the name into the structured variable

    /* retrieve the interface index of the interface into ifr_ifindex. */
    if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) {
        error +=0x04;
    }

    if(error) return error ;

    addr.can_ifindex = ifr.ifr_ifindex;

    setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

    /* Bind function assigns a local protocol address to a socket. * */
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        error +=0x08;
    }

    return error;
}

void Can::clearRxBuffer(void){
    frameQueue.clear();
}

int Can::getNextFrame(can_frame *p){
    int status =1;
    can_frame f;
    if(frameQueue.size()){
        f =frameQueue.front();
        frameQueue.pop_front();
        memcpy(p,&f,sizeof(can_frame));
    }
    else{
        status = 0;
    }
    return status;
}


void Can::toString(can_frame *p,QString *pReply){
        pReply->append(QString::number(p->data[0],16));pReply->append(":");
        pReply->append(QString::number(p->data[6],16));pReply->append(":");
        pReply->append(QString::number(p->data[1],16));pReply->append(":");
        pReply->append(QString::number(p->data[2],16));pReply->append(":");
        pReply->append(QString::number(p->data[3],16));pReply->append(":");
        pReply->append(QString::number(p->data[4],16));pReply->append(":");
        pReply->append(QString::number(p->data[5],16));pReply->append(":");
        pReply->append(QString::number(p->data[6],16));pReply->append(":");
        pReply->append(QString::number(p->data[7],16));
}
void Can::setRxFilter(canid_t can_id, canid_t can_mask){

    rfilter[0].can_id = can_id;
    rfilter[0].can_mask = can_mask;
}
 //fixme going to have to set a reception thread
int Can::_read(void){
    can_frame frame;

    if(s){
        memset(&frame,0,sizeof(can_frame));
        frame.can_dlc =8; //maximum size

        int nbytes = read(s,&frame,sizeof(struct can_frame));

        if(nbytes<0){
            return 1;
        }
        else if(static_cast <unsigned int>(nbytes) < sizeof(struct can_frame)){
            return 2;
        }
        else{
            frameQueue.push_back(frame);
        }
    }
    else {
        return 3;
    }

    return 0;
}
int Can::_writeMsg(CanMsg_e index,canid_t can_id){
    int status = -1;
    can_frame frame;

    frame.can_id= can_id;
    frame.can_dlc = 8;

    if(index < C_MAX_MSG){
        memcpy(frame.data,canMsg[index],8);
        //pce->pCan->_write(&frame);
        status = _write(&frame);
    }
    return status;
}

/* convert a ascii string to a CAN frame and send it */
int Can::_write(char *canFrame){
    int nbytes;
    can_frame  frame;

    frame.can_dlc =8;


    if (parse_canframe(canFrame, &frame)){
        error += 0x01;
    }

    if(!error) {
    /* send frame */
    frame.can_id |= CAN_EFF_FLAG; // set to extended frame
    if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
        error +=0x10;
    }
    }
    return error;
}

/* send the CAN frame */
int Can::_write(can_frame *frame){
    int nbytes;

    frame->can_id |= CAN_EFF_FLAG; // set to extended frame

    /* send frame */
    if ((nbytes = write(s, frame, sizeof(can_frame))) != sizeof(can_frame)) {
        error +=0x10;
    }
    return error;
}


/* close the CAN connection */
void Can::_close(void){

    if(s){
    close(s);
    }
}
