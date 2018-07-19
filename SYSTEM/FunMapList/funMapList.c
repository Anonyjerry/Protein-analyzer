#include "funmaplist.h"
#include "sys.h"
#include "ui.h"
#include "ic_card.h"
#include "usart_TFT.h"	 
#include "delay.h"
#include "extikey.h"

#include "wifi_function.h"
#include "wifi_config.h"
#include "MessageSendandReceive.h"

extern void Printer(char *string,float AD,char data[] );
unsigned char funMod = 0;// 0 ghost   1  normal

unsigned char funsel = 0;// 001开wifi   010 标定  100打印

unsigned char fun_G = 0;// 001 Decerese 010 Increase   100 next



unsigned char KeyScan()
{
	char statue = 0;
	if (Key_p)statue = statue|0x04;
	if (Key_d)statue = statue|0x02;
	if (Key_Wifi)statue = statue|0x01;
	 Key_p =0;
	 Key_d =0;
	 Key_Wifi = 0;
	return statue;
}


void funMap_Key( unsigned char sel,float AD)
{
	char array[] ={0};
	delay_ms(20);
	switch ( (uint8_t)sel)
	{
		struct MSG_FRAM senmsg;
		char tmpbuf[128];
		int n=0;
			case 0x01://normal
					sprintf(buf,"DS24(150,210,'网络数据同步',4);\r\n" );
					GpuSend(buf); 
//						IC_ReadData(ucArray_ID,Calibrate_nblock, array);
//						sprintf(buf,"DS24(150,210,'读取标定:%s',4);\r\n" ,array);
//						GpuSend(buf); 
				delay_ms(60);
				#if 1    //WiFi_debug		
			
			sprintf(tmpbuf,"Card_ID:%02X%02X%02X%02X;Value:%.4f;\r\n",ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ],AD);
		
			memcpy(senmsg.msg.Data_RX_BUF ,tmpbuf,sizeof(tmpbuf));
			Message_que_Send(senmsg);
			
//						sprintf(buf,"Card ID:%02X%02X%02X%02X; Value:%.4f V;\r\n",ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ],AD);
//						ESP8266_SendString ( DISABLE, buf, strlen ( buf ), Multiple_ID_0 );			
						delay_ms(50);
				#endif		
			  break;
			case 0x02:
				sprintf(buf,"DS24(180,210,'标定中...',4);\r\n" );
				GpuSend(buf);
				IC_WriteData(ucArray_ID,Calibrate_nblock,(u8*)Calibrate_nblock);
				delay_ms(50);
				break;
			case 0x03:
//				if(sel==0x03)
//			{
//				sprintf(buf,"DS24(180,210,'标定中...',4);\r\n" );
//				GpuSend(buf);
//				IC_WriteData(ucArray_ID,Calibrate_nblock,(u8*)Calibrate_nblock);
//				delay_ms(50);
//			}
				break;
			case 0x04:
				sprintf(buf,"DS24(180,210,'打印中...',4);\r\n" );
				GpuSend(buf);
				delay_ms(50);
				Printer("",AD,(char *)ucArray_ID );
				delay_ms(10);
				break;
			case 0x05:
				WiFi_EN = !WiFi_EN;
				delay_ms(10);
				if (WiFi_EN)
					{
						ESP8266_AP_TCP_Server ();
						sprintf(buf,"DS24(180,210,'WiFi 已开启',4);\r\n" );
						GpuSend(buf);
					}		
				else
					{
						sprintf(buf,"DS24(180,210,'WiFi 已关闭',4);\r\n" );
						GpuSend(buf);
					}
				delay_ms(500);
				break;
			case 0x06://normal  可以将信息写入STM32指定的Flash区域中等
				IC_ReadData(ucArray_ID,Calibrate_nblock, array);
				sprintf(buf,"DS24(0,210,'读取卡内信息为:%s',4);\r\n" ,array);
				GpuSend(buf); 
				delay_ms(1000);
				break;
//			case 0x07://normal
//				sprintf(buf,"CLS(0);DS24(100,0,'Ghost',4);\r\n" );
//				GpuSend(buf); 
//				delay_ms(1000);
//				break;
		  default:sel =0;
				break;
	}	
}


void funMap(unsigned char Mod, unsigned char sel,float AD)
{
	char array[] ={0};
	delay_ms(20);
	switch ( (uint8_t)Mod)
	{
		case 0:
			if(sel==100)delay_ms(50);
			break;
		case 0x01://normal
			 ui_main((char *)ucArray_ID,ucArray_ID,AD);
			 delay_ms(50);
			 sel = KeyScan();
		   funMap_Key(sel, AD);
			break;
		default:sel =0;
			break;
	
	}	
	if(sel)
		{ 
			sel =0;
			sprintf(buf,"DS24(0,210,'                          ',4);\r\n" );
			GpuSend(buf); 
		} 
}
