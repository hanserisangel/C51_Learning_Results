#include <REGF51RC.H>

void Int0_Init()
{
	IT0 = 1; // �½���
	IE0 = 0;
	EX0 = 1;
	EA = 1;
	PX0 = 1; // �����ȼ��ж�
}

/* �ⲿ�жϺ���
void hanser() interrupt 0
{

}
*/