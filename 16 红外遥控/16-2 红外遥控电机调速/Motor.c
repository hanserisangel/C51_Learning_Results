#include <REGF51RC.H>
#include "Timer1.h"

sbit Motor = P1^0;

unsigned char Counter, Compare;

// ��ʼ��
void Moter_Init()
{
	Timer1_Init();
}

// �޸�ռ�ձ�
void Motor_SetSpeed(unsigned char Speed)
{
	Compare = Speed;
}

// ��ʱ��1�ж�
void Timer1() interrupt 3
{
	TL1 = 0xA4;		
	TH1 = 0xFF;	
	Counter ++; // 100us ���� + 1
	Counter %= 100; // Counter <= 100
	
	// PWM 
	if(Counter < Compare) Motor = 1;
	else Motor = 0;
}