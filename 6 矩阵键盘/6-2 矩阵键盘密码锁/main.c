#include <REGF51RC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char Keynum;
unsigned int Password;

int main()
{
	LCD_Init(); // LCD1602 初始化
	LCD_ShowString(1, 1, "Password:");
	while(1)
	{
		// 不停地获取键码
		Keynum = MatrixKey();
		
		// 表示按键按下
		if(Keynum)
		{
			// 组建输入的密码
			if(Keynum <= 10)
			{
				Password *= 10;
				Password += Keynum % 10;
				LCD_ShowNum(2, 1, Password, 4);
			}
			
			// 确认键
			if(Keynum == 11) 
			{
				if(Password == 2589) LCD_ShowString(1, 14, "OK ");
				else LCD_ShowString(1, 14, "ERR");
				
				Password = 0;
				LCD_ShowNum(2, 1, Password, 4);
			}
			
			// 取消键
			if(Keynum == 12)
			{
				Password = 0;
				LCD_ShowNum(2, 1, Password, 4);
			}
		}
	}
}

