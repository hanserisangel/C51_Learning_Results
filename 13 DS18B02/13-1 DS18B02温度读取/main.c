#include <REGF51RC.H>
#include "LCD1602.h"
#include "OneWire.h"
#include "DS18B20.h"

float T;

int main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "Temperature");
	LCD_ShowChar(2, 4, '.');
	while(1)
	{
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		
		if(T < 0)
		{
			LCD_ShowChar(2, 1, '-');
			T = -T;
		}
		else LCD_ShowChar(2, 1, '+');
		
		LCD_ShowNum(2, 2, T, 2);
		LCD_ShowNum(2, 5,(unsigned long) (T * 10000)%10000, 4);
	}
}