#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
	 

#define KEY0 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����0
#define KEY1 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ����1
#define KEY2 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)//��ȡ����2 
#define fire11  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//���汨��
#define fire10  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//������
#define fire13  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//�к����屨��
#define human   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)//������⴫����


 

#define KEY0_PRES 1	//KEY0����
#define KEY1_PRES	2	//KEY1����
#define KEY2_PRES	3	//KEY2����



void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
