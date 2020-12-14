#include "temperature_sensor.h"
#include "ds18b20.h"
#include "lcd.h"



#include <assert.h>
#include <stdio.h>
#include <string.h>

temperture_status_t temperture_sensor_initialize(void)
{
    // a. Initialize LCD  (if okay we could use if for error codes)
    bool okay = lcd_initialize();
    if(!okay){
        return TEMP_LCD_FALIURE;
    }

    // b.  Initialize the DS18B20 to be configurable for 9, 10, 11 or 12-bit resolution
    okay = ds18b20_initialise(R12);  
    if(!okay){
        return TEMP_DS18B20_FALURE;
    }

    // c.  Read DS18B20 ROM
    ds18b20_ROM_t rom_data = ds18b20_read_rom();

    // c.  Check ROM CRC value
    uint8_t crc = ds18b20_calculate_CRC((uint8_t*)&rom_data, 7);
    if(rom_data.rom_code.crc != crc){
        return TEMP_DS18B20_FALURE;
    }

    // d.  On the LCD display print out ROM's Family Code
    char buff[40] = { '\0' };
    sprintf(buff, "Family code: 0x%02X", rom_data.rom_code.family_code);

    int count = lcd_display(buff);  
    if(count == -1) {
        // LCD display error
        return TEMP_LCD_FALIURE;
    }


    // d.  On a LCD display print out the Serial number
    memset(buff, 0, sizeof(buff));
    int num = sprintf(buff, "Serial Number: ");
    for (uint32_t i = 6, offset = 0; i != 0; --i) {
        int xnum = sprintf((buff+(num+offset)), "%02X%s", \
                            rom_data.rom_code.serial_number[i-1], \
                            (i != 1)?":":"");
        offset += xnum;
    }

    count = lcd_display(buff);
    if(count == -1) {
        // LCD display error
        return TEMP_LCD_FALIURE;
    }

    return TEMP_OK;
}


temperture_status_t temperture_sensor_run(void)
{
    // a.  Instruct the DS18B20 to do a conversion 
    ds18b20_do_conversion();

    // b.  Read the Scratchpad
    ds18b20_scratchpad_data_t scratchpad;
    memset(&scratchpad, 0, sizeof(scratchpad));
    bool okay = ds18b20_read_scratchpad(&scratchpad);
    if(!okay){
        return TEMP_DS18B20_FALURE;
    }

    // c.  Check Scratchpad data CRC
    uint8_t crc = ds18b20_calculate_CRC((uint8_t*)&scratchpad, sizeof(scratchpad)-1);  
    if(scratchpad.crc != crc){
        return TEMP_DS18B20_FALURE;
    }

    // d.  Convert 16-bit raw temperature to floating point degree C
    uint16_t raw_sensor_temp = ((scratchpad.msb << 8) | scratchpad.lsb);
    float deg_C = ds18b20_convert(raw_sensor_temp);
    if((deg_C < -55.0f) || (deg_C > 125.0f)) {
        // Out of range error
        return TEMP_DS18B20_FALURE;
    }

    // e.  Convert float to C-string format <nn.nnC>
    char buff[20] = { '\0' };
    sprintf(buff, "%02.2fC", deg_C); 

    // f.  Call LCD display to print C-string value
    int count = lcd_display(buff);   
    if(count == -1) {
        return TEMP_LCD_FALIURE;
    }

    return TEMP_OK;
}