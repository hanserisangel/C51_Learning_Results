#include <REGF51RC.H>

void Timer_Init()       //@11.0592MHz
{
	// TMOD = 0x01 �����ʼ��
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	// TCON
	TF0 = 0; // �����־, 1 ��ʾ���, �����ж� 
	TR0 = 1; // ʹ�ܶ�ʱ�� 
	
	// ������Ԫ, ����ֵ, �� 100us 
	TL0 = 0xA4;		
	TH0 = 0xFF;		
	
	//�ж�ϵͳ
	ET0=1; // ��ʱ�ж�ʹ�� 
	EA=1; // �ж��ܿ���ʹ�� 
	PT0=0; // ���ȼ����� 
}

/* �������ж�ģ��
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
