#include "unity.h"
#include "temperature_sensor.h"


// include dependent modules for compilation/linking
#include "mock_ds18b20.h"
#include "mock_lcd.h"

#include <string.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_temperature_sensor_initialization_code(void)
{
    // TEST_IGNORE();
    lcd_initialize_ExpectAndReturn(true);
    ds18b20_initialise_ExpectAndReturn(R12, true);

    ds18b20_ROM_t data = { 
        .rom_code.family_code = 0x28, 
        .rom_code.serial_number = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 } ,
        .rom_code.crc = 0x00, 
    };

    ds18b20_read_rom_ExpectAndReturn(data);

    ds18b20_calculate_CRC_ExpectAndReturn((void*)&data, sizeof(data)-1, data.rom_code.crc);

    const char* fc_str = "Family code: 0x28";
    lcd_display_ExpectAndReturn(fc_str, strlen(fc_str)-1);
    const char* sn_str = "Serial Number: 06:05:04:03:02:01";
    lcd_display_ExpectAndReturn(sn_str, strlen(sn_str)-1);

    // Call UUT
    temperture_status_t rvalue = temperture_sensor_initialize();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_OK);
}



void test_temperature_sensor_main_code(void)
{
    // TEST_IGNORE();
    test_temperature_sensor_initialization_code();

    ds18b20_do_conversion_Expect();

    // bool ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data);
    ds18b20_scratchpad_data_t scratchpad = {
        .lsb = 0x50,
        .msb = 0x05,
        .crc = 0
    };
    ds18b20_read_scratchpad_ExpectAndReturn(0, true);
    ds18b20_read_scratchpad_IgnoreArg_data();
    ds18b20_read_scratchpad_ReturnThruPtr_data(&scratchpad);

    ds18b20_calculate_CRC_ExpectAndReturn((void*)&scratchpad, sizeof(scratchpad)-1, scratchpad.crc);

    ds18b20_convert_ExpectAndReturn(0x0550U, 85.0f);

    lcd_display_ExpectAndReturn("85.00C", 6);

    // run UUT
    temperture_status_t rvalue = temperture_sensor_run();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_OK);
}


///// INITIALIZATION FAILURE TESTS /////
void test_temperature_sensor_initialization_ds18b20_failure(void)
{
    // TEST_IGNORE();

    lcd_initialize_ExpectAndReturn(true);
    ds18b20_initialise_ExpectAndReturn(R12, false);

    // Call UUT
    temperture_status_t rvalue = temperture_sensor_initialize();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_DS18B20_FALURE);

}

void test_temperature_sensor_initialization_lcd_failure(void)
{
    // TEST_IGNORE();

    lcd_initialize_ExpectAndReturn(false);
    // ds18b20_initialise_ExpectAndReturn(R12, true);

    // Call UUT
    temperture_status_t rvalue = temperture_sensor_initialize();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_LCD_FALIURE);
}

void test_temperature_sensor_initialization_crc_fail(void)
{
    // TEST_IGNORE();

    lcd_initialize_ExpectAndReturn(true);
    ds18b20_initialise_ExpectAndReturn(R12, true);

    ds18b20_ROM_t data = { 
        .rom_code.family_code = 0x28, 
        .rom_code.serial_number = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 } ,
        .rom_code.crc = 0x00, 
    };

    ds18b20_read_rom_ExpectAndReturn(data);

    ds18b20_calculate_CRC_ExpectAndReturn((void*)&data, sizeof(data)-1, 0xFF);

    // Call UUT
    temperture_status_t rvalue = temperture_sensor_initialize();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_DS18B20_FALURE);
}

void test_temperature_sensor_initialization_lcd_write_fail_family(void)
{
    // TEST_IGNORE();

    lcd_initialize_ExpectAndReturn(true);
    ds18b20_initialise_ExpectAndReturn(R12, true);

    ds18b20_ROM_t data = { 
        .rom_code.family_code = 0x28, 
        .rom_code.serial_number = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 } ,
        .rom_code.crc = 0x00, 
    };

    ds18b20_read_rom_ExpectAndReturn(data);

    ds18b20_calculate_CRC_ExpectAndReturn((void*)&data, sizeof(data)-1, data.rom_code.crc);

    const char* fc_str = "Family code: 0x28";
    lcd_display_ExpectAndReturn(fc_str, -1);

    // Call UUT
    temperture_status_t rvalue = temperture_sensor_initialize();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_LCD_FALIURE);
}

void test_temperature_sensor_initialization_lcd_write_fail_sn(void)
{
    // TEST_IGNORE();

    lcd_initialize_ExpectAndReturn(true);
    ds18b20_initialise_ExpectAndReturn(R12, true);

    ds18b20_ROM_t data = { 
        .rom_code.family_code = 0x28, 
        .rom_code.serial_number = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 } ,
        .rom_code.crc = 0x00, 
    };

    ds18b20_read_rom_ExpectAndReturn(data);

    ds18b20_calculate_CRC_ExpectAndReturn((void*)&data, sizeof(data)-1, data.rom_code.crc);

    const char* fc_str = "Family code: 0x28";
    lcd_display_ExpectAndReturn(fc_str, strlen(fc_str)-1);
    const char* sn_str = "Serial Number: 06:05:04:03:02:01";
    lcd_display_ExpectAndReturn(sn_str, -1);

    // Call UUT
    temperture_status_t rvalue = temperture_sensor_initialize();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_LCD_FALIURE);
}

///// MAIN FAILURE TESTS /////
void test_temperature_sensor_main_code_read_scratchpad_error(void)
{
    // TEST_IGNORE();

    ds18b20_do_conversion_Expect();

    // bool ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data);
    ds18b20_scratchpad_data_t scratchpad = {
        .lsb = 0x50,
        .msb = 0x05,
        .crc = 0
    };
    ds18b20_read_scratchpad_ExpectAndReturn(0, false);
    ds18b20_read_scratchpad_IgnoreArg_data();

    // run UUT
    temperture_status_t rvalue = temperture_sensor_run();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_DS18B20_FALURE);
}

void test_temperature_sensor_main_code_crc_error(void)
{
    // TEST_IGNORE();

    ds18b20_do_conversion_Expect();

    // bool ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data);
    ds18b20_scratchpad_data_t scratchpad = {
        .lsb = 0x50,
        .msb = 0x05,
        .crc = 0
    };
    ds18b20_read_scratchpad_ExpectAndReturn(0, true);
    ds18b20_read_scratchpad_IgnoreArg_data();
    ds18b20_read_scratchpad_ReturnThruPtr_data(&scratchpad);

    ds18b20_calculate_CRC_ExpectAndReturn((void*)&scratchpad, sizeof(scratchpad)-1, 0xFF);

    // run UUT
    temperture_status_t rvalue = temperture_sensor_run();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_DS18B20_FALURE);
}

void test_temperature_sensor_main_code_converts_fail_neg(void)
{
    // TEST_IGNORE();

    ds18b20_do_conversion_Expect();

    // bool ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data);
    ds18b20_scratchpad_data_t scratchpad = {
        .lsb = 0x50,
        .msb = 0x05,
        .crc = 0
    };
    ds18b20_read_scratchpad_ExpectAndReturn(0, true);
    ds18b20_read_scratchpad_IgnoreArg_data();
    ds18b20_read_scratchpad_ReturnThruPtr_data(&scratchpad);

    ds18b20_calculate_CRC_ExpectAndReturn((void*)&scratchpad, sizeof(scratchpad)-1, scratchpad.crc);

    ds18b20_convert_ExpectAndReturn(0x0550U, -100.0f);

    // run UUT
    temperture_status_t rvalue = temperture_sensor_run();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_DS18B20_FALURE);
}

void test_temperature_sensor_main_code_converts_fail_positive(void)
{
    // TEST_IGNORE();

    ds18b20_do_conversion_Expect();

    // bool ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data);
    ds18b20_scratchpad_data_t scratchpad = {
        .lsb = 0x50,
        .msb = 0x05,
        .crc = 0
    };
    ds18b20_read_scratchpad_ExpectAndReturn(0, true);
    ds18b20_read_scratchpad_IgnoreArg_data();
    ds18b20_read_scratchpad_ReturnThruPtr_data(&scratchpad);

    ds18b20_calculate_CRC_ExpectAndReturn((void*)&scratchpad, sizeof(scratchpad)-1, scratchpad.crc);

    ds18b20_convert_ExpectAndReturn(0x0550U, 126.0f);

    // run UUT
    temperture_status_t rvalue = temperture_sensor_run();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_DS18B20_FALURE);
}

void test_temperature_sensor_main_code_lcd_write_fail(void)
{
    // TEST_IGNORE();

    ds18b20_do_conversion_Expect();

    // bool ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data);
    ds18b20_scratchpad_data_t scratchpad = {
        .lsb = 0x50,
        .msb = 0x05,
        .crc = 0
    };
    ds18b20_read_scratchpad_ExpectAndReturn(0, true);
    ds18b20_read_scratchpad_IgnoreArg_data();
    ds18b20_read_scratchpad_ReturnThruPtr_data(&scratchpad);

    ds18b20_calculate_CRC_ExpectAndReturn((void*)&scratchpad, sizeof(scratchpad)-1, scratchpad.crc);

    ds18b20_convert_ExpectAndReturn(0x0550U, 85.0f);

    lcd_display_ExpectAndReturn("85.00C", -1);

    // run UUT
    temperture_status_t rvalue = temperture_sensor_run();
    TEST_ASSERT_EQUAL_INT(rvalue, TEMP_LCD_FALIURE);
}
