#ifndef RELAY_H
#define RELAY_H

#include "Pi2c-master/pi2c.h"
#include "Pi2c-master/mcp2317.h"

class Relay : public Mcp2317
{
public:
    Relay(Pi2c *pi2c,uint8_t address):Mcp2317(pi2c,address){init();}
    Relay(uint8_t address):Mcp2317(address){init();}
    ~Relay();
private:
    void init();
};

#endif // RELAY_H

/* the i2c port will be shared
 * the port must be opened and closed on each command
 * the address of the io expander must be used
 * each relay must nave an id that is public
 * the relay class will extend the mcp2317 class.
 *
 * the mcp2317 class will perform the init of the device
 * using
 * */
