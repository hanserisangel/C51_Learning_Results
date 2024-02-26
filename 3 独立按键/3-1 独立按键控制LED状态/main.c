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
	while(1)
	{
		if( P3_1 == 0 )
		{
			// 按键消抖过程
			Delay(20);
			while( P3_1 == 0 );
			Delay(20);
			
			P2_0 = ~P2_0;
		}
	}
}