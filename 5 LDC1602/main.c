#include <REGF51RC.H>
#include "LCD1602.H"

int main()
{
	LCD_Init();
	LCD_ShowString(2,1,"hanser");
	LCD_ShowNum(2,8,520,3);
	while(1)
	{
		
	}
}