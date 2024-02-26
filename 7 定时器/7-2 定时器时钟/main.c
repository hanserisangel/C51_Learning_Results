#include <REGF51RC.H>
#include "Timer_Init.h"
#include "Delay.h"
#include "Key.h"
#include "LCD1602.h"

unsigned char Second, Minute, Hour;

int main()
{
	Timer_Init();
	LCD_Init();
	LCD_ShowString(1, 1, "Clock");
	LCD_ShowString(2, 1, "  :  :");

	while(1)
	{
		LCD_ShowNum(2, 1, Hour, 2);
		LCD_ShowNum(2, 4, Minute, 2);
		LCD_ShowNum(2, 7, Second, 2);
	}
}

unsigned int Count;
void hanser() interrupt 1
{
	// ÿ�ν����ж϶�Ҫ���¸���ֵ, ��Ϊ init ����ִֻ��һ��
	TL0 = 0x66;	
	TH0 = 0xFC;	
	
	// ������ 1s
	Count++;
	if(Count >= 1000)
	{
		Count = 0;
		
		Second ++;
		if(Second >= 60)
		{
			Second = 0;
			Minute ++;
			
			if(Minute >= 60)
			{
				Minute = 0;
				Hour ++;
				
				if(Hour >= 24) Hour = 0;
			}
		}
	}
}

