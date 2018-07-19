#ifndef __UI_H
#define	__UI_H 

#include <string.h> 
#include "delay.h"

#define value_min 1.0
#define value_max 3.0



void init_ghost(void);
void init_infor(void);
void ui_main(char date[],unsigned char ucArray_ID [ 4 ],float value);
void ui_Show(void);

void ui_Timer(uint8_t Date [5]);

#endif