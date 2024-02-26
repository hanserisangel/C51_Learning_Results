#include <REGF51RC.H>

sbit OneWire_DQ = P3^7;

void Delay480us()		//@11.0592MHz
{
	unsigned char i;

	i = 218;
	while (--i);
}

void Delay70us()		//@11.0592MHz
{
	unsigned char i;

	i = 29;
	while (--i);
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void Delay50us()		//@11.0592MHz
{
	unsigned char i;

	i = 20;
	while (--i);
}

void Delay5us()		//@11.0592MHz
{
}

// 初始化
bit OneWire_Init()
{
	bit ACK;
	EA = 0; // *关闭定时器中断
	OneWire_DQ = 1;
	OneWire_DQ = 0; // 主机发送
	Delay480us();
	
	OneWire_DQ = 1; // 释放总线
	
	Delay70us();
	ACK = OneWire_DQ; // 从机应答
	
	Delay480us(); // 保证时间片长度在手册规定范围内
	
	EA = 1;
	
	return ACK;
}

// 发送 1 位
void OneWire_SendBit(bit Bit)
{
	EA = 0;
	OneWire_DQ = 1;
	OneWire_DQ = 0; // 主机发送
	Delay10us();
	OneWire_DQ = Bit;
	Delay50us(); // 保证时间片长度在手册规定范围内
	
	OneWire_DQ = 1; // 释放总线
	EA = 1;
}

// 接收 1 位
bit OneWire_ReceiveBit()
{
	bit Bit;
	EA = 0;
	OneWire_DQ = 1;
	OneWire_DQ = 0; // 主机发送
	Delay5us();
	OneWire_DQ = 1;
	Delay5us();
	
	Bit = OneWire_DQ;
	Delay50us(); // 保证时间片长度在手册规定范围内
	EA = 1;
	return Bit;
}

// 发送 1 个字节
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i ++)
	{
		OneWire_SendBit(Byte & (0x01<<i));
	}
}

// 接收 1 个字节
unsigned char OneWire_ReceiveByte()
{
	unsigned char i;
	unsigned char Byte = 0x00;
	for(i = 0; i < 8; i ++)
	{
		if(OneWire_ReceiveBit()) Byte |= (0x01 << i);
	}
	return Byte;
}