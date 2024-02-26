#include <REGF51RC.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

// 起始条件
void I2C_Start()
{
	// P2 默认就是高电平, 这里置 1 是为了好拼图(构成完整时序)
	I2C_SDA = 1;
	I2C_SCL = 1;
	
	I2C_SDA = 0; // SCL = 1 时, SDA = 1 → 0
	I2C_SCL = 0;
}

// 终止条件
void I2C_Stop()
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	
	I2C_SDA = 1; // SCL = 1 时, SDA = 0 → 1
}

// 发送
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i ++)
	{
		I2C_SDA = Byte & (0x80 >> i); // 高位先行
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}

// 接收
unsigned char I2C_ReceiveByte()
{
	unsigned char i, Byte = 0x00;
	
	I2C_SDA = 1; // 释放总线
	
	for(i = 0; i < 8; i ++)
	{
		I2C_SCL = 1;
		if(I2C_SDA) Byte = Byte | (0x80 >> i); // 高位先行
		I2C_SCL = 0;
	}
	
	return Byte;
}

// 发送应答
void I2C_SendACK(bit ACK)
{
	I2C_SDA = ACK;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

// 接收应答
bit I2C_ReceiveACK()
{
	bit ACK;
	I2C_SDA = 1; // 释放总线
	
	I2C_SCL = 1;
	ACK = I2C_SDA;
	I2C_SCL = 0;
	
	return ACK;
}