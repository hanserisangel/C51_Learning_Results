#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

bit OneWire_Init();
void OneWire_SendBit(bit Bit);
bit OneWire_ReceiveBit();
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReceiveByte();

#endif