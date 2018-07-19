#ifndef __USART_PRINTER_H
#define __USART_PRINTER_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
void uart_printer_init(u32 bound);
void UART3_SendByte(u16 Data);
void UART3Write(u8* data,u16 len);

void Usart_SendString( USART_TypeDef * pUSARTx, char *str);



#endif


