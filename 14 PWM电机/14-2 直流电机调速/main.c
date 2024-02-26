#include <REGF51RC.H>
#include "Delay.h"
#include "Timer.h"
#include "Seg.h"
#include "Key.h"

sbit Motor = P1^0;

unsigned char Counter, Compare;
unsigned char KeyNum, SpeedMode;

int main()
{
	Timer_Init();
	while(1)
	{
		KeyNum = Key();
		
		if(KeyNum == 1)
		{
			SpeedMode ++;
			SpeedMode %= 5;
			
			if(SpeedMode == 0) Compare = 0; // 设置占空比
			if(SpeedMode == 1) Compare = 25;
			if(SpeedMode == 2) Compare = 50;
			if(SpeedMode == 3) Compare = 75;
			if(SpeedMode == 4) Compare = 100;
		}
		seg(1, SpeedMode);
	}
}

void hanser() interrupt 1
{
	TL0 = 0xA4;		
	TH0 = 0xFF;	
	Counter ++; // 100us 自增 + 1
	Counter %= 100; // Counter <= 100
	
	// PWM 
	if(Counter < Compare) Motor = 1;
	else Motor = 0;
}