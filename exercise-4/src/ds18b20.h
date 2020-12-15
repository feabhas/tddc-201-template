/** @file ds18b20.h 
    \brief API for the DS18B20 Temperature Sensor.
    \version 2.0
*/
#ifndef _DS18B20_H
#define _DS18B20_H

#include <stdbool.h>
#include <stdint.h>

/**  
 *  Defines the DS18B20 Temperature Sensor Resolution 
 */
typedef enum { 
    R9  = ~1U, //!<  9-bit Resolution
    R10 = ~3U, //!< 10-bit Resolution
    R11 = ~7U, //!< 11-bit Resolution
    R12 = ~0U  //!< 12-bit Resolution
} Resolution;

/*! \struct ds18b20_scratchpad_data_t
    \brief Structure for storing the returned DS18B20 scratchpad data.
*/
typedef struct
{
    uint8_t lsb;            //!< least-significant byte of temperature 
    uint8_t msb;            //!< most-significant byte of temperature 
    uint8_t Th;             //!< High alarm trigger value
    uint8_t Tl;             //!< Low alarm trigger value
    uint8_t config_reg;     //!< Configuration register
    uint8_t reserved[3];    //!< reserved
    uint8_t crc;            //!< Cyclic Redundancy Check
} ds18b20_scratchpad_data_t;

/*! \fn bool ds18b20_initialise(Resolution resolution)
    \brief Initialised the DS18B20 Temperature Sensor.
    \param resolution ```[IN]``` The required resolution.
    \return ```true``` if initialisation was successful.
*/
bool ds18b20_initialise(Resolution resolution);

/*! \union ds18b20_ROM_t
    \brief Union for storing the ROM values

    The 64-bytes of data can either byte access or strct access.
*/
typedef union
{
    uint8_t bytes[8];               //!< raw byte access of 64-bits of data
    struct {
        uint8_t family_code;        //!< Family code (```0x28```)
        uint8_t serial_number[6];   //!< Serial number (```00:00:00:00:00:00```)
        uint8_t crc;                //!< Cyclic Redundancy Check
    }rom_code;
} ds18b20_ROM_t;


/*! \fn ds18b20_ROM_t ds18b20_read_rom(void)
    \brief Read ROM
    \return 64-bits of data as type ```ds18b20_ROM_t```
*/
ds18b20_ROM_t ds18b20_read_rom(void);

/*! \fn void ds18b20_do_conversion(void)
    \brief Initiate Temperature Conversion - blocks until conversion complete
*/ 
void ds18b20_do_conversion(void);


/*! \fn bool ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data)
    \brief Reads the DS18B20 Scratchpad data
    \param data ```[OUT]``` the current contents pf the device scartchpad
    \return ```true``` if read successful
*/ 
bool ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data);

/*! \fn float ds18b20_convert(uint16_t digital)
    \brief Converts the signed 12.4 fixed point representation to degC.
    \param digital ```[IN]``` The 16-bit raw temperature reading in signed 12.4
    \return The temperature converted to degrees Centigrade.
*/
float ds18b20_convert(uint16_t digital);

/*! \fn uint8_t ds18b20_calculate_CRC(const uint8_t* data, uint32_t num_of_bytes)
    \brief Compute CRC using CRC = X^{8} + X^{5} + X^{4} + 1
    \param data ```[IN]``` takes N-bytes of data 
    \param num_of_bytes ```[IN]``` the number of bytes for the CRC to use in calculation
    \return CRC value
*/
uint8_t ds18b20_calculate_CRC(const uint8_t* data, uint32_t num_of_bytes);

#endif // _DS18B20_H
