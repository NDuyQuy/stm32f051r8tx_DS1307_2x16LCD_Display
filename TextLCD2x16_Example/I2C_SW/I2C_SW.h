#ifndef _I2C_SW_H
#define _I2C_SW_H

#include "main.h"

void I2C_SW_SetSDAPin_Direction(uint8_t u8InOut);
void I2C_SW_Start(void);
void I2C_SW_Stop(void);
void I2C_SW_WriteByte(uint8_t u8Data);
uint8_t I2C_SW_ReadByte(void);












#endif 
