#include <REGF51RC.H>

void UART_Init()		//4800bps@11.0592MHz
{
	// ���ڼĴ���
	PCON |= 0x80;
	SCON = 0x40;
	
	// ��ʱ���Ĵ���
	TMOD &= 0x0F;		
	TMOD |= 0x20;		
	
	// ������Ԫ, ����ֵ, 4800bps
	TL1 = 0xF4;		
	TH1 = 0xF4;		
	
	// �ж�ϵͳ
	ET1 = 0;		//��ֹ��ʱ���ж�
	TR1 = 1;		//������ʱ��1
}

void SendByte(unsigned char Byte)
{
	SBUF = Byte; // SBUF �Ĵ���
	
	// TI ����������
	while(TI == 0);
	TI = 0;
}