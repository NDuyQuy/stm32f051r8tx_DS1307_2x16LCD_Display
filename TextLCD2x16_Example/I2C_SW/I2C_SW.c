#include "I2C_SW.h"
#include "main.h"


void I2C_SW_SetSDAPin_Direction(uint8_t u8InOut)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.Pin = I2C_SDA_Pin;
	
	if(u8InOut == 1)
	{
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
	}else
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	}
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void I2C_SW_Start(void)
{
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,1);
	HAL_GPIO_WritePin(I2C_SDA_GPIO_Port,I2C_SDA_Pin,1);
	HAL_GPIO_WritePin(I2C_SDA_GPIO_Port,I2C_SDA_Pin,0);
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,0);
	__nop();
	__nop();
	__nop();
	__nop();
}


void I2C_SW_Stop(void)
{
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,0);
	HAL_GPIO_WritePin(I2C_SDA_GPIO_Port,I2C_SDA_Pin,0);
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,1);
	HAL_GPIO_WritePin(I2C_SDA_GPIO_Port,I2C_SDA_Pin,1);
	__nop();
	__nop();
	__nop();
	__nop();
}

void I2C_SW_WriteByte(uint8_t u8Data)
{
	uint8_t u8Cnt = 0;
	uint8_t u8TmpData = u8Data;
	
	for(u8Cnt = 0; u8Cnt < 8; u8Cnt++)
	{
		
		if((u8TmpData & 0x80) == 0x80)
		{
			HAL_GPIO_WritePin(I2C_SDA_GPIO_Port,I2C_SDA_Pin,1);
		}
		else
		{
			HAL_GPIO_WritePin(I2C_SDA_GPIO_Port,I2C_SDA_Pin,0);
		}
		u8TmpData <<= 1;
		HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,1);
		__nop();
		__nop();
		__nop();
		__nop();
		HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,0);
	}
	//ACK
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,1);
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,0);
	__nop();
	__nop();
	__nop();
	__nop();
}
uint8_t I2C_SW_ReadByte(void)
{
	uint8_t u8Cnt = 0;
	uint8_t u8data = 0;
	I2C_SW_SetSDAPin_Direction(1);
	for(u8Cnt = 0; u8Cnt < 8; u8Cnt++)
	{
		HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,0);
		
		HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,1);
		__nop();
		__nop();
		__nop();
		__nop();
		u8data<<=1;
		if(HAL_GPIO_ReadPin(I2C_SDA_GPIO_Port,I2C_SDA_Pin)==1)
		{
			u8data |= 1;
		}
	}
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,0);
	I2C_SW_SetSDAPin_Direction(0);
	//NACK
	HAL_GPIO_WritePin(I2C_SDA_GPIO_Port,I2C_SDA_Pin,1);
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,0);
	HAL_GPIO_WritePin(I2C_SCL_GPIO_Port,I2C_SCL_Pin,1);
	__nop();
	__nop();
	__nop();
	__nop();
	return u8data;
}






















