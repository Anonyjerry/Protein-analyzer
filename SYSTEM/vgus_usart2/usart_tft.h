#ifndef __USART_TFT_H
#define __USART_TFT_H
#include "stdio.h"	
#include "sys.h" 

extern char buf[];

void uart2_init(u32 bound);
void GpuSend(char * buf1);


#endif
