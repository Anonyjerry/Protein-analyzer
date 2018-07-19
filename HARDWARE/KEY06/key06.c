#include "stm32f10x.h"
#include "key06.h"
#include "sys.h" 
#include "beep.h"
#include "delay.h"
#include "usart_TFT.h"	  
#include "usart_wifi.h"	  
#include "usart_printer.h"	
								    
//������ʼ������
void KEY06_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = RFKEY_VT|RFKEY_D0|RFKEY_D1|RFKEY_D2|RFKEY_D3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������
 	GPIO_Init(RFKEY, &GPIO_InitStructure);//��ʼ��IO
	
}
/**********************************************************
������		��u8 KEY_Scan(u8 mode)
��������	��ɨ�谴���Ƿ���
����			��0��1   0 ֧������   1  ��֧������
���			��������Ӧֵ 1-4
**********************************************************/


u8 KEY06_Scan(u8 mode)
{	 
	static u8 key_up = 1;//�������ɿ���־
	if(KEY_VT==high)
	{
		if(mode)key_up = 1;  //֧������		  
		if(key_up&&(KEY_D3 == high || KEY_D2 == high || KEY_D1 == high || KEY_D0 == high))
		{
			delay_ms(10);//ȥ���� 
			key_up = 0;
			if(KEY_D3 == high) return KEY_D3_PRES;
			if(KEY_D2 == high) return KEY_D2_PRES;
			if(KEY_D1 == high) return KEY_D1_PRES;
			if(KEY_D0 == high) return KEY_D0_PRES;
		}else if(KEY_D3 == low && KEY_D2 == low && KEY_D1 == low && KEY_D0 == low)key_up=1; 	 
	}	
 	return 0;// �ް�������
}

void Key06_Main(void)
{
	u8 buffer=0;        //�洢����ɨ��ֵ
	 
	KEY06_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	BEEP_Init();
	uart2_init( 115200 );  //������������ 115200
	uart_init( 115200 );  //������������ 115200
	delay_ms( 1000 );      //��ʱ�ȴ���Ļ
  GpuSend("CLS(1);\r\n");
	GpuSend("DS24(70,50,'��������Ƶʵ��',4);\r\n");
	
	while(USART_RX_BUF[5]=='6')
	{
		buffer = KEY06_Scan(0);//��¼����ɨ��ֵ0��1��2��3��4��
		if(buffer != 0)
		{ 
			switch(buffer)
			{
				case 0x01:
				{
					GpuSend("DS24(100,120,'��ֵ��B ',4);\r\n");
				  break;
				}
				case 2:
				{
					GpuSend("DS24(100,120,'��ֵ��D ',4);\r\n");
				  break;
				}
				case 3:
				{
					GpuSend("DS24(100,120,'��ֵ��A ',4);\r\n");
				  break;
				}
				case 4:
				{
					GpuSend("DS24(100,120,'��ֵ��C ',4);\r\n");
				  break;
				}
				default:break;
			}
			delay_ms(100);
		}
	}	 	
}



