#include <REGF51RC.H>
#include "Timer.h"
#include "Delay.h"

#define TIME_Quarter_note 250
// 4 分音符的一拍 500ms 或 250ms
sbit Buzzer = P2^5;

unsigned char FreqSel, MusicSel; // 音高选择索引, 乐谱选择索引

// 音高: excel 得到的计数重装值
unsigned int Freq[] = {
	0, // 休止符
	63777, 63872, 63969, 64054, 64140, 64216, 64291, 64360, 64426, 64489, 64547, 64603,
	64655, 64704, 64751, 64795, 64837, 64876, 64913, 64948, 64981, 65012, 65042, 65070,
	65095, 65120, 65144, 65166, 65186, 65206, 65225, 65242, 65259, 65274, 65289, 65303
};

// 乐谱: pair(音高数组的索引, 音符的时长)
unsigned char code Music[] = {
	// 一闪一闪亮晶晶
	13, 1,
	13, 1,
	20, 1,
	20, 1,
	22, 1,
	22, 1,
	20, 2,
	
	// 满天都是小星星
	18, 1,
	18, 1,
	17, 1,
	17, 1,
	15, 1,
	15, 1,
	13, 2,
	
	0xff // 终止符, 防数组越界
};

int main()
{
	Timer_Init();
	while(1)
	{
		if(Music[MusicSel] != 0xff) // 终止符
		{
			// 确定音高
			FreqSel = Music[MusicSel];
			MusicSel ++;
			
			// 确定音长
			Delay(TIME_Quarter_note * Music[MusicSel]);
			MusicSel ++;
			
			// 断音, 不要连音
			TR0 = 0; // 关闭定时器
			Delay(5);
			TR0 = 1; // 打开定时器
		}
		else
		{
			TR0 = 0; // 关闭定时器
		}
	}
}

void hanser() interrupt 1
{
	if(Freq[FreqSel]) // 休止符特判
	{
		// 修改频率
		TL0 = Freq[FreqSel] % 256; // 低 8 位
		TH0 = Freq[FreqSel] / 256; // 高 8 位
		
		// 翻转电平, 生成波形
		Buzzer = !Buzzer;
	}
}