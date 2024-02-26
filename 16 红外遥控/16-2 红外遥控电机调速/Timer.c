#include <REGF51RC.H>

void Timer_Init()       //@11.0592MHz
{
	// TMOD = 0x01 �����ʼ��
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	// TCON
	TF0 = 0; // �����־, 1 ��ʾ���, �����ж� 
	TR0 = 0; // ʧ�ܶ�ʱ�� 
	
	// ������Ԫ, ����ֵ 
	TL0 = 0;	
	TH0 = 0;	
}

// ���ü�����Ԫ
void Timer_SetCounter(unsigned int Value)
{
	TH0 = Value / 256;
	TL0 = Value % 256;
}

// ��ȡ������Ԫֵ
unsigned int Timer_GetCounter(void)
{
	return (TH0<<8)|TL0;
}

// ��ʱ����ͣ
void Timer_Run(unsigned char Flag)
{
	TR0 = Flag;
}