#include <REGF51RC.H>

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

int main()
{
	while(1)
	{
		// D1 …¡À∏
		P2 = 0xfe;
		Delay500ms(); // ¡¡ 0.5 s
		
		P2 = 0xff;
		Delay500ms(); // √ 0.5 s
	}
}