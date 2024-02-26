#include <REGF51RC.H>

void Int0_Init()
{
	IT0 = 1; // 下降沿
	IE0 = 0;
	EX0 = 1;
	EA = 1;
	PX0 = 1; // 高优先级中断
}

/* 外部中断函数
void hanser() interrupt 0
{

}
*/