#include "dac.h"
#include "Pi2c-master/pi2c.h"


/*!
 *    @brief  Applies formula to conver desired voltage to required setting.
 *    @param  volts - the desired voltage
 *    @return  uint16_t setting value
 */
uint16_t Dac::volts2Steps(double volts){
#define SLOPE  781.46
#define OFFSET  15.21

volts *=SLOPE+OFFSET;

return(uint16_t(volts));

#undef SLOPE
#undef OFFSET
}

void Dac::init(){
  pi2c = new Pi2c(address,false);
}

#if(0)
bool Dac::begin(uint8_t i2c_address) {
  i2c_dev = new Pi2c(i2c_address);
  return true;
}
#endif

//Set channel value settings
bool Dac::setChannelValue(
    MCP4728_channel_t channel, double value, MCP4728_vref_t new_vref,
    MCP4728_gain_t new_gain, MCP4728_pd_mode_t new_pd_mode, bool udac) {

    uint16_t new_value;
    new_value = this->volts2Steps(value);

   setChannelValue(channel, new_value, new_vref, new_gain, new_pd_mode, udac) ;
   return true;// fixme
}

/**
 * @brief Sets the input register for a given channel to the specified settings
 *
 * @param channel The channel to update
 * @param new_value The new value to assign
 * @param new_vref Optional vref setting - Defaults to `MCP4728_VREF_VDD`
 * @param new_gain Optional gain setting - Defaults to `MCP4728_GAIN_1X`
 * @param new_pd_mode Optional power down mode setting - Defaults to
 * `MCP4728_PD_MOOE_NORMAL`
 * @param udac Optional UDAC setting - Defaults to `false`, latching
 * immediately. Set to `true` to latch when the LDAC pin is pulled low
 *
 * @return true if the write was successful
 * @return false if there was an error with I2C communication between the MCU
 * and the DAC
 */
bool Dac::setChannelValue(
    MCP4728_channel_t channel, uint16_t new_value, MCP4728_vref_t new_vref,
    MCP4728_gain_t new_gain, MCP4728_pd_mode_t new_pd_mode, bool udac) {

  uint8_t output_buffer[3];

  // build the setter header/ "address"
  // 0 1 0 0 0 DAC1 DAC0 UDAC[A]
  uint8_t sequential_write_cmd = MCP4728_MULTI_IR_CMD;
  sequential_write_cmd |= (channel << 1);
  sequential_write_cmd |= udac;

  output_buffer[0] = sequential_write_cmd;
  // VREF PD1 PD0 Gx D11 D10 D9 D8 [A] D7 D6 D5 D4 D3 D2 D1 D0 [A]
  new_value |= (new_vref << 15);
  new_value |= (new_pd_mode << 13);
  new_value |= (new_gain << 12);

  output_buffer[1] = new_value >> 8;
  output_buffer[2] = new_value & 0xFF;

  if (!pi2c->i2cWrite((char *)output_buffer, 3)) {
    return false;
  }
  return true;
}
/**
 * @brief Set the values of all four channels simultaneously with minimal delay
 * or configuration
 *
 * @param channel_a_value The value to assign to channel A
 * @param channel_b_value The value to assign to channel B
 * @param channel_c_value The value to assign to channel C
 * @param channel_d_value The value to assign to channel D
 * @return true if the write was successful
 * @return false if there was an error with I2C communication between the MCU
 * and the DAC
 */
bool Dac::fastWrite(uint16_t channel_a_value,
uint16_t channel_b_value,uint16_t channel_c_value,
uint16_t channel_d_value) {

    uint8_t output_buffer[8];

    output_buffer[0] = channel_a_value >> 8;
    output_buffer[1] = channel_a_value & 0xFF;

    output_buffer[2] = channel_b_value >> 8;
    output_buffer[3] = channel_b_value & 0xFF;

    output_buffer[4] = channel_c_value >> 8;
    output_buffer[5] = channel_c_value & 0xFF;

    output_buffer[6] = channel_d_value >> 8;
    output_buffer[7] = channel_d_value & 0xFF;

    if (!pi2c->i2cWrite((char *)output_buffer, 8)) {
       return false;
    }

    return true;
}

/**
 * @brief Saves the DAC's input register settings to the internal EEPROM,
 * makeing them the default values when the ADC is powered on
 *
 * @return true if the write was successful
 * @return false if there was an error with I2C communication between the MCU
 * and the DAC */

bool Dac::saveToEEPROM(void) {
      uint8_t input_buffer[24];
      uint8_t output_buffer[9];

      pi2c->i2cRead((char *)input_buffer, 24);

      // build header byte 0 1 0 1 0 DAC1 DAC0 UDAC [A]
      uint8_t eeprom_write_cmd = MCP4728_MULTI_EEPROM_CMD; // 0 1 0 1 0 xxx
      eeprom_write_cmd |=
          (MCP4728_CHANNEL_A << 1); // DAC1 DAC0, start at channel A obvs
      eeprom_write_cmd |= 0;        // UDAC ; yes, latch please
      // First byte is the write command+options
      output_buffer[0] = eeprom_write_cmd;

      // copy the incoming input register bytes to the outgoing buffer
      // Channel A
      output_buffer[1] = input_buffer[1];
      output_buffer[2] = input_buffer[2];
      // Channel B
      output_buffer[3] = input_buffer[7];
      output_buffer[4] = input_buffer[8];
      // Channel C
      output_buffer[5] = input_buffer[13];
      output_buffer[6] = input_buffer[14];
      // Channel D
      output_buffer[7] = input_buffer[19];
      output_buffer[8] = input_buffer[20];

      if (!pi2c->i2cWrite((char *)output_buffer, 9)) {
        return false;
      }
      //fixme delay(15);
      return true;
}
