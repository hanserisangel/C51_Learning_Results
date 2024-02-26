#include <REGF51RC.H>
#include "Int0.h"
#include "Timer.h"

unsigned int IR_Time; 
unsigned char IR_State; // ״̬��״̬

unsigned char IR_Data[4]; // 32λ����
unsigned char IR_pData; // ��������ָ��

unsigned char IR_DataFlag; // �յ�����
unsigned char IR_RepeatFlag; // �յ��ظ�λ
unsigned char IR_Address; // ��ַ
unsigned char IR_Command; // ����

void IR_Init()
{
	Int0_Init();
	Timer_Init();
}

// �յ�����
unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

// �յ�����֡
unsigned char IR_GetRepeatFlag(void)
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

// �յ���ַ
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

// �յ�����
unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

// �жϺ���, �½��ش���
void Int0_Routine(void) interrupt 0
{
	if(IR_State == 0) // ״̬0, ����״̬
	{
		Timer_SetCounter(0);	// ��0��ʼ
		Timer_Run(1);			// ������ʱ��
		IR_State = 1;			// ״̬ת��
	}
	else if(IR_State==1) // ״̬1, �ȴ�start �� repeat �ź�
	{
		IR_Time = Timer_GetCounter();	//�����½��ؼ��ʱ��
		Timer_SetCounter(0);	//����
		//��ʱ 13.5ms, Start�ź�
		if(IR_Time > 12442-500 && IR_Time < 12442+500)
		{
			IR_State=2;			// ״̬ת��
		}
		//��ʱ 11.25ms, Repeat�ź�
		else if(IR_Time > 10368-500 && IR_Time < 10368+500)
		{
			IR_RepeatFlag = 1;	
			Timer_Run(0);		
			IR_State = 0;			// ״̬ת�Ƶ� 0
		}
		else					    // ���ճ���
		{
			IR_State = 1;			
		}
	}
	else if(IR_State==2) // ״̬ 2, ��������
	{
		IR_Time = Timer_GetCounter();
		Timer_SetCounter(0);
		// ��ʱ 1120us, ���� 0
		if(IR_Time > 1032-500 && IR_Time < 1032+500)
		{
			IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));	//��Ӧλ����
			IR_pData ++;			//����λ��ָ������
		}
		// ��ʱ 2250us, ���� 1
		else if(IR_Time > 2074-500 && IR_Time < 2074+500)
		{
			IR_Data[IR_pData/8] |= (0x01<<(IR_pData%8));
			IR_pData ++;			
		}
		else					// ���ճ���
		{
			IR_pData = 0;			
			IR_State = 1;			
		}
		
		if(IR_pData >= 32)		// ��������
		{
			IR_pData = 0;			
			if((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3])) // ���ݼ���
			{
				IR_Address = IR_Data[0];	
				IR_Command = IR_Data[2];
				IR_DataFlag = 1;	
			}
			Timer_Run(0);		
			IR_State = 0;			
		}
	}
}