#include <REGF51RC.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

// ��ʼ����
void I2C_Start()
{
	// P2 Ĭ�Ͼ��Ǹߵ�ƽ, ������ 1 ��Ϊ�˺�ƴͼ(��������ʱ��)
	I2C_SDA = 1;
	I2C_SCL = 1;
	
	I2C_SDA = 0; // SCL = 1 ʱ, SDA = 1 �� 0
	I2C_SCL = 0;
}

// ��ֹ����
void I2C_Stop()
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	
	I2C_SDA = 1; // SCL = 1 ʱ, SDA = 0 �� 1
}

// ����
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i ++)
	{
		I2C_SDA = Byte & (0x80 >> i); // ��λ����
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}

// ����
unsigned char I2C_ReceiveByte()
{
	unsigned char i, Byte = 0x00;
	
	I2C_SDA = 1; // �ͷ�����
	
	for(i = 0; i < 8; i ++)
	{
		I2C_SCL = 1;
		if(I2C_SDA) Byte = Byte | (0x80 >> i); // ��λ����
		I2C_SCL = 0;
	}
	
	return Byte;
}

// ����Ӧ��
void I2C_SendACK(bit ACK)
{
	I2C_SDA = ACK;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

// ����Ӧ��
bit I2C_ReceiveACK()
{
	bit ACK;
	I2C_SDA = 1; // �ͷ�����
	
	I2C_SCL = 1;
	ACK = I2C_SDA;
	I2C_SCL = 0;
	
	return ACK;
}