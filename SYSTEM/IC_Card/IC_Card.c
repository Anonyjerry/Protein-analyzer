#include "ic_card.h"
#include "rc522_function.h"
#include "rc522_config.h" 
#include "string.h"
#include "stdio.h"
#include <stdlib.h>
unsigned char ucArray_ID [ 4 ]={0}; //����
unsigned char pucArray_ID [ 4 ]={0}; //����
unsigned char  DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  //IC����������
unsigned char Card_flag = 0;
//	u8  RevBuffer =AD;

//	u8 Rres = AD; 
//	u8 nblock =8;

char *r =0;
u8 GetICNum()
{

  //�Ⱥ���IC�������ͺ�UID(IC�����к�)
	uint8_t ucStatusReturn;          //����״̬
	unsigned char Array_ID [ 4 ]={0}; //����
	int count =0;
	
	
	      /*1Ѱ��*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, Array_ID ) ) != MI_OK &&count<2) 
		{
			count++;
					 /*��ʧ���ٴ�Ѱ��*/
			ucStatusReturn = PcdRequest ( PICC_REQALL, Array_ID );
		}

		r = strstr(ucArray_ID,Array_ID);
   // r = memcmp(ucArray_ID,Array_ID,sizeof(Array_ID));
		if ( ucStatusReturn == MI_OK &&r ==NULL )
		{
      /*2����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����*/
			if ( PcdAnticoll ( Array_ID ) == MI_OK )  
			{
//				/*3 ѡ��*/
//				if (PcdSelect ( ucArray_ID ) != MI_OK)
//				{
//					return  ;
//				}
//				/*4 �趨��*/
//			if (PcdAuthState(PICC_AUTHENT1A, nblock, DefaultKey, ucArray_ID)!= MI_OK)
//				{
//					sprintf(buf,"DS24(0,0,'����֤ʧ�ܣ������Ի򻻿�',4);\r\n");
//					GpuSend(buf);
//					return  ;
//				}
//				/*5 ����ַд������*/
//			if(PcdWrite(nblock,&RevBuffer) != MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'д����������Ի�ÿ���ʧЧ',4);\r\n");
//					GpuSend(buf);
//					return;
//				}
//					/*5-1 ����ַ��ȡ����*/
//				if(PcdRead(nblock,&Rres)!=MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'���ݶ�ȡ����',4);\r\n");
//					GpuSend(buf);
//					return;
//					
//				}
//				AD = Rres;
				Card_flag ++;
				memcpy(ucArray_ID,Array_ID,sizeof(Array_ID));
			  return 1;
				}
			
		}
	 else if( ucStatusReturn != MI_OK)
		{
			Card_flag = 0;
			memset(ucArray_ID,'\0',sizeof(ucArray_ID));
			return 0;
		}  
		
		
}


//��ָ����IC��ָ���ĵ�ַд��ָ�������ݣ�
uint8_t IC_ReadData(unsigned char IC_ID [  ],u8 nblock,char array[])
{
	u8 Rres;
	
	 /*2����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  
			{
				/*3 ѡ��*/
				if (PcdSelect ( ucArray_ID ) != MI_OK)
				{
					return  -1;
				}
				/*4 �趨��*/
			if (PcdAuthState(PICC_AUTHENT1A, nblock, DefaultKey, ucArray_ID)!= MI_OK)
				{

					return -1 ;
				}
//				/*5 ����ַд������*/
//			if(PcdWrite(nblock,&RevBuffer) != MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'д����������Ի�ÿ���ʧЧ',4);\r\n");
//					GpuSend(buf);
//					return;
//				}
					/*5-1 ����ַ��ȡ����*/
				if(PcdRead(nblock,&Rres)!=MI_OK)
				{

					return -1;
					
				}
				memcpy(array,&Rres,sizeof(Rres));
			}
	return -1;
}


//��ָ����IC����ָ���ĵ�ַд������
uint8_t IC_WriteData(unsigned char IC_ID [],u8 nblock,u8 array[])
{
	int n=0;
		u8  RevBuffer ;
	 /*2����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  
			{
				/*3 ѡ��*/
				if (PcdSelect ( ucArray_ID ) != MI_OK)
				{
					return  -1;
				}
				/*4 �趨��*/
			if (PcdAuthState(PICC_AUTHENT1A, nblock, DefaultKey, ucArray_ID)!= MI_OK)
				{
//					sprintf(buf,"DS24(0,0,'����֤ʧ�ܣ������Ի򻻿�',4);\r\n");
//					GpuSend(buf);
					return -1 ;
				}
				/*5 ����ַд������*/
				//n=sizeof(array);
				memcpy(&RevBuffer,array,sizeof(array));
			if(PcdWrite(nblock,&RevBuffer) != MI_OK)
				{

					return -1;
				}
//					/*5-1 ����ַ��ȡ����*/
//				if(PcdRead(nblock,&Rres)!=MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'���ݶ�ȡ����',4);\r\n");
//					GpuSend(buf);
//					return;
//					
//				}
	
			}
	
	return -1;
}

///***********************************///
//��д��RF��һ��Ҫ�������¼�������
//1��Ѱ��    status2=PcdRequest(0x52,Temp);////Ѱ�������������
//2������ͻ   status2= PcdAnticoll(UID);  //��ײ�崦��,�����Ƭ���к�,4�ֽ�
//3��ѡ��			 status2= PcdSelect(UID);  //ѡ���������У�4�ֽ�
//  �� 4 ��֮ǰ��Ҫ��Ҫ����֤   status2= PcdAuthState(PICC_AUTHENT1A, 1, Password_Buffer, UID);
//				��֤��ԿA�����ַ����Կ�������
//4������д��     status2=PcdWrite(1,writeData);  //���ַ��data

///***********************************///
void IC_test_ ( )
{
  //�Ⱥ���IC�������ͺ�UID(IC�����к�)
	uint8_t ucStatusReturn;          //����״̬
	u8 nblock =8;
 // while ( 1 )
  { 
       /*1Ѱ��*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )                                   
			 /*��ʧ���ٴ�Ѱ��*/
      ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		   
		if ( ucStatusReturn == MI_OK  )
		{
      /*2����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  
			{
//				/*3 ѡ��*/
//				if (PcdSelect ( ucArray_ID ) != MI_OK)
//				{
//					return  ;
//				}
//				/*4 �趨��*/
//			if (PcdAuthState(PICC_AUTHENT1A, nblock, DefaultKey, ucArray_ID)!= MI_OK)
//				{
//					sprintf(buf,"DS24(0,0,'����֤ʧ�ܣ������Ի򻻿�',4);\r\n");
//					GpuSend(buf);
//					return  ;
//				}
//				/*5 ����ַд������*/
//			if(PcdWrite(nblock,&RevBuffer) != MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'д����������Ի�ÿ���ʧЧ',4);\r\n");
//					GpuSend(buf);
//					return;
//				}
//					/*5-1 ����ַ��ȡ����*/
//				if(PcdRead(nblock,&Rres)!=MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'���ݶ�ȡ����',4);\r\n");
//					GpuSend(buf);
//					return;
//					
//				}
				}
		}	
  }	
}