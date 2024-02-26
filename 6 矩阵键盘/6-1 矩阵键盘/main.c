#include <REGF51RC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char Keynum;

int main()
{
	LCD_Init(); // LCD1602 初始化
	while(1)
	{
		// 不停地获取键码
		Keynum = MatrixKey();
		
		if(Keynum) LCD_ShowNum(1, 1, Keynum, 2);
	}
}