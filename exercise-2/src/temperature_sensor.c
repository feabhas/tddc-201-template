#include "temperature_sensor.h"
#include "ds18b20.h"
#include "lcd.h"

temperture_status_t temperture_sensor_initialize(void)
{
    // a.  Initialize LCD  (if okay we could use for error codes)
    // b.  Initialize the DS18B20 to be configurable for 9, 10, 11 or 12-bit resolution
    // c.  Read DS18B20 ROM
    // c.  Check ROM CRC value
    // d.  On the LCD display print out ROM's Family Code
    // e.  On a LCD display print out the Serial number
    // return OK
    return !TEMP_OK;
}


temperture_status_t temperture_sensor_run(void)
{
    // a.  Instruct the DS18B20 to do a conversion 
    // b.  Read the Scratchpad
    // c.  Check Scratchpad data CRC
    // d.  Convert 16-bit raw temperature to floating point degree C
    // e.  Convert float to C-string format <nn.nnC>
    // f.  Call LCD display to print C-string value
    return !TEMP_OK;
}