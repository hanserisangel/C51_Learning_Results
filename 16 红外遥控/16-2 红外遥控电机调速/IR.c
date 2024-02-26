#include <REGF51RC.H>
#include "Int0.h"
#include "Timer.h"

unsigned int IR_Time; 
unsigned char IR_State; // 状态机状态

unsigned char IR_Data[4]; // 32位数据
unsigned char IR_pData; // 数组索引指针

unsigned char IR_DataFlag; // 收到数据
unsigned char IR_RepeatFlag; // 收到重复位
unsigned char IR_Address; // 地址
unsigned char IR_Command; // 命令

void IR_Init()
{
	Int0_Init();
	Timer_Init();
}

// 收到数据
unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

// 收到连发帧
unsigned char IR_GetRepeatFlag(void)
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

// 收到地址
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

// 收到命令
unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

// 中断函数, 下降沿触发
void Int0_Routine(void) interrupt 0
{
	if(IR_State == 0) // 状态0, 空闲状态
	{
		Timer_SetCounter(0);	// 从0开始
		Timer_Run(1);			// 开启定时器
		IR_State = 1;			// 状态转移
	}
	else if(IR_State==1) // 状态1, 等待start 或 repeat 信号
	{
		IR_Time = Timer_GetCounter();	//两次下降沿间隔时间
		Timer_SetCounter(0);	//清零
		//计时 13.5ms, Start信号
		if(IR_Time > 12442-500 && IR_Time < 12442+500)
		{
			IR_State=2;			// 状态转移
		}
		//计时 11.25ms, Repeat信号
		else if(IR_Time > 10368-500 && IR_Time < 10368+500)
		{
			IR_RepeatFlag = 1;	
			Timer_Run(0);		
			IR_State = 0;			// 状态转移到 0
		}
		else					    // 接收出错
		{
			IR_State = 1;			
		}
	}
	else if(IR_State==2) // 状态 2, 接收数据
	{
		IR_Time = Timer_GetCounter();
		Timer_SetCounter(0);
		// 计时 1120us, 数据 0
		if(IR_Time > 1032-500 && IR_Time < 1032+500)
		{
			IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));	//对应位清零
			IR_pData ++;			//数据位置指针自增
		}
		// 计时 2250us, 数据 1
		else if(IR_Time > 2074-500 && IR_Time < 2074+500)
		{
			IR_Data[IR_pData/8] |= (0x01<<(IR_pData%8));
			IR_pData ++;			
		}
		else					// 接收出错
		{
			IR_pData = 0;			
			IR_State = 1;			
		}
		
		if(IR_pData >= 32)		// 数据完整
		{
			IR_pData = 0;			
			if((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3])) // 数据检验
			{
				IR_Address = IR_Data[0];	
				IR_Command = IR_Data[2];
				IR_DataFlag = 1;	
			}
			Timer_Run(0);		
			IR_State = 0;			
		}
	}
}