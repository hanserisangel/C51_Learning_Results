#include <REGF51RC.H>

void Timer_Init()       //@11.0592MHz
{
	// TMOD = 0x01 经典初始化
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	// TCON
	TF0 = 0; // 溢出标志, 1 表示溢出, 产生中断 
	TR0 = 1; // 使能定时器 
	
	// 计数单元, 赋初值, 计 100us 
	TL0 = 0xA4;		
	TH0 = 0xFF;		
	
	//中断系统
	ET0=1; // 定时中断使能 
	EA=1; // 中断总开关使能 
	PT0=0; // 优先级设置 
}

/* 计数器中断模板
	unsigned int Count;
	void hanser() interrupt 1
	{
		TL0 = 0x66;	
		TH0 = 0xFC;	
		Count++;
		if(Count >= 1000)
		{
			Count = 0;
			P2_0 = ~P2_0;
		}
	}
*/
