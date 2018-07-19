#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
 
#define DHT11_IO_IN()  {GPIOD->CRH&=0XFFFFF0FF;GPIOD->CRH|=8<<8;}
#define DHT11_IO_OUT() {GPIOD->CRH&=0XFFFFF0FF;GPIOD->CRH|=3<<8;}
////IO��������											   
#define	DHT11_DQ_OUT PDout(10) //���ݶ˿�	PC5
#define	DHT11_DQ_IN  PDin(10)  //���ݶ˿�	PC5


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11  
void DHT11_Main(void);
#endif















