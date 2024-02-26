#include <REGF51RC.H>

unsigned char Key_number;

unsigned char Key() // 返回处理过的按键值
{
	unsigned char temp;
	
	temp = Key_number;
	Key_number = 0; // 清零
	
	return temp;
}

// 每 20ms 检测 P3状态
unsigned char Key_GetState()
{
	unsigned char Keynum = 0;
	
	if(P3_1 == 0) Keynum = 1;
	if(P3_0 == 0) Keynum = 2;
	if(P3_2 == 0) Keynum = 3;
	if(P3_3 == 0) Keynum = 4;
	
	return Keynum;
}

void Key_Loop()
{
	static unsigned char NowState, LastState; // 现态, 上一个状态; 为了检测上升沿
	LastState = NowState;
	NowState = Key_GetState();
	
	if(LastState == 1 && NowState == 0)	Key_number = 1;
	if(LastState == 2 && NowState == 0)	Key_number = 2;
	if(LastState == 3 && NowState == 0)	Key_number = 3;
	if(LastState == 4 && NowState == 0)	Key_number = 4;
}
