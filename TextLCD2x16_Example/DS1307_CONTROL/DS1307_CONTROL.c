#include "I2C_SW.h"
#include "main.h"
#include "DS1307_CONTROL.h"

#define DS1307_W_ADDR	0xD0
#define DS1307_R_ADDR	0xD1

uint8_t DS1307_ReadByte(uint8_t u8Addr)
{
	I2C_SW_Start();
	I2C_SW_WriteByte(DS1307_W_ADDR);
	I2C_SW_WriteByte(u8Addr);
	I2C_SW_Start();
	I2C_SW_WriteByte(DS1307_R_ADDR);
	uint8_t dataRead = I2C_SW_ReadByte();
	I2C_SW_Stop();
	
	return dataRead;
}
void DS1307_WriteByte(uint8_t u8Addr, uint8_t u8Data)
{
	I2C_SW_Start();
	I2C_SW_WriteByte(DS1307_W_ADDR);
	I2C_SW_WriteByte(u8Addr);
	I2C_SW_WriteByte(u8Data);
	I2C_SW_Stop();
}

uint8_t Dec2Bin(uint8_t num)
{
	return ((num/10*16)+num%10) ;
}
uint8_t Bin2Dec(uint8_t num)
{
	return ((num/16*10)+num%16);
}
uint8_t DS1307_getSec(void)
{
	uint8_t sec = DS1307_ReadByte(0x0);
	sec = Bin2Dec(sec);
	return sec;
}

uint8_t DS1307_getMin(void)
{
	uint8_t min = DS1307_ReadByte(0X01);
	min = Bin2Dec(min);
	return min;
}
 
void DS1307_setMin(uint8_t time)
{
	uint8_t t = Dec2Bin(time);
	DS1307_WriteByte(0X01,t);
}
uint8_t DS1307_getHour(void)
{
	uint8_t hour = DS1307_ReadByte(0X02);
	if((hour&0X40) == 0x40)
	{
		if((hour&0x20)==0x20)
		{
			hour+=12;
		}
		hour &=0x3F;
		hour += Bin2Dec(hour);
		if(hour==24) hour=0;
	}
	else
	{
		hour &=0x3F;
		hour = Bin2Dec(hour);
	}
	return hour;
}
uint8_t DS1307_getDay(void)
{
	uint8_t day = DS1307_ReadByte(0X03);
	return (Bin2Dec(day));
}
uint8_t DS1307_getDate(void)
{
	uint8_t date = DS1307_ReadByte(0x04);
	return (Bin2Dec(date));
}
uint8_t DS1307_getMonth(void)
{
	uint8_t month = DS1307_ReadByte(0x05);
	return (Bin2Dec(month));
}
uint8_t DS1307_getYear(void)
{
	uint8_t year = DS1307_ReadByte(0x06);
	return (Bin2Dec(year));
}
void DS1307_setHour(uint8_t time)
{
	uint8_t t = Dec2Bin(time);
	DS1307_WriteByte(0x02,t);
}
void DS1307_setDay(uint8_t time)
{
	uint8_t t = Dec2Bin(time);
	DS1307_WriteByte(0x03,t);
}
void DS1307_setDate(uint8_t time)
{
	uint8_t t = Dec2Bin(time);
	DS1307_WriteByte(0x04,t);
}
void DS1307_setMonth(uint8_t time)
{
	uint8_t t = Dec2Bin(time);
	DS1307_WriteByte(0x05,t);
}
void DS1307_setYear(uint8_t time)
{
	uint8_t t = Dec2Bin(time);
	DS1307_WriteByte(0x06,t);
}
void DS1307_setTime(uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
	DS1307_setMin(min);
	__nop();
	__nop();
	DS1307_setHour(hour);
	__nop();
	__nop();
	DS1307_setDay(day);
	__nop();
	__nop();
	DS1307_setDate(date);
	__nop();
	__nop();
	DS1307_setMonth(month);
	__nop();
	__nop();
	DS1307_setYear(year);
	__nop();
	__nop();
}
void DS1307_getTime(uint8_t* timeBuffer)
{
	timeBuffer[0] = DS1307_getMin();
	__nop();
	__nop();
	timeBuffer[1] = DS1307_getHour();
	__nop();
	__nop();
	timeBuffer[2] = DS1307_getDay();
	__nop();
	__nop();
	timeBuffer[3] = DS1307_getDate();
	__nop();
	__nop();
	timeBuffer[4] = DS1307_getMonth();
	__nop();
	__nop();
	timeBuffer[5] = DS1307_getYear();
	__nop();
	__nop();
}
