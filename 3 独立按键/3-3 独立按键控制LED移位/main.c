#include <REGF51RC.H>

void Delay(unsigned int n)		//@11.0592MHz
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
	unsigned char ch = 0x01;
	while(1)
	{
		if( P3_1 == 0 )
		{
			// 按键消抖过程
			Delay(20);
			while( P3_1 == 0 );
			Delay(20);
			
			// 0000_0001 → ... → 1000_0000 → 0000_0000(0000_0001)
			ch = ch << 1;
			if( ch == 0 ) ch = 0x01;
			P2 = ~ch;
		}
	}
}