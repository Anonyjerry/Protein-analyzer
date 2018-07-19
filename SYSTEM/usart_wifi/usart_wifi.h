#ifndef __USART_WIFI_H
#define __USART_WIFI_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern char  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void UART_WIFIWrite(u8* data,u16 len);
void UART_WIFI_SendByte(u16 Data);
void USART1_printfNull( USART_TypeDef* USARTx, char *Data, ... );
void USART1_printf( USART_TypeDef* USARTx, char *Data, ... );





#endif


