#include <REGF51RC.H>
#include "Delay.h"

unsigned char MatrixKey()
{
	unsigned char Keynum = 0;
	
	// �� 1 ��
	P1 = 0xFF;
	P1_3 = 0;
	if(P1_7 == 0) {Delay(20); while(P1_7 == 0); Delay(20); Keynum = 1;}
	if(P1_6 == 0) {Delay(20); while(P1_6 == 0); Delay(20); Keynum = 5;}
	if(P1_5 == 0) {Delay(20); while(P1_5 == 0); Delay(20); Keynum = 9;}
	if(P1_4 == 0) {Delay(20); while(P1_4 == 0); Delay(20); Keynum = 13;}
	
	// �� 2 ��
	P1 = 0xFF;
	P1_2 = 0;
	if(P1_7 == 0) {Delay(20); while(P1_7 == 0); Delay(20); Keynum = 2;}
	if(P1_6 == 0) {Delay(20); while(P1_6 == 0); Delay(20); Keynum = 6;}
	if(P1_5 == 0) {Delay(20); while(P1_5 == 0); Delay(20); Keynum = 10;}
	if(P1_4 == 0) {Delay(20); while(P1_4 == 0); Delay(20); Keynum = 14;}
	
	// �� 3 ��
	P1 = 0xFF;
	P1_1 = 0;
	if(P1_7 == 0) {Delay(20); while(P1_7 == 0); Delay(20); Keynum = 3;}
	if(P1_6 == 0) {Delay(20); while(P1_6 == 0); Delay(20); Keynum = 7;}
	if(P1_5 == 0) {Delay(20); while(P1_5 == 0); Delay(20); Keynum = 11;}
	if(P1_4 == 0) {Delay(20); while(P1_4 == 0); Delay(20); Keynum = 15;}
	
	// �� 4 ��
	P1 = 0xFF;
	P1_0 = 0;
	if(P1_7 == 0) {Delay(20); while(P1_7 == 0); Delay(20); Keynum = 4;}
	if(P1_6 == 0) {Delay(20); while(P1_6 == 0); Delay(20); Keynum = 8;}
	if(P1_5 == 0) {Delay(20); while(P1_5 == 0); Delay(20); Keynum = 12;}
	if(P1_4 == 0) {Delay(20); while(P1_4 == 0); Delay(20); Keynum = 16;}
	
	return Keynum;
}

