#ifndef __USART_PRINTER_H
#define __USART_PRINTER_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
void uart_printer_init(u32 bound);
void UART3_SendByte(u16 Data);
void UART3Write(u8* data,u16 len);

void Usart_SendString( USART_TypeDef * pUSARTx, char *str);



#endif


