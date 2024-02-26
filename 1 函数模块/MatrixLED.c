#include <REGF51RC.H>
#include "Delay.h"

sbit RCLK = P3^5;
sbit SRCLK = P3^6;
sbit SER = P3^4;

void MatrixLED_Init()
{
	// 因为上升沿移位, 所以上电后 低电平
	SRCLK = 0;
	RCLK = 0;
}

void WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i ++) // 取出 Byte 的每一位
	{
		SER = Byte & (0x80 >> i);
		
		// 上升沿移位
		SRCLK = 1;
		SRCLK = 0;
	}
	
	// 上升沿锁存
	RCLK = 1;
	RCLK = 0;
}

/* 1 列显示函数
	Col 列, [0, 7]
	Data 段选信号
*/
void ShowMatrixLED(unsigned char Col, Data)
{
	WriteByte(Data); // 段选
	P0 = ~(0x80 >> Col); // 位选
	
	// 消影
	Delay(1);
	P0 = 0xff; // 位选清零
}