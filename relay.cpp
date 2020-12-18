#include "relay.h"

/* the i2c port will be shared
 * the address of the io expander must be used
 * each relay must nave an id that is public
 * the relay class will extend the mcp2317 class.
 *
 * the mcp2317 class will perform the init of the device
 * using
 * */
Relay::~Relay(){
}

void Relay::init(){
}
