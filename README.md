# stm32f051r8tx_DS1307_2x16LCD_Display

# Description
	Using STM32F051 comunication with real-time module DS1307 and display on 2x16LCD. 
	I CONTAIN A SCHEMATIC FOR LCD CONNECTION IN 'ABOUTLCD' FOLDER BUT IT DOESNT CONTAIN THE DS1307 IN IT. BUT THE DS1307 CONNECTION IS 
	QUITE SIMPLE TO DESCRIBLE SO YOU JUST FOLLOW THE CONNECTION OTHER. 
# pin connection


## STM32F051 DISCOVERY KIT                            DS1307
	PORT B PIN6											DS1307_SCL
	PORT B PIN7											DS1307_SDA
## STM32F051 DISCOVERY KIT                            2x16LCD
	PORT A PIN4->7										D4->7
	PORT C PIN0->2										RS>RW>E	