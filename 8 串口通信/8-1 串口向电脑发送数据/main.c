#include <REGF51RC.H>
#include "Delay.h"
#include "UART.h"

int main()
{
	UART_Init();
	while(1)
	{
		SendByte(0xaa);
		Delay(1); // Ϊ�˵��Կ����ȶ���������
	}
}