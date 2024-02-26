#include <REGF51RC.H>

void UART_Init()		//4800bps@11.0592MHz
{
	// 串口寄存器
	PCON |= 0x80;
	SCON = 0x40;
	
	// 定时器寄存器
	TMOD &= 0x0F;		
	TMOD |= 0x20;		
	
	// 计数单元, 赋初值, 4800bps
	TL1 = 0xF4;		
	TH1 = 0xF4;		
	
	// 中断系统
	ET1 = 0;		//禁止定时器中断
	TR1 = 1;		//启动定时器1
}

void SendByte(unsigned char Byte)
{
	SBUF = Byte; // SBUF 寄存器
	
	// TI 发送完清零
	while(TI == 0);
	TI = 0;
}