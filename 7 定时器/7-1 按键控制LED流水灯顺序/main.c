#include <REGF51RC.H>
#include "Timer_Init.h"
#include "Delay.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNum, KeyMode;

int main()
{
	Timer_Init();
	P2 = 0xfe;
	while(1)
	{
		KeyNum = Key();
		
		if(KeyNum) // ��ʾ��������
		{
			if(KeyNum == 1) // ���µ� 1 ������, �ı�ģʽ
			{
				KeyMode ++;
				if(KeyMode >= 2) KeyMode = 0;
			}
		}
	}
}

unsigned int Count;
void hanser() interrupt 1
{
	// ÿ�ν����ж϶�Ҫ���¸���ֵ, ��Ϊ init ����ִֻ��һ��
	TL0 = 0x66;	
	TH0 = 0xFC;	
	
	// ������ 0.5s
	Count++;
	if(Count >= 500)
	{
		Count = 0;
		
		if(KeyMode == 0) P2 = _cror_(P2, 1); // ���� 1 λ
		if(KeyMode == 1) P2 = _crol_(P2, 1); // ���� 1 λ
	}
}