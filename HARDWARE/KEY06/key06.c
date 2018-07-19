#include "stm32f10x.h"
#include "key06.h"
#include "sys.h" 
#include "beep.h"
#include "delay.h"
#include "usart_TFT.h"	  
#include "usart_wifi.h"	  
#include "usart_printer.h"	
								    
//按键初始化函数
void KEY06_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = RFKEY_VT|RFKEY_D0|RFKEY_D1|RFKEY_D2|RFKEY_D3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //下拉输入
 	GPIO_Init(RFKEY, &GPIO_InitStructure);//初始化IO
	
}
/**********************************************************
函数名		：u8 KEY_Scan(u8 mode)
函数功能	：扫描按键是否按下
输入			：0或1   0 支持连按   1  不支持连按
输出			：按键对应值 1-4
**********************************************************/


u8 KEY06_Scan(u8 mode)
{	 
	static u8 key_up = 1;//按键按松开标志
	if(KEY_VT==high)
	{
		if(mode)key_up = 1;  //支持连按		  
		if(key_up&&(KEY_D3 == high || KEY_D2 == high || KEY_D1 == high || KEY_D0 == high))
		{
			delay_ms(10);//去抖动 
			key_up = 0;
			if(KEY_D3 == high) return KEY_D3_PRES;
			if(KEY_D2 == high) return KEY_D2_PRES;
			if(KEY_D1 == high) return KEY_D1_PRES;
			if(KEY_D0 == high) return KEY_D0_PRES;
		}else if(KEY_D3 == low && KEY_D2 == low && KEY_D1 == low && KEY_D0 == low)key_up=1; 	 
	}	
 	return 0;// 无按键按下
}

void Key06_Main(void)
{
	u8 buffer=0;        //存储按键扫描值
	 
	KEY06_Init();          //初始化与按键连接的硬件接口
	BEEP_Init();
	uart2_init( 115200 );  //串口屏波特率 115200
	uart_init( 115200 );  //串口屏波特率 115200
	delay_ms( 1000 );      //延时等待屏幕
  GpuSend("CLS(1);\r\n");
	GpuSend("DS24(70,50,'开关量射频实验',4);\r\n");
	
	while(USART_RX_BUF[5]=='6')
	{
		buffer = KEY06_Scan(0);//记录按键扫描值0、1、2、3、4、
		if(buffer != 0)
		{ 
			switch(buffer)
			{
				case 0x01:
				{
					GpuSend("DS24(100,120,'键值：B ',4);\r\n");
				  break;
				}
				case 2:
				{
					GpuSend("DS24(100,120,'键值：D ',4);\r\n");
				  break;
				}
				case 3:
				{
					GpuSend("DS24(100,120,'键值：A ',4);\r\n");
				  break;
				}
				case 4:
				{
					GpuSend("DS24(100,120,'键值：C ',4);\r\n");
				  break;
				}
				default:break;
			}
			delay_ms(100);
		}
	}	 	
}



