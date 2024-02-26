#include <REGF51RC.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "AT24C02.h"
#include "Key.h"
#include "Delay.h"
#include "Timer.h"

unsigned char KeyNumber;
float T, Tshow;
char TL, TH;

int main()
{
	LCD_Init();
	Timer_Init();
	LCD_ShowString(1, 1, "T:");
	LCD_ShowChar(1, 6, '.');
	LCD_ShowString(2, 1, "TH:");
	LCD_ShowString(2, 9, "TL:");
	
	TH = AT24C02_ReadByte(0);
	TL = AT24C02_ReadByte(1);
	
	LCD_ShowSignedNum(2, 4, TH, 3);
	LCD_ShowSignedNum(2, 12, TL, 3);
	while(1)
	{
		KeyNumber = Key();
		// 温度读取显示
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		
		if(T < 0)
		{
			LCD_ShowChar(1, 3, '-');
			Tshow = -T;
		}
		else
		{
			LCD_ShowChar(1, 3, '+');
			Tshow = T;
		}
		
		LCD_ShowNum(1, 4, Tshow, 2);
		LCD_ShowNum(1, 7,(unsigned long) (Tshow * 10000)%10000, 4);
		
		// 温度阈值显示
		if(KeyNumber)
		{
			if(KeyNumber == 1) TH ++;
			if(KeyNumber == 2)
			{
				if(TH > TL) TH --;
			}
			if(KeyNumber == 3)
			{
				if(TH > TL)	TL ++;
			}
			if(KeyNumber == 4) TL --;
			LCD_ShowSignedNum(2, 4, TH, 3);
			LCD_ShowSignedNum(2, 12, TL, 3);
			
			AT24C02_WriteByte(0, TH);
			Delay(5);
			AT24C02_WriteByte(1, TL);
			Delay(5);
		}
		
		// 温度报警
		if(T > TH) LCD_ShowString(1, 13, "OVH");
		else if(T < TL) LCD_ShowString(1, 13, "OVL");
		else LCD_ShowString(1, 13, "   ");
	}
}

unsigned int Count;
void hanser() interrupt 1
{
	TL0 = 0x66;	
	TH0 = 0xFC;	
	Count++;
	if(Count >= 20)
	{
		Count = 0;
		 Key_Loop();
	}
}