#ifndef __RC522_FUNCTION_H
#define	__RC522_FUNCTION_H


#include "stm32f10x_it.h"

#define          macDummy_Data              0x00

/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
void   PcdReset             ( void );                       //复位
void   M500PcdConfigISOType ( u8 type );                    //工作方式
char   PcdRequest           ( u8 req_code, u8 * pTagType ); //寻卡
char   PcdAnticoll          ( u8 * pSnr);                   //读卡号
char   PcdAuthState         ( u8 ucAuth_mode, u8 ucAddr, u8 * pKey, u8 * pSnr );//验证卡片密码
char   PcdRead              ( u8 ucAddr, u8 * pData );      //读卡
char   PcdSelect            ( u8 * pSnr );                  //选卡   

char    PcdWrite                ( u8 ucAddr, u8 * pData );

#endif 



