#ifndef __USARTT_H
#define __USARTT_H
#include "stdio.h"	
#include "sys.h" 

extern char buf[];

int fgetc(FILE *f);
void uart2_init(u32 bound);
void GpuSend(char * buf1);
extern void USART2_printf(USART_TypeDef* USARTx, char *Data, ...);

void USART2_printfNull( USART_TypeDef* USARTx, char *Data, ... );

#endif
