#include <REGF51RC.H>

unsigned char segment[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
								0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};

/* seg: 1 位数码管显示函数
	segsel: 段选信号, [1, 8]
	number: 位选信号, [0, 9]
*/
void seg(unsigned char segsel, number)
{
	// 位选信号 segsel( 通过控制 P2 寄存器实现)
	switch(segsel)
	{
		case 1: P2_4 = 1, P2_3 = 1, P2_2 = 1; break;
		case 2: P2_4 = 1, P2_3 = 1, P2_2 = 0; break;
		case 3: P2_4 = 1, P2_3 = 0, P2_2 = 1; break;
		case 4: P2_4 = 1, P2_3 = 0, P2_2 = 0; break;
		case 5: P2_4 = 0, P2_3 = 1, P2_2 = 1; break;
		case 6: P2_4 = 0, P2_3 = 1, P2_2 = 0; break;
		case 7: P2_4 = 0, P2_3 = 0, P2_2 = 1; break;
		case 8: P2_4 = 0, P2_3 = 0, P2_2 = 0; break;
	}
	
	// 段选信号 segment(通过控制 P0 寄存器实现)
	P0 = segment[number];
}

int main()
{
	seg(1, 3); // 第 1 位显示数字 3
	
	while(1)
	{
		
	}
}