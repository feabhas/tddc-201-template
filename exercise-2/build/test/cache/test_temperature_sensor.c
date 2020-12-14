#include "build/temp/_test_temperature_sensor.c"
#include "lcd.h"
#include "ds18b20.h"
#include "unity.h"
#include "temperature_sensor.h"












void setUp(void) {}



void tearDown(void) {}



void test_temperature_sensor_initialization_code(void)

{

  UnityIgnore( (

 ((void *)0)

 ), (UNITY_UINT)(17));

  temperture_status_t rvalue = temperture_sensor_initialize();

  UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_OK)), (

 ((void *)0)

 ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_INT);

}



void test_temperature_sensor_main_code(void)

{

  UnityIgnore( (

 ((void *)0)

 ), (UNITY_UINT)(24));

  temperture_sensor_initialize();

  temperture_status_t rvalue = temperture_sensor_run();

  UnityAssertEqualNumber((UNITY_INT)((rvalue)), (UNITY_INT)((TEMP_OK)), (

 ((void *)0)

 ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);

}
