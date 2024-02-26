#include <REGF51RC.H>

unsigned char Key_number;

unsigned char Key() // ���ش�����İ���ֵ
{
	unsigned char temp;
	
	temp = Key_number;
	Key_number = 0; // ����
	
	return temp;
}

// ÿ 20ms ��� P3״̬
unsigned char Key_GetState()
{
	unsigned char Keynum = 0;
	
	if(P3_1 == 0) Keynum = 1;
	if(P3_0 == 0) Keynum = 2;
	if(P3_2 == 0) Keynum = 3;
	if(P3_3 == 0) Keynum = 4;
	
	return Keynum;
}

void Key_Loop()
{
	static unsigned char NowState, LastState; // ��̬, ��һ��״̬; Ϊ�˼��������
	LastState = NowState;
	NowState = Key_GetState();
	
	if(LastState == 1 && NowState == 0)	Key_number = 1;
	if(LastState == 2 && NowState == 0)	Key_number = 2;
	if(LastState == 3 && NowState == 0)	Key_number = 3;
	if(LastState == 4 && NowState == 0)	Key_number = 4;
}
