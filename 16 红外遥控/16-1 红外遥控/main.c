#include <REGF51RC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "IR.h"

unsigned char Num;
unsigned char Address, Command;

int main()
{
	LCD_Init();
	IR_Init();
	
	LCD_ShowString(1, 1, "ADD  Cmd  Num");
	while(1)
	{
		if(IR_GetDataFlag() && IR_GetRepeatFlag())
		{
			Address = IR_GetAddress();
			Command = IR_GetCommand();
			
			LCD_ShowNum(2, 1, Address, 3);
			LCD_ShowNum(2, 6, Command, 3);
			
			if(Command == IR_VOL_MINUS) Num --;
			else if(Command == IR_VOL_ADD) Num ++;
			
			LCD_ShowNum(2, 11, Num, 3);
		}
	}
}
