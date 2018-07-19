#include "fire.h"
#include "delay.h"
#include "sys.h"
#include "beep.h"
#include "usart_TFT.h"	  
#include "usart_wifi.h"	  
#include "usart_printer.h"	
#include "adc.h"
#include "key.h"
#include "stdio.h"

void adc11_main(void)
 {	 
  u16 adcx;
	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart2_init(115200);	 	//���ڳ�ʼ��Ϊ115200	 
 	Adc_Init();		  		//ADC��ʼ��
  BEEP_Init();
  GpuSend("CLS(1);\r\n");		
	 
	while(USART_RX_BUF[5]=='1')
	{
		//printf("%x\r\n",USART_RX_BUF[5]);
		if(fire11==0)
		{
      BEEP=1;
			GpuSend("CLS(1);DS24(100,100,'���ֱ���',4);\r\n" );		
			delay_ms(500);
		}			
		else
		{
			BEEP=0;
			adcx=Get_Adc_Average(ADC_Channel_11,10);
			//printf("��ʾADC��ֵ%d",adcx);
			temp=(float)adcx*(3.3/4096);
			//printf("��ʾ��ѹֵ%.2f",temp);	
			sprintf(buf,"DS24(0,50,'���洫����',4);DS24(0,100,'�����Ӧ��ѹֵ��%.2f V',4);\r\n",temp);
			GpuSend(buf);			
			delay_ms(250);
		}		
	}
 }
 
void adc10_main(void)
{	 
	u16 adcx;
	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart2_init(115200);	 	//���ڳ�ʼ��Ϊ115200	 
	Adc_Init();		  		//ADC��ʼ��
	BEEP_Init();
	GpuSend("CLS(1);\r\n");		
	 
	while(USART_RX_BUF[5]=='2')
	{
		if(fire10==0)
		{
			BEEP=1;
			GpuSend("CLS(1);DS24(100,100,'������',4);\r\n" );		
			delay_ms(500);
		}			
		else
		{
			BEEP=0;
			adcx=Get_Adc_Average(ADC_Channel_10,10);
			//printf("��ʾADC��ֵ%d",adcx);
			temp=(float)adcx*(3.3/4096);
			//printf("��ʾ��ѹֵ%.2f",temp);	
			sprintf(buf,"DS24(0,50,'��������',4);DS24(0,100,'�����Ӧ��ѹֵ��%.2f V',4);\r\n",temp);
			GpuSend(buf);			
			delay_ms(250);
		}		
	}
}

void adc13_main(void)
{	 
	u16 adcx;
	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart2_init(115200);	 	//���ڳ�ʼ��Ϊ115200	 
	Adc_Init();		  		//ADC��ʼ��
	BEEP_Init();
	GpuSend("CLS(1);\r\n");		
	 
	while(USART_RX_BUF[5]=='3')
	{
		if ( fire13 == 0 )
		{
			BEEP = 1;
			GpuSend ( "CLS(1);DS24(100,100,'���峬�걨��',4);\r\n" );		
			delay_ms(500);
		}			
		else
		{
			BEEP = 0;
			adcx = Get_Adc_Average ( ADC_Channel_13,10 );
			//printf ( "��ʾADC��ֵ%d",adcx );
			temp = ( float)adcx*(3.3/4096 );
			//printf ( "��ʾ��ѹֵ%.2f" , temp );	
			sprintf ( buf,"DS24(0,50,'�к����崫����',4);DS24(0,100,'�к������Ӧ��ѹֵ��%.2f V',4);\r\n", temp );
			GpuSend ( buf );			
			delay_ms(250);
		}		
	}
}
 


void human_main(void)
{
	BEEP_Init();
	while(USART_RX_BUF[5]=='4')
	{
		if(human == 1)
		{
      BEEP = 1;
			GpuSend("CLS(3);DS24(100,100,'��ע������',4);\r\n" );		
			delay_ms(500);
		}			
		else
		{
			BEEP = 0;			
			GpuSend ( "CLS(3);DS24(50,100,'������⴫����ʵ��',4);\r\n" );				
			delay_ms(500);
		}		
	}	
}
	 
float  adc12_main(void)
 {	 
  u16 adcx;
	float temp;

 	//Adc_Init();		  		//ADC��ʼ��
		{
	//		BEEP=0;
			adcx=Get_Adc_Average(ADC_Channel_12,180);//40*5 =400ms
			
			temp=(float)adcx*(3.3/4096);

			delay_ms(5);
	
		}		

	return temp;
 } 

