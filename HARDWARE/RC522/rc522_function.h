#ifndef __RC522_FUNCTION_H
#define	__RC522_FUNCTION_H


#include "stm32f10x_it.h"

#define          macDummy_Data              0x00

/* ��չ���� ------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
void   PcdReset             ( void );                       //��λ
void   M500PcdConfigISOType ( u8 type );                    //������ʽ
char   PcdRequest           ( u8 req_code, u8 * pTagType ); //Ѱ��
char   PcdAnticoll          ( u8 * pSnr);                   //������
char   PcdAuthState         ( u8 ucAuth_mode, u8 ucAddr, u8 * pKey, u8 * pSnr );//��֤��Ƭ����
char   PcdRead              ( u8 ucAddr, u8 * pData );      //����
char   PcdSelect            ( u8 * pSnr );                  //ѡ��   

char    PcdWrite                ( u8 ucAddr, u8 * pData );

#endif 



