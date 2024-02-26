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

// ��ʼ��
bit OneWire_Init()
{
	bit ACK;
	EA = 0; // *�رն�ʱ���ж�
	OneWire_DQ = 1;
	OneWire_DQ = 0; // ��������
	Delay480us();
	
	OneWire_DQ = 1; // �ͷ�����
	
	Delay70us();
	ACK = OneWire_DQ; // �ӻ�Ӧ��
	
	Delay480us(); // ��֤ʱ��Ƭ�������ֲ�涨��Χ��
	
	EA = 1;
	
	return ACK;
}

// ���� 1 λ
void OneWire_SendBit(bit Bit)
{
	EA = 0;
	OneWire_DQ = 1;
	OneWire_DQ = 0; // ��������
	Delay10us();
	OneWire_DQ = Bit;
	Delay50us(); // ��֤ʱ��Ƭ�������ֲ�涨��Χ��
	
	OneWire_DQ = 1; // �ͷ�����
	EA = 1;
}

// ���� 1 λ
bit OneWire_ReceiveBit()
{
	bit Bit;
	EA = 0;
	OneWire_DQ = 1;
	OneWire_DQ = 0; // ��������
	Delay5us();
	OneWire_DQ = 1;
	Delay5us();
	
	Bit = OneWire_DQ;
	Delay50us(); // ��֤ʱ��Ƭ�������ֲ�涨��Χ��
	EA = 1;
	return Bit;
}

// ���� 1 ���ֽ�
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i ++)
	{
		OneWire_SendBit(Byte & (0x01<<i));
	}
}

// ���� 1 ���ֽ�
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