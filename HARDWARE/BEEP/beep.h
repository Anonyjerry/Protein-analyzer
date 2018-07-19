#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

#define BEEP PAout(8)	// BEEP,蜂鸣器接口		   

void BEEP_Init(void);	//初始化
		 				    
#endif

