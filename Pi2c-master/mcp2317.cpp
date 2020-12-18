#include "mcp2317.h"
/* addresing when control register IOCON>BANK=0, default */
typedef enum
{
    _IODIRA,/* data direction */
    _IODIRB,/* data direction */
    _IPOLA,
    _IPOLB,
    _GPINTENA,
    _GPINTENB,
    _DEFVALA,
    _DEFVALB,
    _INTCONA,
    _INTCONB,
    _IOCONA,
    _IOCONB,
    _GPPUA,
    _GPPUB,
    _INT_FA,
    _INT_FB,
    _INTCAPA,
    _INTCAPB,
    _GPIOA,
    _GPIOB,
    _OLATA,
    _OLATB
}ControlReg_t;

#define NOT_SEQUENTIAL 0x20

Mcp2317::Mcp2317(Pi2c *pi2c,uint8_t address):pi2c(pi2c),address(address){
     pi2c = new Pi2c(address,false);
     init();
 } /* initialize the chip, must know the address */


Mcp2317::Mcp2317(uint8_t address):pi2c(pi2c),address(address){
    pi2c = new Pi2c(address,false);
    init();
} /* initialize the chip, must know the address */


Mcp2317::~Mcp2317(){
    //delete this->pi2c;
}
void Mcp2317:: init() /* initialize the chip, must know the address */
{
    int status;

    //this->address = address;
    //this->pi2c = pi2c;

    // clear the relay states
    ioState[0] =0;
    ioState[1] =0;

    if(pi2c){
        // enable non seqential writes
        buffer[0] =_IOCONA;
        buffer[1] =NOT_SEQUENTIAL;
        status = pi2c->i2cWrite(buffer,2);

        buffer[0] =_IOCONB;
        buffer[1] =NOT_SEQUENTIAL;
        status = pi2c->i2cWrite(buffer,2);


        // set outputs to A
        buffer[0] =_IODIRA;
        buffer[1] =0x00;
        status = pi2c->i2cWrite(buffer,2);

        // set outputs to B
        buffer[0] =_IODIRB;
        buffer[1] =0x00;
        status = pi2c->i2cWrite(buffer,2);

/* Don't write becuase you will erase previous setting
        buffer[0] =_OLATA;
        buffer[1] =0x00;
        status = pi2c->i2cWrite(buffer,2);

        buffer[0] =_OLATB;
        buffer[1] =0x00;
        status = pi2c->i2cWrite(buffer,2);

        buffer[0] =_GPIOA;
        buffer[1] =0x00;
        status = pi2c->i2cWrite(buffer,2);

        // set outputs to B
        buffer[0] =_GPIOB;
        buffer[1] =0x00;
        status = pi2c->i2cWrite(buffer,2);
        */
    }
}
uint8_t Mcp2317:: read(bool sideA){
    if(sideA){
      return ioState[0];
    }
    else{

      return ioState[1];
    }
}

int Mcp2317:: write(bool sideA,uint8_t data){
        int status;

        if(sideA){
            buffer[0] =_GPIOA;
            ioState[0] = data;
        }
        else{
            buffer[0] =_GPIOB;
            ioState[1] = data;
        }
        buffer[1] =data;
        status = pi2c->i2cWrite(buffer,2);
        return status;
} /* initialize the chip, must know the address */
