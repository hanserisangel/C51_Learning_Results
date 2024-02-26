#include <REGF51RC.H>
#include "I2C.h"

#define AT24C02_Address 0xA0

// 发送一帧
void AT24C02_WriteByte(unsigned char WordAddress, Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02_Address);
	I2C_ReceiveACK();
	I2C_SendByte(WordAddress);
	I2C_ReceiveACK();
	I2C_SendByte(Data);
	I2C_ReceiveACK();
	I2C_Stop();
}

// 接收一帧
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	
	I2C_Start();
	I2C_SendByte(AT24C02_Address);
	I2C_ReceiveACK();
	I2C_SendByte(WordAddress);
	I2C_ReceiveACK();
	
	I2C_Start();
	I2C_SendByte(AT24C02_Address | 0x01);
	I2C_ReceiveACK();
	Data = I2C_ReceiveByte();
	I2C_SendACK(1);
	I2C_Stop();
	
	return Data;
}