#include <REGF51RC.H>
#include "Key.h"
#include "Seg.h"
#include "Buzzer.h"

unsigned char KeyNum;

int main()
{
	seg(1, 0);
	while(1)
	{
		KeyNum = Key();
		
		if(KeyNum)
		{
			Buzzer_Time(100);
			seg(1, KeyNum);
		}
	}
}