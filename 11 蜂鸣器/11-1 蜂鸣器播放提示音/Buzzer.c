#include <REGF51RC.H>
#include "Delay.h"

sbit Buzzer = P2^5;

// ����������ʱ��
void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i = 0; i < ms; i ++) // ��ʾ�� n ms
	{
		// ���� 2ms, Ƶ�� 500Hz
		Buzzer = !Buzzer;
		Delay(1);
	}
}