#include <REGF51RC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

unsigned int ADValue;

int main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "ADJ  NTC  RG"); // ��λ��  ��������  ��������
	while(1)
	{
		ADValue = XPT2046_ReadAD(XPT2046_XP);
		LCD_ShowNum(2, 1, ADValue, 4);
		ADValue = XPT2046_ReadAD(XPT2046_YP);
		LCD_ShowNum(2, 6, ADValue, 4);
		ADValue = XPT2046_ReadAD(XPT2046_VBAT);
		LCD_ShowNum(2, 11, ADValue, 4);
		Delay(10);
	}
}