#include <REGF51RC.H>

void UART_Init()		//4800bps@11.0592MHz
{
	// 串口寄存器
	PCON |= 0x80;
	SCON = 0x50; // 接收时使能 REN = 1
	
	// 定时器寄存器
	TMOD &= 0x0F;		
	TMOD |= 0x20;		
	
	// 计数单元, 赋初值, 4800bps
	TL1 = 0xF4;		
	TH1 = 0xF4;		
	
	// 中断系统
	ET1 = 0;		//禁止定时器中断
	TR1 = 1;		//启动定时器1
	ES = 1;         //启动串口中断
	EA = 1;
}

void SendByte(unsigned char Byte)
{
	SBUF = Byte; // SBUF 寄存器
	
	// TI 发送完清零
	while(TI == 0);
	TI = 0;
}

/* 接收串口中断函数模板
	void hanser() interrupt 4
	{
		if(RI == 1) // 因为发送数据 TI = 1 时也会进入中断, 所以这里要特判一下
		{
			P2 = SBUF;
			
			SendByte(SBUF); // 发送接收到的数据
			
			RI = 0; // 接收完清零
		}
	}
*/