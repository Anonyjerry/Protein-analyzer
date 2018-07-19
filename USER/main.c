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

//打印机打印
void Printer(char *string,float AD,char data[] )
{
	char *str = "  ";
	 if (AD<value_min)  str = "↓";
	 if (AD>value_max)  str = "↑";
	 
//		Usart_SendString( USART3,string);
	
		delay_ms(50);
		UART3Write((u8*)"\x1b\x4a\x30",sizeof("\x1b\x4a\x30")) ; 	
	
		sprintf(buf,"      胱抑素C测量结果");
		Usart_SendString( USART3,buf);
	
		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 
		sprintf(buf,"日期：2018年06月%02d日  %02d:%02d:%02d ", gDate [ 2 ], gDate [ 3 ],gDate [ 4 ], gDate [ 5 ]);
		Usart_SendString( USART3,buf);
		delay_ms(10);
	
		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 
		sprintf(buf,"蛋白仪卡ID：%02X%02X%02X%02X ",data [ 0 ], data [ 1 ], data [ 2 ], data [ 3 ]);
		Usart_SendString( USART3,buf);
		delay_ms(10);
			
		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 	
		sprintf(buf,"检测结果    正常范围     状态");
		Usart_SendString( USART3,buf);
		delay_ms(10);

		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 	
		sprintf(buf,"  %.3F     %.1f--%.1f      %s ",AD,value_min,value_max,str);
//		delay_ms(50);
		Usart_SendString( USART3,buf);
//	delay_ms(50);
		UART3Write((u8*)"\x1b\x4a\x40",sizeof("\x1b\x4a\x40")) ; 	

		//移动并剪切
		UART3Write((u8*)"\x1b\x4a\x60",sizeof("\x1b\x4a\x60")) ; 	
		UART3Write((u8*)"\x1b\x69",sizeof("\x1b\x69")) ; 	
}

void ( * pNet_Test ) ( void );

 int main(void)
 {	 
		char cCh;	
	
		delay_init();	    	 //延时函数初始化	  
	 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 	 TIM2_Configuration();
		TIM2_NVIC_Configuration();
		EXTIKEYX_Init();
	 uart_init(115200);	     //wifi
		uart_printer_init(9600);  //9600
		uart2_init(115200);	      //tft
		
	 	Adc_Init();		  		//ADC初始化
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

// 	//	WriteFlashData(10,dt,sizeof(dt)); //写入指定地址字符串    
//    delay_ms(10);                           
////    ReadNum =ReadFlashNBtye (10, Temp_Data,sizeof(dt)*2); 
////    Temp = (unsigned char)ReadNum;  
////	
////	for(i=0;i<sizeof(dt)*2;i++)
////	{
////		Te[n++]=Temp_Data[i++];
////	}
//	 flashReadStr(10,Temp_Data,sizeof(dt));
//		sprintf(buf,"DS16(0,150,'测试通过写入字符串%s',4);\r\n",Temp_Data );
//		GpuSend(buf); 
//}

	  
#if WiFi_debug

// WiFi Module - ESP8266

		PC_Usart("\r\n WIFI-ESP8266 WiFi模块\r\n");                            //打印测试例程提示信息

  PC_Usart ( "\r\n请输入模块的测试模式的编号，编号如下：\
              \r\n1.STA模式： TCP Client\
              \r\n2.AP模式： AP Server\
              \r\n3.STA+AP模式： (STA)TCP Client + (AP)TCP Server\
              \r\n输入格式为：编号+空格，点击发送\r\n" );
	
//  scanf ( "%c",  & cCh );
cCh = '2';
  switch ( cCh )
  {
		case '1':
			pNet_Test = ESP8266_STA_TCP_Client;
		  PC_Usart("\r\n即将进行的测试是：1.STA模式： TCP Client\r\n");
		  break;
		
		case '2':
			pNet_Test = ESP8266_AP_TCP_Server;
		  PC_Usart("\r\n即将进行的测试是：2.AP模式： TCP Server\r\n");
		  break;

		case '3':
			pNet_Test = ESP8266_StaTcpClient_ApTcpServer;
		  PC_Usart("\r\n即将进行的测试是：3.STA+AP模式： (STA)TCP Client + (AP)TCP Server\r\n");
		  break;

		default:
			pNet_Test = NULL;
		  PC_Usart("\r\n输入错误，不进行测试！\r\n");
		  break;		
			
	}

	if ( pNet_Test )
		  pNet_Test ();
	
		delay_ms(500);
	GpuSend("CLS(0);\r\n");
	GpuSend("DS24(0,0,'WiFi初始化完成',4);\r\n");
	delay_ms(500);
	UART_WIFIWrite((u8*)"printer    WiFi初始化完成\r\n",sizeof("printer    WiFi初始化完成\r\n")) ; 
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
	M500PcdConfigISOType ( 'A' );//设置工作方式 
		/* TIM2  */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	ui_Show();
	funsel = 0; 
	funMod =1;
	WiFi_EN = 0;
	while(1)
	{ 
		#if WiFi_debug		//此处为测试WiFi模块
						
			 if ( strEsp8266_Fram_Record .InfBit .FramFinishFlag )
				 {
						//打印收到的字符串到串口
						pStr = ESP8266_ReceiveString ( DISABLE );
						PC_Usart ( "%s", pStr );	//打印机或串口调试
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








