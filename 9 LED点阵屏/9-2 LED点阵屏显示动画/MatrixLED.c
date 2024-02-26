#include <REGF51RC.H>
#include "Delay.h"

sbit RCLK = P3^5;
sbit SRCLK = P3^6;
sbit SER = P3^4;

void MatrixLED_Init()
{
	// ��Ϊ��������λ, �����ϵ�� �͵�ƽ
	SRCLK = 0;
	RCLK = 0;
}

void WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i ++) // ȡ�� Byte ��ÿһλ
	{
		SER = Byte & (0x80 >> i);
		
		// ��������λ
		SRCLK = 1;
		SRCLK = 0;
	}
	
	// ����������
	RCLK = 1;
	RCLK = 0;
}

/* 1 ����ʾ����
	Col ��, [0, 7]
	Data ��ѡ�ź�
*/
void ShowMatrixLED(unsigned char Col, Data)
{
	WriteByte(Data); // ��ѡ
	P0 = ~(0x80 >> Col); // λѡ
	
	// ��Ӱ
	Delay(1);
	P0 = 0xff; // λѡ����
}