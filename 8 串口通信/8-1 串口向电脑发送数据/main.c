#include <REGF51RC.H>
#include "Delay.h"
#include "UART.h"

int main()
{
	UART_Init();
	while(1)
	{
		SendByte(0xaa);
		Delay(1); // 为了电脑可以稳定接收数据
	}
}