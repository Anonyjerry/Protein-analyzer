#ifndef _IC_CARD_H
#define _IC_CARD_H

#include "sys.h"
#define  Calibrate_nblock   56
#define  Measure_nblock     256

extern unsigned char ucArray_ID [ 4 ]; //����

extern unsigned char  DefaultKey[6];  //IC����������
extern unsigned char Card_flag ;//�����ڵı�־

u8 GetICNum();
uint8_t IC_ReadData(unsigned char IC_ID [],u8 nblock,char array[]);
uint8_t IC_WriteData(unsigned char IC_ID [],u8 nblock,u8 array[]);
void IC_test_ ( );
#endif