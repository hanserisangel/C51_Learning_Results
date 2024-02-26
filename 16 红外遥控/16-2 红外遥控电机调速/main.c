#include <REGF51RC.H>
#include "Delay.h"
#include "Motor.h"
#include "Seg.h"
#include "IR.h"

unsigned char Command, SpeedMode;

int main()
{
	Moter_Init();
	IR_Init();
	
	while(1)
	{
		if(IR_GetDataFlag())
		{
			Command = IR_GetCommand();
			
			if(Command == IR_0) SpeedMode = 0;
			if(Command == IR_1) SpeedMode = 1;
			if(Command == IR_2) SpeedMode = 2;
			if(Command == IR_3) SpeedMode = 3;
			if(Command == IR_4) SpeedMode = 4;
			
			if(SpeedMode == 0) Motor_SetSpeed(0);
			if(SpeedMode == 1) Motor_SetSpeed(25);
			if(SpeedMode == 2) Motor_SetSpeed(50);
			if(SpeedMode == 3) Motor_SetSpeed(75);
			if(SpeedMode == 4) Motor_SetSpeed(100);
		}
		
		seg(1, SpeedMode);
	}
}
