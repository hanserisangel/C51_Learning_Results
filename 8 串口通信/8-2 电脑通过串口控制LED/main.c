#include <REGF51RC.H>
#include "Delay.h"
#include "UART.h"

int main()
{
	UART_Init();
	while(1)
	{
		
	}
}

void hanser() interrupt 4
{
	if(RI == 1) // 因为发送数据 TI = 1 时也会进入中断, 所以这里要特判一下
	{
		P2 = SBUF;
		
		SendByte(SBUF); // 发送接收到的数据
		
		RI = 0; // 接收完清零
	}
}