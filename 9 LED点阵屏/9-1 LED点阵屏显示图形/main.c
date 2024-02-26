#include <REGF51RC.H>
#include "MatrixLED.h"

int main()
{
	MatrixLED_Init();
	while(1)
	{
		ShowMatrixLED(0, 0x3C);
		ShowMatrixLED(1, 0x42);
		ShowMatrixLED(2, 0xA9);
		ShowMatrixLED(3, 0x85);
		ShowMatrixLED(4, 0x85);
		ShowMatrixLED(5, 0xA9);
		ShowMatrixLED(6, 0x42);
		ShowMatrixLED(7, 0x3C);
	}
}

