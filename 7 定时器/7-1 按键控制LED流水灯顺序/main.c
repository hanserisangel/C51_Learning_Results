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
		
		if(KeyNum) // 表示按键按下
		{
			if(KeyNum == 1) // 按下第 1 个按键, 改变模式
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
	// 每次进入中断都要重新赋初值, 因为 init 函数只执行一次
	TL0 = 0x66;	
	TH0 = 0xFC;	
	
	// 计数到 0.5s
	Count++;
	if(Count >= 500)
	{
		Count = 0;
		
		if(KeyMode == 0) P2 = _cror_(P2, 1); // 右移 1 位
		if(KeyMode == 1) P2 = _crol_(P2, 1); // 左移 1 位
	}
}