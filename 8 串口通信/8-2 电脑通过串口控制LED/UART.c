#include <REGF51RC.H>

void UART_Init()		//4800bps@11.0592MHz
{
	// ���ڼĴ���
	PCON |= 0x80;
	SCON = 0x50; // ����ʱʹ�� REN = 1
	
	// ��ʱ���Ĵ���
	TMOD &= 0x0F;		
	TMOD |= 0x20;		
	
	// ������Ԫ, ����ֵ, 4800bps
	TL1 = 0xF4;		
	TH1 = 0xF4;		
	
	// �ж�ϵͳ
	ET1 = 0;		//��ֹ��ʱ���ж�
	TR1 = 1;		//������ʱ��1
	ES = 1;         //���������ж�
	EA = 1;
}

void SendByte(unsigned char Byte)
{
	SBUF = Byte; // SBUF �Ĵ���
	
	// TI ����������
	while(TI == 0);
	TI = 0;
}

/* ���մ����жϺ���ģ��
	void hanser() interrupt 4
	{
		if(RI == 1) // ��Ϊ�������� TI = 1 ʱҲ������ж�, ��������Ҫ����һ��
		{
			P2 = SBUF;
			
			SendByte(SBUF); // ���ͽ��յ�������
			
			RI = 0; // ����������
		}
	}
*/