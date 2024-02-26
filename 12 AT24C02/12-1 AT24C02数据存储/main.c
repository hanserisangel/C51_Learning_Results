#include <REGF51RC.H>
#include "Delay.h"
#include "Key.h"
#include "LCD1602.h"
#include "I2C.h"
#include "AT24C02.h"

unsigned char KeyNum;
unsigned int number;

int main()
{
	LCD_Init();
	LCD_ShowNum(1, 1, number, 5);
	while(1)
	{
		KeyNum = Key();
		
		if(KeyNum == 1)
		{
			number ++;
			LCD_ShowNum(1, 1, number, 5);
		}
		if(KeyNum == 2)
		{
			number --;
			LCD_ShowNum(1, 1, number, 5);
		}
		if(KeyNum == 3) // 写数据
		{
			AT24C02_WriteByte(0, number % 256); // 16位数据
			Delay(5); // 写周期(写反应时间)
			AT24C02_WriteByte(1, number / 256);
			Delay(5);
			LCD_ShowString(2, 1, "Write OK");
			Delay(1000);
			LCD_ShowString(2, 1, "        ");
		}
		if(KeyNum == 4) // 读数据
		{
			number = AT24C02_ReadByte(0); // 16位数据
			number |= AT24C02_ReadByte(1) << 8;
			LCD_ShowNum(1, 1, number, 5);
			LCD_ShowString(2, 1, "Read OK");
			Delay(1000);
			LCD_ShowString(2, 1, "       ");
		}
	}
}