/** @file temperature_sensor.h 
    \brief API for the abstracted Temperature Sensor module.
*/
#ifndef _TEMPERATURE_SENSOR_H
#define _TEMPERATURE_SENSOR_H

typedef enum { TEMP_OK, TEMP_LCD_FALIURE, TEMP_DS18B20_FALURE } temperture_status_t;
/*! \fn void temperture_sensor_initialize(void)
    \brief Initialise the genertic Temperature Sensor Interface
*/ 
temperture_status_t temperture_sensor_initialize(void);

/*! \fn void temperture_sensor_run(void)
    \brief Perform the reading of the raw temperature sensor and displays the value
*/ 
temperture_status_t temperture_sensor_run(void);

#endif // _TEMPERATURE_SENSOR_H
