#include "ui.h"
#include <string.h> 
#include <stdio.h>  
#include <stdbool.h>
#include "delay.h"
#include "usart_TFT.h"	  
#include "usart_wifi.h"	  
#include "usart_printer.h"	
#include "mTimer.h"


//�˴�Ϊ������UI���棬�л���ʾTFT��Ļ����Ϣ
//���Խ�ȫ������Ϣ���ϵ�һ����Ϊȫ�ֱ���
//��ʾ��ǰ��Ĭ����Ϣ

//void init_ghost(void)
//{
//GpuSend("\
//CLS(0);\
//SXY(0,0);\
//DS16(80,0,'����Ӳ����Ϣ',4);\
//DS16(0,24,'ѧУ����������ѧ',4);\
//DS16(0,48,'�Ŷӣ�ɰʯ֮��',4);\
//DS16(0,72,'�ںţ�ɰʯ֮�ã��ഺ�������ն��������Զ��',4);\
//DS16(0,96,'��Ա������������������������Զ������Ӫ',4);\
//\r\n");   //TfT��Ļ
// delay_ms(100);	
//GpuSend("\
//SXY(220,200);\
//BTN(1,0,0,43,20,1,140);\
//DS16(7,2,'��ҳ',1);\
//BTN(2,45,0,83,20,1,142);\
//DS16(43,2,'��ҳ',1);\
//SXY(0,0);\
//TPN(2);\
//\r\n");   //TfT��Ļ
//}

void init_infor(void)
{
	
GpuSend("\
CLS(0);\
SXY(0,0);\
DS16(80,30,'�о���������ƴ���',4);\
DS16(0,54,'ѧУ����������ѧ',4);\
DS16(0,78,'�Ŷӣ�ɰʯ֮��',4);\
DS16(0,102,'�ںţ��ഺ�������ն��������Զ��',4);\
DS16(0,126,'��Ա������������������������Զ������Ӫ',4);\
\r\n");   //TfT��Ļ
 delay_ms(100);	
GpuSend("\
SXY(220,200);\
BTN(1,0,0,43,20,1,140);\
DS16(7,2,'��ҳ',1);\
BTN(2,45,0,83,20,1,142);\
DS16(43,2,'��ҳ',1);\
SXY(0,0);\
TPN(2);\
\r\n");   //TfT��Ļ
}

void ui_main(char date[],unsigned char ucArray_ID [ 4 ],float value)
{
	 char *str = "  ";
	 if (value<value_min)  str = "��";
	 if (value>value_max)  str = "��";
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
DS24(100,20,'���׼����',4);\
DS24(0,65,'Date:----',4);\
DS24(0,100,'Card ID:--------',4);\
DS24(0,140,'�����  ������Χ  ״̬',4);\r\n");
GpuSend(buf); 

}



//��ȡ��ʱ��ʱ��Ľ�Ϊ��ȡʱ��ģ��ʱ��
void ui_Timer(uint8_t Date [5])
{
	Date[2] = 24;

	sprintf(buf,"DS24(0,65,'Date:2018.06.%02d %02d:%02d:%02d',4);\r\n",Date[2],Date[3],Date[4],Date[5]);
	GpuSend(buf); 

}






