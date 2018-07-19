#include "ui.h"
#include <string.h> 
#include <stdio.h>  
#include <stdbool.h>
#include "delay.h"
#include "usart_TFT.h"	  
#include "usart_wifi.h"	  
#include "usart_printer.h"	
#include "mTimer.h"


//此处为整个的UI界面，切换显示TFT屏幕的信息
//可以将全部的信息整合到一起，作为全局变量
//显示当前的默认信息

//void init_ghost(void)
//{
//GpuSend("\
//CLS(0);\
//SXY(0,0);\
//DS16(80,0,'本机硬件信息',4);\
//DS16(0,24,'学校：长春理工大学',4);\
//DS16(0,48,'团队：砂石之旅',4);\
//DS16(0,72,'口号：砂石之旅，青春飞扬，披荆斩棘，奔向远方',4);\
//DS16(0,96,'成员：尹莉、刘忠宁、郭金明、秦远、梁龙营',4);\
//\r\n");   //TfT屏幕
// delay_ms(100);	
//GpuSend("\
//SXY(220,200);\
//BTN(1,0,0,43,20,1,140);\
//DS16(7,2,'上页',1);\
//BTN(2,45,0,83,20,1,142);\
//DS16(43,2,'下页',1);\
//SXY(0,0);\
//TPN(2);\
//\r\n");   //TfT屏幕
//}

void init_infor(void)
{
	
GpuSend("\
CLS(0);\
SXY(0,0);\
DS16(80,30,'研究生电子设计大赛',4);\
DS16(0,54,'学校：长春理工大学',4);\
DS16(0,78,'团队：砂石之旅',4);\
DS16(0,102,'口号：青春飞扬，披荆斩棘，奔向远方',4);\
DS16(0,126,'成员：尹莉、刘忠宁、郭金明、秦远、梁龙营',4);\
\r\n");   //TfT屏幕
 delay_ms(100);	
GpuSend("\
SXY(220,200);\
BTN(1,0,0,43,20,1,140);\
DS16(7,2,'上页',1);\
BTN(2,45,0,83,20,1,142);\
DS16(43,2,'下页',1);\
SXY(0,0);\
TPN(2);\
\r\n");   //TfT屏幕
}

void ui_main(char date[],unsigned char ucArray_ID [ 4 ],float value)
{
	 char *str = "  ";
	 if (value<value_min)  str = "↓";
	 if (value>value_max)  str = "↑";
	ui_Timer(gDate);
sprintf(buf,"\
DS24(0,100,'Card ID:%02X%02X%02X%02X',4);\
DS24(0,180,' %.4f    %.1f--%.1f  %s',4);\r\n",ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ],value,value_min,value_max,str);
GpuSend(buf); 
}
void ui_Show(void)
{
	sprintf(buf,"\
CLS(0);\
DS24(100,20,'蛋白检测仪',4);\
DS24(0,65,'Date:----',4);\
DS24(0,100,'Card ID:--------',4);\
DS24(0,140,'检测结果  正常范围  状态',4);\r\n");
GpuSend(buf); 

}



//获取定时器时间改进为获取时钟模块时间
void ui_Timer(uint8_t Date [5])
{
	Date[2] = 24;

	sprintf(buf,"DS24(0,65,'Date:2018.06.%02d %02d:%02d:%02d',4);\r\n",Date[2],Date[3],Date[4],Date[5]);
	GpuSend(buf); 

}






