#include <REGF51RC.H>
#include "OneWire.h"

#define DS18B20_SKIP_ROM 		0xCC
#define DS18B20_CONVERT_T 		0x44
#define DS18B20_READ_SCRATCHPAD 0xBE

// 温度转换指令
void DS18B20_ConvertT()
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

// 读取温度指令
float DS18B20_ReadT()
{
	unsigned char TLSB, THSB;
	int temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB = OneWire_ReceiveByte(); // 第 0 个字节
	THSB = OneWire_ReceiveByte(); // 第 1 个字节
	
	temp = (THSB << 8) | TLSB; // int 16位
	T = temp / 16.0; // 因为低 4 位是小数
	return T;
}