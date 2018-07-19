#include "extikey.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart_TFT.h"	  
#include "usart_wifi.h"	  
#include "usart_printer.h"	
#include "beep.h"
#include "funmaplist.h"
u8 Ghost = 0;

u8 mUI = 0;
char Key_p =0;
char Key_d =0;
char Key_Wifi = 0;



void EXTIKEYX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource5);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn ;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}


 
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	char tmp = 0;
	delay_ms(10);//����
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)	  //����KEY2   s3
	{
		//funsel = 2;  //��λ����ǰ�λ��
	//	BEEP=!BEEP;
		Key_d =1;
		
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//����
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)	 //����KEY1   s2
	{				 
		Key_p =1;
		//funsel = 4;  //��λ����ǰ�λ��
		LED0=!LED0;
	//	BEEP=!BEEP;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY2==1)	 //����KEY0                       //s4
	{
		Key_Wifi =1;
		//funsel = 1;  //��λ����ǰ�λ��
	//	BEEP=!BEEP;
		LED0=!LED0;
	
	}		 
	EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE4�ϵ��жϱ�־λ  
}
 
