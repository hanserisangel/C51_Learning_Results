#include <REGF51RC.H>

void Timer_Init()       //@11.0592MHz
{
	// TMOD = 0x01 经典初始化
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	// TCON
	TF0 = 0; // 溢出标志, 1 表示溢出, 产生中断 
	TR0 = 0; // 失能定时器 
	
	// 计数单元, 赋初值 
	TL0 = 0;	
	TH0 = 0;	
}

// 设置计数单元
void Timer_SetCounter(unsigned int Value)
{
	TH0 = Value / 256;
	TL0 = Value % 256;
}

// 获取计数单元值
unsigned int Timer_GetCounter(void)
{
	return (TH0<<8)|TL0;
}

// 定时器启停
void Timer_Run(unsigned char Flag)
{
	TR0 = Flag;
}