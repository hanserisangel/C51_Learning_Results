#include <REGF51RC.H>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

// 时间寄存器写地址
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E

char time[] = {24, 1, 28, 14, 0, 0}; // 从 DS1302 读出的 BCD码 时间数据

void DS1302_Init() 
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

/* 写入一个字节函数
	1、CE = 1
	2、低位先行
	3、先把数据放在IO线上, 然后上升沿写入
	4、CE = 0
*/
void DS1302_WriteByte(unsigned char Command, Data)
{
	unsigned char i;
	DS1302_CE = 1;
	
	// 模拟时序图
	for(i = 0; i < 8; i ++)
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 1; // 不用在后面加延时, 因为51运行速度较慢
		DS1302_SCLK = 0;
	}
	
	for(i = 0; i < 8; i ++)
	{
		DS1302_IO = Data & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	DS1302_CE = 0;
}

/* 读出一个字节
	1、CE = 1
	2、低位先行
	3、先把数据放在IO线上, 上升沿写入, 下降沿读出
	4、CE = 0
*/
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i, Data = 0x00;
	
	Command |= 0x01; // 写地址 → 读地址
	DS1302_CE = 1;
	
	// 模拟时序图
	for(i = 0; i < 8; i ++)
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	
	for(i = 0; i < 8; i ++)
	{
		DS1302_SCLK = 1; // 特别注意
		DS1302_SCLK = 0;
		if(DS1302_IO) Data |= (0x01 << i);
	}
	
	DS1302_CE = 0;
	DS1302_IO = 0; // 关键
	return Data;
}

void DS1302_SetTime() // 设置初始时间
{
	DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护
	
	DS1302_WriteByte(DS1302_YEAR,  time[0]/10 * 16 + time[0]%10); // 年
	DS1302_WriteByte(DS1302_MONTH, time[1]/10 * 16 + time[1]%10); // 月
	DS1302_WriteByte(DS1302_DATE,  time[2]/10 * 16 + time[2]%10); // 日
	DS1302_WriteByte(DS1302_HOUR,  time[3]/10 * 16 + time[3]%10); // 时
	DS1302_WriteByte(DS1302_MINUTE,time[4]/10 * 16 + time[4]%10); // 分
	DS1302_WriteByte(DS1302_SECOND,time[5]/10 * 16 + time[5]%10); // 秒
	
	DS1302_WriteByte(DS1302_WP,0x80); // 开启写保护
}

void DS1302_ReadTime() // 读出完整时间
{
	unsigned char Temp;
	Temp = DS1302_ReadByte(DS1302_YEAR);
	time[0] = Temp/16 * 10 + Temp%16;
	Temp = DS1302_ReadByte(DS1302_MONTH);
	time[1] = Temp/16 * 10 + Temp%16;
	Temp=DS1302_ReadByte(DS1302_DATE);
	time[2] = Temp/16 * 10 + Temp%16;
	Temp = DS1302_ReadByte(DS1302_HOUR);
	time[3] = Temp/16 * 10 + Temp%16;
	Temp = DS1302_ReadByte(DS1302_MINUTE);
	time[4] = Temp/16 * 10 + Temp%16;
	Temp = DS1302_ReadByte(DS1302_SECOND);
	time[5] = Temp/16 * 10 + Temp%16;
}