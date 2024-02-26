#include <REGF51RC.H>

void Timer1_Init()       //@11.0592MHz
{
	// TMOD = 0x01 �����ʼ��
	TMOD &= 0x0F;
	TMOD |= 0x10;
	
	// TCON
	TF1 = 0; // �����־, 1 ��ʾ���, �����ж� 
	TR1 = 1; // ʹ�ܶ�ʱ�� 
	
	// ������Ԫ, ����ֵ, �� 100us 
	TL1 = 0xA4;		
	TH1 = 0xFF;		
	
	//�ж�ϵͳ
	ET1=1; // ��ʱ�ж�ʹ�� 
	EA=1; // �ж��ܿ���ʹ�� 
	PT1=0; // ���ȼ����� 
}

/* �������ж�ģ��
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
