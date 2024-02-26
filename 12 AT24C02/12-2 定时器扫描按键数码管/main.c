#include <REGF51RC.H>
#include "Delay.h"
#include "Key.h"
#include "I2C.h"
#include "AT24C02.h"
#include "Seg.h"
#include "Timer.h"

unsigned char Keynumber, runflag;
unsigned char minute, second, msecond;

int main()
{
	Timer_Init();
	while(1)
	{
		Keynumber = Key();
		
		if(Keynumber == 1) runflag = !runflag;
		
		if(Keynumber == 2)
		{
			minute = 0;
			second = 0;
			msecond = 0;
		}
		
		if(Keynumber == 3)
		{
			AT24C02_WriteByte(0, minute);
			Delay(5);
			AT24C02_WriteByte(1, second);
			Delay(5);
			AT24C02_WriteByte(2, msecond);
			Delay(5);
		}
		
		if(Keynumber == 4)
		{
			minute = AT24C02_ReadByte(0);
			second = AT24C02_ReadByte(1);
			msecond = AT24C02_ReadByte(2);
		}
		
		Seg_SetBuf(1, minute/10);
		Seg_SetBuf(2, minute%10);
		
		Seg_SetBuf(3, 11);
		
		Seg_SetBuf(4, second/10);
		Seg_SetBuf(5, second%10);
		
		Seg_SetBuf(6, 11);
		
		Seg_SetBuf(7, msecond/10);
		Seg_SetBuf(8, msecond%10);
	}
}

void Set_Loop()
{
	if(runflag)
	{
		msecond ++;
		if(msecond >= 100)
		{
			msecond = 0;
			second ++;
			if(second >= 60)
			{
				second = 0;
				minute ++;
				if(minute >= 60) minute = 0;
			}
		}
	}
}

unsigned int Count1, Count2, Count3;
void hanser() interrupt 1
{
	TL0 = 0x66;	
	TH0 = 0xFC;	
	Count1++;
	if(Count1 >= 20) // 去除按键消抖的 Delay, while
	{
		Count1 = 0;
		Key_loop(); // 驱动函数, 循环函数
	}
	Count2++;
	if(Count2 >= 2) // 为了动态扫描时, 主函数可以执行耗时长的操作
	{
		Count2 = 0;
		Seg_Loop();
	}
	Count3++;
	if(Count3 >= 10) // 秒表计数
	{
		Count3 = 0;
		Set_Loop();
	}
}