#ifndef _MTIMER_H
#define _MTIMER_H

#include "stm32f10x.h"

#include "delay.h"
extern uint16_t time;
extern unsigned char gDate [6];

void TIM2_NVIC_Configuration(void);
void TIM2_Configuration(void);

#endif	/* TIME_TEST_H */