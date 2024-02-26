#include <REGF51RC.H>
#include "Timer.h"
#include "Delay.h"

#define TIME_Quarter_note 250
// 4 ��������һ�� 500ms �� 250ms
sbit Buzzer = P2^5;

unsigned char FreqSel, MusicSel; // ����ѡ������, ����ѡ������

// ����: excel �õ��ļ�����װֵ
unsigned int Freq[] = {
	0, // ��ֹ��
	63777, 63872, 63969, 64054, 64140, 64216, 64291, 64360, 64426, 64489, 64547, 64603,
	64655, 64704, 64751, 64795, 64837, 64876, 64913, 64948, 64981, 65012, 65042, 65070,
	65095, 65120, 65144, 65166, 65186, 65206, 65225, 65242, 65259, 65274, 65289, 65303
};

// ����: pair(�������������, ������ʱ��)
unsigned char code Music[] = {
	// һ��һ��������
	13, 1,
	13, 1,
	20, 1,
	20, 1,
	22, 1,
	22, 1,
	20, 2,
	
	// ���춼��С����
	18, 1,
	18, 1,
	17, 1,
	17, 1,
	15, 1,
	15, 1,
	13, 2,
	
	0xff // ��ֹ��, ������Խ��
};

int main()
{
	Timer_Init();
	while(1)
	{
		if(Music[MusicSel] != 0xff) // ��ֹ��
		{
			// ȷ������
			FreqSel = Music[MusicSel];
			MusicSel ++;
			
			// ȷ������
			Delay(TIME_Quarter_note * Music[MusicSel]);
			MusicSel ++;
			
			// ����, ��Ҫ����
			TR0 = 0; // �رն�ʱ��
			Delay(5);
			TR0 = 1; // �򿪶�ʱ��
		}
		else
		{
			TR0 = 0; // �رն�ʱ��
		}
	}
}

void hanser() interrupt 1
{
	if(Freq[FreqSel]) // ��ֹ������
	{
		// �޸�Ƶ��
		TL0 = Freq[FreqSel] % 256; // �� 8 λ
		TH0 = Freq[FreqSel] / 256; // �� 8 λ
		
		// ��ת��ƽ, ���ɲ���
		Buzzer = !Buzzer;
	}
}