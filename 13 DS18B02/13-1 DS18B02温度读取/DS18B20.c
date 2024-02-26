#include <REGF51RC.H>
#include "OneWire.h"

#define DS18B20_SKIP_ROM 		0xCC
#define DS18B20_CONVERT_T 		0x44
#define DS18B20_READ_SCRATCHPAD 0xBE

// �¶�ת��ָ��
void DS18B20_ConvertT()
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

// ��ȡ�¶�ָ��
float DS18B20_ReadT()
{
	unsigned char TLSB, THSB;
	int temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB = OneWire_ReceiveByte(); // �� 0 ���ֽ�
	THSB = OneWire_ReceiveByte(); // �� 1 ���ֽ�
	
	temp = (THSB << 8) | TLSB; // int 16λ
	T = temp / 16.0; // ��Ϊ�� 4 λ��С��
	return T;
}