#include <REGF51RC.H>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

// ʱ��Ĵ���д��ַ
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E

char time[6]; // �� DS1302 ������ BCD�� ʱ������

void DS1302_Init() 
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

/* д��һ���ֽں���
	1��CE = 1
	2����λ����
	3���Ȱ����ݷ���IO����, Ȼ��������д��
	4��CE = 0
*/
void DS1302_WriteByte(unsigned char Command, Data)
{
	unsigned char i;
	DS1302_CE = 1;
	
	// ģ��ʱ��ͼ
	for(i = 0; i < 8; i ++)
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 1; // �����ں������ʱ, ��Ϊ51�����ٶȽ���
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

/* ����һ���ֽ�
	1��CE = 1
	2����λ����
	3���Ȱ����ݷ���IO����, ������д��, �½��ض���
	4��CE = 0
*/
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i, Data = 0x00;
	
	Command |= 0x01; // д��ַ �� ����ַ
	DS1302_CE = 1;
	
	// ģ��ʱ��ͼ
	for(i = 0; i < 8; i ++)
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	
	for(i = 0; i < 8; i ++)
	{
		DS1302_SCLK = 1; // �ر�ע��
		DS1302_SCLK = 0;
		if(DS1302_IO) Data |= (0x01 << i);
	}
	
	DS1302_CE = 0;
	DS1302_IO = 0; // �ؼ�
	return Data;
}

void DS1302_SetTime() // ���ó�ʼʱ��
{
	DS1302_WriteByte(DS1302_WP, 0x00); // �ر�д����
	
	DS1302_WriteByte(DS1302_YEAR,  0x24); // ��
	DS1302_WriteByte(DS1302_MONTH, 0x01); // ��
	DS1302_WriteByte(DS1302_DATE,  0x28); // ��
	DS1302_WriteByte(DS1302_HOUR,  0x10); // ʱ
	DS1302_WriteByte(DS1302_MINUTE,0x30); // ��
	DS1302_WriteByte(DS1302_SECOND,0x00); // ��
}

void DS1302_ReadTime() // ��������ʱ��
{
	time[0] = DS1302_ReadByte(DS1302_YEAR  ); // ��
	time[1] = DS1302_ReadByte(DS1302_MONTH ); // ��
	time[2] = DS1302_ReadByte(DS1302_DATE  ); // ��
	time[3] = DS1302_ReadByte(DS1302_HOUR  ); // ʱ
	time[4] = DS1302_ReadByte(DS1302_MINUTE); // ��
	time[5] = DS1302_ReadByte(DS1302_SECOND); // ��
}
