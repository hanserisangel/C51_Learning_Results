#include <REGF51RC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char Keynum;

int main()
{
	LCD_Init(); // LCD1602 ��ʼ��
	while(1)
	{
		// ��ͣ�ػ�ȡ����
		Keynum = MatrixKey();
		
		if(Keynum) LCD_ShowNum(1, 1, Keynum, 2);
	}
}