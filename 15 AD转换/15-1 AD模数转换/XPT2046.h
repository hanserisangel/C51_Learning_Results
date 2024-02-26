#ifndef __XPT2046_H__
#define __XPT2046_H__

// 12Î»·Ö±æÂÊ
#define XPT2046_XP 0x94
#define XPT2046_YP 0xD4
#define XPT2046_VBAT 0xA4
#define XPT2046_AUX 0xE4

unsigned int XPT2046_ReadAD(unsigned char Command);

#endif