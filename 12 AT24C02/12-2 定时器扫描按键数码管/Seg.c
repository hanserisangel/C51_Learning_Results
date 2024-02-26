#include <REGF51RC.H>

unsigned char Seg_Buf[9]={0,10,10,10,10,10,10,10,10}; // ��ʼ����ʾ

unsigned char Segment[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
								0x6F,0x00,0x40}; // 0x00 ����ʾ; 0x40 ��ʾ���

// ������ʾ����
void Seg_SetBuf(unsigned char Location, Number)
{
	Seg_Buf[Location] = Number;
}

/* seg: ��λ�������ʾ����
	segsel: ��ѡ�ź�, [1, 8]
	number: λѡ�ź�, [0, 9]
*/
void Seg_scan(unsigned char segsel, number)
{
	P0 = 0x00; // ����
	
	// λѡ�ź� segsel( ͨ������ P2 �Ĵ���ʵ��)
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
	
	// ��ѡ�ź� segment(ͨ������ P0 �Ĵ���ʵ��)
	P0 = Segment[number];
	
	// ��Ӱ
	//Delay(1); // Ϊ�������ȶ���ʾ
}

void Seg_Loop() // ��������
{
	static unsigned char i = 1;
	Seg_scan(i, Seg_Buf[i]);
	i ++;
	if(i >= 9) i = 1;
}