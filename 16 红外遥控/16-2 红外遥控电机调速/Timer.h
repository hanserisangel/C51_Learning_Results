#ifndef __Timer_H__
#define __Timer_H__

void Timer_Init();
void Timer_SetCounter(unsigned int Value);
unsigned int Timer_GetCounter(void);
void Timer_Run(unsigned char Flag);

#endif
