#ifndef _DS1307_CONTROL_H
#define _DS1307_CONTROL_H

#include "main.h"
#include "I2C_SW.h"

void DS1307_setTime(uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void DS1307_getTime(uint8_t* timeBuffer);
#endif 