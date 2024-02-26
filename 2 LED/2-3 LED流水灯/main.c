#include <REGF51RC.H>

void Delayms(unsigned int n)		//@11.0592MHz
{
	unsigned char i, j;

	while(n --)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

int main()
{
	unsigned char temp; // P2 �����
	unsigned int i;
	while(1)
	{
		temp = 0x01; // ÿ����ˮ�ƶ����� temp Ϊ��׼
		for(i = 0; i < 8; i ++)
		{
			P2 = ~(temp << i);
			Delayms(500);
		}
	}
}