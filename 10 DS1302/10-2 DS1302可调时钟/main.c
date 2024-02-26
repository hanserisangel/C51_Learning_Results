#include <REGF51RC.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer.h"

unsigned char KeyNum, KeyMode, KeySel, flag;

void TimeShow()
{
	DS1302_ReadTime();
		
	// BCD码 → 十进制
	LCD_ShowNum(1, 3, time[0], 2);
	LCD_ShowNum(1, 6, time[1], 2);
	LCD_ShowNum(1, 9, time[2], 2);
	
	LCD_ShowNum(2, 1, time[3], 2);
	LCD_ShowNum(2, 4, time[4], 2);
	LCD_ShowNum(2, 7, time[5], 2);
}

void TimeSet()
{
	// 第 2 个按键: 用来选择调整位(0: 年; 1: 月; ...)
	if(KeyNum == 2)
	{
		KeySel ++;
		KeySel = KeySel % 6;
	}
	
	if(KeyNum == 3) // 增加按键
	{
		time[KeySel] ++;
		if(time[0] > 99) time[0] = 0; // 年越界
		if(time[1] > 12) time[1] = 1; // 月越界
		
		// 日越界
		if( time[1] == 1 || time[1] == 3 || time[1] == 5 || time[1] == 7 || 
			time[1] == 8 || time[1] == 10 || time[1] == 12)
		{
			if(time[2] > 31) time[2] = 1;
		}
		else if(time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11)
		{
			if(time[2] > 30) time[2] = 1;
		}
		else if(time[1] == 2)
		{
			if(time[0]%4 == 0)
			{
				if(time[2] > 29) time[2] = 1;
			}
			else
			{
				if(time[2] > 28) time[2] = 1;
			}
		}
		
		if(time[3] > 23) time[3] = 0; // 时越界
		if(time[4] > 59) time[4] = 0; // 分越界
		if(time[5] > 59) time[5] = 0; // 秒越界
	}
	
	if(KeyNum == 4) // 减小按键
	{
		time[KeySel] --;
		if(time[0] < 0) time[0] = 99;
		if(time[1] < 1) time[1] = 12;
		if( time[1] == 1 || time[1] == 3 || time[1] == 5 || time[1] == 7 || 
			time[1] == 8 || time[1] == 10 || time[1] == 12)
		{
			if(time[2] < 1) time[2] = 31;
			if(time[2] > 31) time[2] = 1;
		}
		else if(time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11)
		{
			if(time[2] < 1) time[2] = 30;
			if(time[2] > 30) time[2] = 1;
		}
		else if(time[1] == 2)
		{
			if(time[0]%4 == 0)
			{
				if(time[2] < 1) time[2] = 29;
				if(time[2] > 29) time[2] = 1;
			}
			else
			{
				if(time[2] < 1) time[2] = 28;
				if(time[2] > 28) time[2] = 1;
			}
		}
		if(time[3] < 0) time[3] = 23;
		if(time[4] < 0) time[4] = 59;
		if(time[5] < 0) time[5] = 59;
	}
	
	// 闪烁显示
	if(KeySel == 0 && flag == 1) LCD_ShowString(1, 3, "  ");
	else LCD_ShowNum(1, 3, time[0], 2);
	if(KeySel == 1 && flag == 1) LCD_ShowString(1, 6, "  ");
	else LCD_ShowNum(1, 6, time[1], 2);
	if(KeySel == 2 && flag == 1) LCD_ShowString(1, 9, "  ");
	else LCD_ShowNum(1, 9, time[2], 2);
	if(KeySel == 3 && flag == 1) LCD_ShowString(2, 1, "  ");
	else LCD_ShowNum(2, 1, time[3], 2);
	if(KeySel == 4 && flag == 1) LCD_ShowString(2, 4, "  ");
	else LCD_ShowNum(2, 4, time[4], 2);
	if(KeySel == 5 && flag == 1) LCD_ShowString(2, 7, "  ");
	else LCD_ShowNum(2, 7, time[5], 2);
}

int main()
{
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();
	Timer_Init();
	
	LCD_ShowString(1, 1, "20  -  -");
	LCD_ShowString(2, 1, "  :  :");
	while(1)
	{
		KeyNum = Key();
		
		// 第 1 个按键: 用来切换模式(0: 走时; 1: 调时)
		if(KeyNum == 1)
		{
			if(KeyMode == 1)
			{
				KeyMode = 0;
				DS1302_SetTime();
			}
			else if(KeyMode == 0)
			{
				KeyMode = 1;
				KeySel = 0;
			}
		}
		switch(KeyMode)
		{
			case 0: TimeShow(); break;
			case 1: TimeSet(); break;
		}
	}
}

unsigned int Count;
void hanser() interrupt 1
{
	TL0 = 0x66;	
	TH0 = 0xFC;	
	Count++;
	if(Count >= 500)
	{
		Count = 0;
		flag = !flag;
	}
}