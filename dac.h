#ifndef DAC_H
#define DAC_H
#include "Pi2c-master/pi2c.h"


#define MCP4728_I2CADDR_DEFAULT   0x60 ///< MCP4728 default i2c address
#define MCP4728_MULTI_IR_CMD      0x40 ///< Command to write to the input register only
#define MCP4728_MULTI_EEPROM_CMD  0x50 ///< Command to write to the input register and EEPROM
#define MCP4728_FAST_WRITE_CMD    0xC0 ///< Command to write all channels at once with

/**
 * @brief Power status values
 *
 * Allowed values for `setPowerMode`.
 */

typedef enum pd_mode {
  MCP4728_PD_MODE_NORMAL, ///< Normal; the channel outputs the given value as
                          ///< normal.
  MCP4728_PD_MODE_GND_1K, ///< VOUT is loaded with 1 kΩ resistor to ground. Most
                          ///< of the channel circuits are powered off.
  MCP4728_PD_MODE_GND_100K, ///< VOUT is loaded with 100 kΩ resistor to ground.
                            ///< Most of the channel circuits are powered off.
  MCP4728_PD_MODE_GND_500K, ///< VOUT is loaded with 500 kΩ resistor to ground.
                            ///< Most of the channel circuits are powered off.
} MCP4728_pd_mode_t;

/**
 * @brief Example enum values
 *
 * Allowed values for `setGain`.
 */
typedef enum gain {
  MCP4728_GAIN_1X,
  MCP4728_GAIN_2X,
} MCP4728_gain_t;

/**
 * @brief Ex
 *
 * Allowed values for `setVref`.
 */
typedef enum vref {
  MCP4728_VREF_VDD,
  MCP4728_VREF_INTERNAL,
} MCP4728_vref_t;

/**
 * @brief Example enum values
 *
 * Allowed values for `setChannelGain`.
 */
typedef enum channel {
  MCP4728_CHANNEL_A,
  MCP4728_CHANNEL_B,
  MCP4728_CHANNEL_C,
  MCP4728_CHANNEL_D,
} MCP4728_channel_t;

class Dac
{
public:
    /*!
 *    @brief  Instantiates a new MCP4728 class
 */

    Dac(Pi2c *pi2c,uint8_t address):pi2c(pi2c),address(address){init();} /* initialize the chip, must know the address */
    Dac(uint8_t address):address(address){init();} /* initialize the chip, must know the address */


    void init(void);
    //Dac(void);
    //Dac(uint8_t i2c_address);
    //~Dac(void);

    uint16_t volts2Steps(double volts);

    /*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2c_address
 *            The I2C address to be used.
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @return True if initialization was successful, otherwise false.
 */
    //bool begin(uint8_t address);
    //bool begin(uint8_t i2c_address, TwoWire *wire);

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
    bool setChannelValue(
            MCP4728_channel_t channel, uint16_t new_value, MCP4728_vref_t new_vref,
            MCP4728_gain_t new_gain, MCP4728_pd_mode_t new_pd_mode, bool udac) ;
    bool setChannelValue(
            MCP4728_channel_t channel, double value, MCP4728_vref_t new_vref,
            MCP4728_gain_t new_gain, MCP4728_pd_mode_t new_pd_mode, bool udac) ;

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
    bool fastWrite(uint16_t channel_a_value,
                        uint16_t channel_b_value,
                        uint16_t channel_c_value,
                        uint16_t channel_d_value) ;


    /**
 * @brief Saves the DAC's input register settings to the internal EEPROM,
 * makeing them the default values when the ADC is powered on
 *
 * @return true if the write was successful
 * @return false if there was an error with I2C communication between the MCU
 * and the DAC */


    bool saveToEEPROM(void) ;
private:
    Pi2c *pi2c;
    uint8_t address;

};
#endif // DAC_H
