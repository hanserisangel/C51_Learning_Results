#include <REGF51RC.H>
#include "Delay.h"
#include "Timer.h"

sbit DA_LED = P2^1;

unsigned char Counter, Compare;
unsigned char i;

int main()
{
	Timer_Init();
	while(1)
	{
		for(i = 0; i < 100; i ++)
		{
			Compare = i;
			Delay(10);
		}
		for(i = 100; i > 0; i --)
		{
			Compare = i;
			Delay(10);
		}
	}
}

void hanser() interrupt 1
{
	TL0 = 0xA4;		
	TH0 = 0xFF;	
	Counter ++; // 100us ×ÔÔö + 1
	Counter %= 100; // Counter <= 100
	
	// PWM 
	if(Counter < Compare) DA_LED = 1;
	else DA_LED = 0;
}