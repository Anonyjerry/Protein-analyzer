#ifndef _FUNMAPLIST_H
#define _FUNMAPLIST_H
#include "sys.h"


extern unsigned char funMod ;// 0 ghost   1  normal

extern unsigned char funsel;// 100��ӡ   010 �궨  001��wifi

extern unsigned char fun_G ;// 100 next  010 Increase  001 Decerese

void funMap(unsigned char Mod, unsigned char sel,float AD);
void funMap_Key( unsigned char sel,float AD);

#endif