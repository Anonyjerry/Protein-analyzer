#ifndef __KEY06_H
#define __KEY06_H	 
#include "sys.h" 	 
#define RFKEY_VT  GPIO_Pin_4
#define RFKEY_D0  GPIO_Pin_3
#define RFKEY_D1  GPIO_Pin_2
#define RFKEY_D2  GPIO_Pin_1
#define RFKEY_D3  GPIO_Pin_0
#define RFKEY     GPIOD

#define KEY_VT  GPIO_ReadInputDataBit(RFKEY,RFKEY_VT)//��ȡ����0
#define KEY_D0  GPIO_ReadInputDataBit(RFKEY,RFKEY_D0)//��ȡ����0
#define KEY_D1  GPIO_ReadInputDataBit(RFKEY,RFKEY_D1)//��ȡ����0
#define KEY_D2  GPIO_ReadInputDataBit(RFKEY,RFKEY_D2)//��ȡ����0
#define KEY_D3  GPIO_ReadInputDataBit(RFKEY,RFKEY_D3)//��ȡ����0

#define high 1
#define low  0

#define KEY_D3_PRES 1
#define KEY_D2_PRES 2
#define KEY_D1_PRES 3
#define KEY_D0_PRES 4


void KEY06_Init(void);//IO��ʼ��
u8 KEY06_Scan(u8 mode);// ����ɨ��
void Key06_Main(void);
				    
#endif
