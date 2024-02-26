#include <REGF51RC.H>

void Timer1_Init()       //@11.0592MHz
{
	// TMOD = 0x01 经典初始化
	TMOD &= 0x0F;
	TMOD |= 0x10;
	
	// TCON
	TF1 = 0; // 溢出标志, 1 表示溢出, 产生中断 
	TR1 = 1; // 使能定时器 
	
	// 计数单元, 赋初值, 计 100us 
	TL1 = 0xA4;		
	TH1 = 0xFF;		
	
	//中断系统
	ET1=1; // 定时中断使能 
	EA=1; // 中断总开关使能 
	PT1=0; // 优先级设置 
}

/* 计数器中断模板
	unsigned int Count;
	void Timer1() interrupt 3
	{
		TL1 = 0x66;	
		TH1 = 0xFC;	
		Count++;
		if(Count >= 1000)
		{
			Count = 0;
			P2_0 = ~P2_0;
		}
	}
*/
