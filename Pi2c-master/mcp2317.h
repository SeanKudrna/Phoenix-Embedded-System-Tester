#ifndef MCP2317_H
#define MCP2317_H
#include "../Pi2c-master/pi2c.h"

class Mcp2317
{
public:
    ~Mcp2317();
    Mcp2317(Pi2c *pi2c,uint8_t address);//:pi2c(pi2c); /* initialize the chip, must know the address */

    Mcp2317(uint8_t address);//:pi2c(pi2c),address(address); /* initialize the chip, must know the address */

    int write(bool sideA,uint8_t data);
    uint8_t getAddress(){return address;}
    void setAddress(uint8_t address){this->address = address;}
    void init(void);
    uint8_t read(bool sideA);

private:
    Pi2c *pi2c;
    uint8_t address;
    char buffer[2];
    uint8_t ioState[2];
};

#endif // MCP2317_H
