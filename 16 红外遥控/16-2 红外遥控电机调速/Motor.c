#include <REGF51RC.H>
#include "Timer1.h"

sbit Motor = P1^0;

unsigned char Counter, Compare;

// 初始化
void Moter_Init()
{
	Timer1_Init();
}

// 修改占空比
void Motor_SetSpeed(unsigned char Speed)
{
	Compare = Speed;
}

// 定时器1中断
void Timer1() interrupt 3
{
	TL1 = 0xA4;		
	TH1 = 0xFF;	
	Counter ++; // 100us 自增 + 1
	Counter %= 100; // Counter <= 100
	
	// PWM 
	if(Counter < Compare) Motor = 1;
	else Motor = 0;
}