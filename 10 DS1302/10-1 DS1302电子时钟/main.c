#include <REGF51RC.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"

int main()
{
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();
	
	LCD_ShowString(1, 1, "20  -  -");
	LCD_ShowString(2, 1, "  :  :");
	while(1)
	{
		DS1302_ReadTime();
		
		LCD_ShowNum(1, 3, time[0], 2);
		LCD_ShowNum(1, 6, time[1], 2);
		LCD_ShowNum(1, 9, time[2], 2);
		
		LCD_ShowNum(2, 1, time[3], 2);
		LCD_ShowNum(2, 4, time[4], 2);
		LCD_ShowNum(2, 7, time[5], 2);
	}
}