/** @file lcd.h 
    \brief API for the abstracted LCD Display Module.
*/
#ifndef _LCD_H
#define _LCD_H

#include <stdbool.h>

/*! \fn bool lcd_initialize(void)
    \brief Initialises the LCD Display module
    \return ```true``` if the inialisation was successful
*/ 
bool lcd_initialize(void);

/*! \fn int lcd_display(const char* str)
    \brief Writes a C-String to the LCD display
    \param str ```[IN]``` a null-terminated byte string (NTBS) to be displayed
    \return the actual number of charaters written
*/ 
int lcd_display(const char* str);

#endif // _LCD_H
