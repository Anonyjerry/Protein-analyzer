#include "delay.h"
#include "sys.h"
#include "led.h"
#include "beep.h"
#include "usart_TFT.h"	  
#include "usart_wifi.h"	  
#include "usart_printer.h"	
#include "key.h"
#include "key06.h"
#include "fire.h"
#include "dht11.h"
#include "extikey.h"
#include "remote.h"
#include "rc522_function.h"
#include "rc522_config.h" 
#include "string.h"
#include "funmaplist.h"
#include "ui.h"
#include "mTimer.h"
#include "wifi_function.h"
#include "wifi_config.h"
#include "ic_card.h"
#include "flash_WR.h"
#include "adc.h"
#include <stdio.h>
#include <stdlib.h>
#include "MessageSendandReceive.h"

//ui
void Rc522_Main(void);
void TouchPanel();

//��ӡ����ӡ
void Printer(char *string,float AD,char data[] )
{
	char *str = "  ";
	 if (AD<value_min)  str = "��";
	 if (AD>value_max)  str = "��";
	 
//		Usart_SendString( USART3,string);
	
		delay_ms(50);
		UART3Write((u8*)"\x1b\x4a\x30",sizeof("\x1b\x4a\x30")) ; 	
	
		sprintf(buf,"      ������C�������");
		Usart_SendString( USART3,buf);
	
		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 
		sprintf(buf,"���ڣ�2018��06��%02d��  %02d:%02d:%02d ", gDate [ 2 ], gDate [ 3 ],gDate [ 4 ], gDate [ 5 ]);
		Usart_SendString( USART3,buf);
		delay_ms(10);
	
		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 
		sprintf(buf,"�����ǿ�ID��%02X%02X%02X%02X ",data [ 0 ], data [ 1 ], data [ 2 ], data [ 3 ]);
		Usart_SendString( USART3,buf);
		delay_ms(10);
			
		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 	
		sprintf(buf,"�����    ������Χ     ״̬");
		Usart_SendString( USART3,buf);
		delay_ms(10);

		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 	
		sprintf(buf,"  %.3F     %.1f--%.1f      %s ",AD,value_min,value_max,str);
//		delay_ms(50);
		Usart_SendString( USART3,buf);
//	delay_ms(50);
		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 	

		//�ƶ�������
		UART3Write((u8*)"\x1b\x4a\x60",sizeof("\x1b\x4a\x60")) ; 	
		UART3Write((u8*)"\x1b\x69",sizeof("\x1b\x69")) ; 	
}

void ( * pNet_Test ) ( void );

 int main(void)
 {	 
		char cCh;	
	
		delay_init();	    	 //��ʱ������ʼ��	  
	 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 	 TIM2_Configuration();
		TIM2_NVIC_Configuration();
		EXTIKEYX_Init();
	 uart_init(115200);	     //wifi
		uart_printer_init(9600);  //9600
		uart2_init(115200);	      //tft
		
	 	Adc_Init();		  		//ADC��ʼ��
		funMod =0;
	  init_infor();
	 
	 
		KEY_Init();
		LED_Init();
		BEEP_Init();

	 delay_ms(1000);

//	 
//	 while(1)
//	 {struct STRUCT_USARTx msg;
//		 memcpy(msg.Data_RX_BUF,"rtj;uhtr;yf",sizeof("rtj;uhtr;yf"));
//		 Message_que_receive(msg);
//	 }
	 
	 
	 
	 
	 
	
//{
//	uint8_t d_Data[5] = {0,20,30,50};
//	uint8_t dt[] = "1234567890";
//	uint8_t Temp_Data[] ="" ; 
//unsigned char * Te ; 	
//	int i =0;
//	int n =0;
//    unsigned char Temp = 0; 
//int ReadNum = 0;

// 	//	WriteFlashData(10,dt,sizeof(dt)); //д��ָ����ַ�ַ���    
//    delay_ms(10);                           
////    ReadNum =ReadFlashNBtye (10, Temp_Data,sizeof(dt)*2); 
////    Temp = (unsigned char)ReadNum;  
////	
////	for(i=0;i<sizeof(dt)*2;i++)
////	{
////		Te[n++]=Temp_Data[i++];
////	}
//	 flashReadStr(10,Temp_Data,sizeof(dt));
//		sprintf(buf,"DS16(0,150,'����ͨ��д���ַ���%s',4);\r\n",Temp_Data );
//		GpuSend(buf); 
//}

	  
#if WiFi_debug

// WiFi Module - ESP8266

		PC_Usart("\r\n WIFI-ESP8266 WiFiģ��\r\n");                            //��ӡ����������ʾ��Ϣ

  PC_Usart ( "\r\n������ģ��Ĳ���ģʽ�ı�ţ�������£�\
              \r\n1.STAģʽ�� TCP Client\
              \r\n2.APģʽ�� AP Server\
              \r\n3.STA+APģʽ�� (STA)TCP Client + (AP)TCP Server\
              \r\n�����ʽΪ�����+�ո񣬵������\r\n" );
	
//  scanf ( "%c",  & cCh );
cCh = '2';
  switch ( cCh )
  {
		case '1':
			pNet_Test = ESP8266_STA_TCP_Client;
		  PC_Usart("\r\n�������еĲ����ǣ�1.STAģʽ�� TCP Client\r\n");
		  break;
		
		case '2':
			pNet_Test = ESP8266_AP_TCP_Server;
		  PC_Usart("\r\n�������еĲ����ǣ�2.APģʽ�� TCP Server\r\n");
		  break;

		case '3':
			pNet_Test = ESP8266_StaTcpClient_ApTcpServer;
		  PC_Usart("\r\n�������еĲ����ǣ�3.STA+APģʽ�� (STA)TCP Client + (AP)TCP Server\r\n");
		  break;

		default:
			pNet_Test = NULL;
		  PC_Usart("\r\n������󣬲����в��ԣ�\r\n");
		  break;		
			
	}

	if ( pNet_Test )
		  pNet_Test ();
	
		delay_ms(500);
	GpuSend("CLS(0);\r\n");
	GpuSend("DS24(0,0,'WiFi��ʼ�����',4);\r\n");
	delay_ms(500);
	UART_WIFIWrite((u8*)"printer    WiFi��ʼ�����\r\n",sizeof("printer    WiFi��ʼ�����\r\n")) ; 
//End WiFi Module - ESP8266	
#endif
	Rc522_Main();


//	TouchPanel();
}

void TouchPanel()
{
	sprintf(buf,"TPOW(2);\r\n");
		GpuSend(buf); 
}

void Rc522_Main(void)
{
char * pStr ;
	float value;
  RC522_Init (); 	 
	PcdReset();
	M500PcdConfigISOType ( 'A' );//���ù�����ʽ 
		/* TIM2  */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	ui_Show();
	funsel = 0; 
	funMod =1;
	WiFi_EN = 0;
	while(1)
	{ 
		#if WiFi_debug		//�˴�Ϊ����WiFiģ��
						
			 if ( strEsp8266_Fram_Record .InfBit .FramFinishFlag )
				 {
						//��ӡ�յ����ַ���������
						pStr = ESP8266_ReceiveString ( DISABLE );
						PC_Usart ( "%s", pStr );	//��ӡ���򴮿ڵ���
						delay_ms(50);
					} 
			#endif 	 
		GetICNum();
		if(Card_flag>0&&Card_flag<2)
			{
				Card_flag =2;
					BEEP=1;
					delay_ms(20);
					BEEP=0;		
			}				
		value = adc12_main();
		funMap( funMod, funsel,value);
	}
}








