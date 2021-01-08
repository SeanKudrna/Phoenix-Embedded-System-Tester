#include "relay.h"

/* The i2c port will be shared
 * the address of the io expander must be used
 * each relay must have an id that is public
 * the relay class will extend mcp2317 class.
 *
 * The mcp2317 class will perform the init of the device
 * using
 * */
Relay::~Relay(){
}

void Relay::init(){
}
