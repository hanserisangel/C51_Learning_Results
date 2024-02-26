#include <REGF51RC.H>

unsigned char Seg_Buf[9]={0,10,10,10,10,10,10,10,10}; // 初始不显示

unsigned char Segment[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
								0x6F,0x00,0x40}; // 0x00 不显示; 0x40 显示横杆

// 控制显示数字
void Seg_SetBuf(unsigned char Location, Number)
{
	Seg_Buf[Location] = Number;
}

/* seg: 多位数码管显示函数
	segsel: 段选信号, [1, 8]
	number: 位选信号, [0, 9]
*/
void Seg_scan(unsigned char segsel, number)
{
	P0 = 0x00; // 清零
	
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
	P0 = Segment[number];
	
	// 消影
	//Delay(1); // 为了数字稳定显示
}

void Seg_Loop() // 驱动函数
{
	static unsigned char i = 1;
	Seg_scan(i, Seg_Buf[i]);
	i ++;
	if(i >= 9) i = 1;
}