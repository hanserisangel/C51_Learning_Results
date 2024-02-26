#include <REGF51RC.H>

void Delay(unsigned char t)
{
	while(t --);
}

int main()
{
	unsigned char time, i;
	while(1)
	{
		for(time = 0; time < 100; time ++)
		{
			for(i = 0; i < 20; i ++)
			{
				P2_0 = 0;
				Delay(time);
				P2_0 = 1;
				Delay(100 - time);
			}
		}
		for(time = 100; time > 0; time --)
		{
			for(i = 0; i < 20; i ++)
			{
				P2_0 = 0;
				Delay(time);
				P2_0 = 1;
				Delay(100 - time);
			}
		}
	}
}