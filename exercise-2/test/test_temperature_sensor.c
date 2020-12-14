#include "temperature_sensor.h"
#include "unity.h"

// include dependent modules for compilation/linking
#include "ds18b20.h"
#include "lcd.h"

#include <stdio.h>
#include <string.h>

void setUp(void) {}

void tearDown(void) {}

void test_temperature_sensor_initialization_code(void)
{
  TEST_IGNORE(); // remove when ready to run test
  temperture_status_t rvalue = temperture_sensor_initialize();
  TEST_ASSERT_EQUAL_INT(rvalue, TEMP_OK);
}

void test_temperature_sensor_main_code(void)
{
  TEST_IGNORE(); // remove when ready to run test
  temperture_sensor_initialize();
  temperture_status_t rvalue = temperture_sensor_run();
  TEST_ASSERT_EQUAL_INT(rvalue, TEMP_OK);
}
