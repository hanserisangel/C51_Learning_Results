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
	if(RI == 1) // ��Ϊ�������� TI = 1 ʱҲ������ж�, ��������Ҫ����һ��
	{
		P2 = SBUF;
		
		SendByte(SBUF); // ���ͽ��յ�������
		
		RI = 0; // ����������
	}
}