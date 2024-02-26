#include <REGF51RC.H>
#include "Delay.h"

sbit Buzzer = P2^5;

// 蜂鸣器持续时间
void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i = 0; i < ms; i ++) // 提示音 n ms
	{
		// 周期 2ms, 频率 500Hz
		Buzzer = !Buzzer;
		Delay(1);
	}
}