#include "build/temp/_test_temperature_sensor.c"
#include "mock_lcd.h"
#include "mock_ds18b20.h"
#include "temperature_sensor.h"
#include "unity.h"












void setUp(void)

{

}



void tearDown(void)

{

}



void test_temperature_sensor_initialization_code(void)

{



    lcd_initialize_CMockExpectAndReturn(22, 

   1

   );

    ds18b20_initialise_CMockExpectAndReturn(23, R12, 

   1

   );



    ds18b20_ROM_t data = {

        .rom_code.family_code = 0x28,

        .rom_code.serial_number = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 } ,

        .rom_code.crc = 0x00,

    };



    ds18b20_read_rom_CMockExpectAndReturn(31, data);



    ds18b20_calculate_CRC_CMockExpectAndReturn(33, (void*)&data, sizeof(data)-1, data.rom_code.crc);



    const char* fc_str = "Family code: 0x28";

    lcd_display_CMockExpectAndReturn(36, fc_str, strlen(fc_str)-1);

    const char* sn_str = "Serial Number: 06:05:04:03:02:01";

    lcd_display_CMockExpectAndReturn(38, sn_str, strlen(sn_str)-1);





    temperture_status_t rvalue = temperture_sensor_initialize();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_INT);

}







void test_temperature_sensor_main_code(void)

{



    test_temperature_sensor_initialization_code();



    ds18b20_do_conversion_CMockExpect(52);





    ds18b20_scratchpad_data_t scratchpad = {

        .lsb = 0x50,

        .msb = 0x05,

        .crc = 0

    };

    ds18b20_read_scratchpad_CMockExpectAndReturn(60, 0, 

   1

   );

    ds18b20_read_scratchpad_CMockIgnoreArg_data(61);

    ds18b20_read_scratchpad_CMockReturnMemThruPtr_data(62, &scratchpad, sizeof(*&scratchpad));



    ds18b20_calculate_CRC_CMockExpectAndReturn(64, (void*)&scratchpad, sizeof(scratchpad)-1, scratchpad.crc);



    ds18b20_convert_CMockExpectAndReturn(66, 0x0550U, 85.0f);



    lcd_display_CMockExpectAndReturn(68, "85.00C", 6);





    temperture_status_t rvalue = temperture_sensor_run();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

}







void test_temperature_sensor_initialization_ds18b20_failure(void)

{





    lcd_initialize_CMockExpectAndReturn(81, 

   1

   );

    ds18b20_initialise_CMockExpectAndReturn(82, R12, 

   0

   );





    temperture_status_t rvalue = temperture_sensor_initialize();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_DS18B20_FALURE)), (

   ((void *)0)

   ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_INT);



}



void test_temperature_sensor_initialization_lcd_failure(void)

{





    lcd_initialize_CMockExpectAndReturn(94, 

   0

   );







    temperture_status_t rvalue = temperture_sensor_initialize();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_LCD_FALIURE)), (

   ((void *)0)

   ), (UNITY_UINT)(99), UNITY_DISPLAY_STYLE_INT);

}



void test_temperature_sensor_initialization_crc_fail(void)

{





    lcd_initialize_CMockExpectAndReturn(106, 

   1

   );

    ds18b20_initialise_CMockExpectAndReturn(107, R12, 

   1

   );



    ds18b20_ROM_t data = {

        .rom_code.family_code = 0x28,

        .rom_code.serial_number = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 } ,

        .rom_code.crc = 0x00,

    };



    ds18b20_read_rom_CMockExpectAndReturn(115, data);



    ds18b20_calculate_CRC_CMockExpectAndReturn(117, (void*)&data, sizeof(data)-1, 0xFF);





    temperture_status_t rvalue = temperture_sensor_initialize();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_DS18B20_FALURE)), (

   ((void *)0)

   ), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_INT);

}



void test_temperature_sensor_initialization_lcd_write_fail_family(void)

{





    lcd_initialize_CMockExpectAndReturn(128, 

   1

   );

    ds18b20_initialise_CMockExpectAndReturn(129, R12, 

   1

   );



    ds18b20_ROM_t data = {

        .rom_code.family_code = 0x28,

        .rom_code.serial_number = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 } ,

        .rom_code.crc = 0x00,

    };



    ds18b20_read_rom_CMockExpectAndReturn(137, data);



    ds18b20_calculate_CRC_CMockExpectAndReturn(139, (void*)&data, sizeof(data)-1, data.rom_code.crc);



    const char* fc_str = "Family code: 0x28";

    lcd_display_CMockExpectAndReturn(142, fc_str, -1);





    temperture_status_t rvalue = temperture_sensor_initialize();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_LCD_FALIURE)), (

   ((void *)0)

   ), (UNITY_UINT)(146), UNITY_DISPLAY_STYLE_INT);

}



void test_temperature_sensor_initialization_lcd_write_fail_sn(void)

{





    lcd_initialize_CMockExpectAndReturn(153, 

   1

   );

    ds18b20_initialise_CMockExpectAndReturn(154, R12, 

   1

   );



    ds18b20_ROM_t data = {

        .rom_code.family_code = 0x28,

        .rom_code.serial_number = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 } ,

        .rom_code.crc = 0x00,

    };



    ds18b20_read_rom_CMockExpectAndReturn(162, data);



    ds18b20_calculate_CRC_CMockExpectAndReturn(164, (void*)&data, sizeof(data)-1, data.rom_code.crc);



    const char* fc_str = "Family code: 0x28";

    lcd_display_CMockExpectAndReturn(167, fc_str, strlen(fc_str)-1);

    const char* sn_str = "Serial Number: 06:05:04:03:02:01";

    lcd_display_CMockExpectAndReturn(169, sn_str, -1);





    temperture_status_t rvalue = temperture_sensor_initialize();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_LCD_FALIURE)), (

   ((void *)0)

   ), (UNITY_UINT)(173), UNITY_DISPLAY_STYLE_INT);

}





void test_temperature_sensor_main_code_read_scratchpad_error(void)

{





    ds18b20_do_conversion_CMockExpect(181);





    ds18b20_scratchpad_data_t scratchpad = {

        .lsb = 0x50,

        .msb = 0x05,

        .crc = 0

    };

    ds18b20_read_scratchpad_CMockExpectAndReturn(189, 0, 

   0

   );

    ds18b20_read_scratchpad_CMockIgnoreArg_data(190);





    temperture_status_t rvalue = temperture_sensor_run();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_DS18B20_FALURE)), (

   ((void *)0)

   ), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_INT);

}



void test_temperature_sensor_main_code_crc_error(void)

{





    ds18b20_do_conversion_CMockExpect(201);





    ds18b20_scratchpad_data_t scratchpad = {

        .lsb = 0x50,

        .msb = 0x05,

        .crc = 0

    };

    ds18b20_read_scratchpad_CMockExpectAndReturn(209, 0, 

   1

   );

    ds18b20_read_scratchpad_CMockIgnoreArg_data(210);

    ds18b20_read_scratchpad_CMockReturnMemThruPtr_data(211, &scratchpad, sizeof(*&scratchpad));



    ds18b20_calculate_CRC_CMockExpectAndReturn(213, (void*)&scratchpad, sizeof(scratchpad)-1, 0xFF);





    temperture_status_t rvalue = temperture_sensor_run();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_DS18B20_FALURE)), (

   ((void *)0)

   ), (UNITY_UINT)(217), UNITY_DISPLAY_STYLE_INT);

}



void test_temperature_sensor_main_code_converts_fail_neg(void)

{





    ds18b20_do_conversion_CMockExpect(224);





    ds18b20_scratchpad_data_t scratchpad = {

        .lsb = 0x50,

        .msb = 0x05,

        .crc = 0

    };

    ds18b20_read_scratchpad_CMockExpectAndReturn(232, 0, 

   1

   );

    ds18b20_read_scratchpad_CMockIgnoreArg_data(233);

    ds18b20_read_scratchpad_CMockReturnMemThruPtr_data(234, &scratchpad, sizeof(*&scratchpad));



    ds18b20_calculate_CRC_CMockExpectAndReturn(236, (void*)&scratchpad, sizeof(scratchpad)-1, scratchpad.crc);



    ds18b20_convert_CMockExpectAndReturn(238, 0x0550U, -100.0f);





    temperture_status_t rvalue = temperture_sensor_run();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_DS18B20_FALURE)), (

   ((void *)0)

   ), (UNITY_UINT)(242), UNITY_DISPLAY_STYLE_INT);

}



void test_temperature_sensor_main_code_converts_fail_positive(void)

{





    ds18b20_do_conversion_CMockExpect(249);





    ds18b20_scratchpad_data_t scratchpad = {

        .lsb = 0x50,

        .msb = 0x05,

        .crc = 0

    };

    ds18b20_read_scratchpad_CMockExpectAndReturn(257, 0, 

   1

   );

    ds18b20_read_scratchpad_CMockIgnoreArg_data(258);

    ds18b20_read_scratchpad_CMockReturnMemThruPtr_data(259, &scratchpad, sizeof(*&scratchpad));



    ds18b20_calculate_CRC_CMockExpectAndReturn(261, (void*)&scratchpad, sizeof(scratchpad)-1, scratchpad.crc);



    ds18b20_convert_CMockExpectAndReturn(263, 0x0550U, 126.0f);





    temperture_status_t rvalue = temperture_sensor_run();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_DS18B20_FALURE)), (

   ((void *)0)

   ), (UNITY_UINT)(267), UNITY_DISPLAY_STYLE_INT);

}



void test_temperature_sensor_main_code_lcd_write_fail(void)

{





    ds18b20_do_conversion_CMockExpect(274);





    ds18b20_scratchpad_data_t scratchpad = {

        .lsb = 0x50,

        .msb = 0x05,

        .crc = 0

    };

    ds18b20_read_scratchpad_CMockExpectAndReturn(282, 0, 

   1

   );

    ds18b20_read_scratchpad_CMockIgnoreArg_data(283);

    ds18b20_read_scratchpad_CMockReturnMemThruPtr_data(284, &scratchpad, sizeof(*&scratchpad));



    ds18b20_calculate_CRC_CMockExpectAndReturn(286, (void*)&scratchpad, sizeof(scratchpad)-1, scratchpad.crc);



    ds18b20_convert_CMockExpectAndReturn(288, 0x0550U, 85.0f);



    lcd_display_CMockExpectAndReturn(290, "85.00C", -1);





    temperture_status_t rvalue = temperture_sensor_run();

    UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_LCD_FALIURE)), (

   ((void *)0)

   ), (UNITY_UINT)(294), UNITY_DISPLAY_STYLE_INT);

}
