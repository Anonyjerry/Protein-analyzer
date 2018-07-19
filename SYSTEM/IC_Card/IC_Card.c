#include "ic_card.h"
#include "rc522_function.h"
#include "rc522_config.h" 
#include "string.h"
#include "stdio.h"
#include <stdlib.h>
unsigned char ucArray_ID [ 4 ]={0}; //卡号
unsigned char pucArray_ID [ 4 ]={0}; //卡号
unsigned char  DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  //IC卡部分上锁
unsigned char Card_flag = 0;
//	u8  RevBuffer =AD;

//	u8 Rres = AD; 
//	u8 nblock =8;

char *r =0;
u8 GetICNum()
{

  //先后存放IC卡的类型和UID(IC卡序列号)
	uint8_t ucStatusReturn;          //返回状态
	unsigned char Array_ID [ 4 ]={0}; //卡号
	int count =0;
	
	
	      /*1寻卡*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, Array_ID ) ) != MI_OK &&count<2) 
		{
			count++;
					 /*若失败再次寻卡*/
			ucStatusReturn = PcdRequest ( PICC_REQALL, Array_ID );
		}

		r = strstr(ucArray_ID,Array_ID);
   // r = memcmp(ucArray_ID,Array_ID,sizeof(Array_ID));
		if ( ucStatusReturn == MI_OK &&r ==NULL )
		{
      /*2防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			if ( PcdAnticoll ( Array_ID ) == MI_OK )  
			{
//				/*3 选卡*/
//				if (PcdSelect ( ucArray_ID ) != MI_OK)
//				{
//					return  ;
//				}
//				/*4 设定卡*/
//			if (PcdAuthState(PICC_AUTHENT1A, nblock, DefaultKey, ucArray_ID)!= MI_OK)
//				{
//					sprintf(buf,"DS24(0,0,'卡认证失败，请重试或换卡',4);\r\n");
//					GpuSend(buf);
//					return  ;
//				}
//				/*5 向块地址写入数据*/
//			if(PcdWrite(nblock,&RevBuffer) != MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'写入出错，请重试或该卡已失效',4);\r\n");
//					GpuSend(buf);
//					return;
//				}
//					/*5-1 向块地址读取数据*/
//				if(PcdRead(nblock,&Rres)!=MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'数据读取出错！',4);\r\n");
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


//向指定的IC卡指定的地址写入指定的数据，
uint8_t IC_ReadData(unsigned char IC_ID [  ],u8 nblock,char array[])
{
	u8 Rres;
	
	 /*2防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  
			{
				/*3 选卡*/
				if (PcdSelect ( ucArray_ID ) != MI_OK)
				{
					return  -1;
				}
				/*4 设定卡*/
			if (PcdAuthState(PICC_AUTHENT1A, nblock, DefaultKey, ucArray_ID)!= MI_OK)
				{

					return -1 ;
				}
//				/*5 向块地址写入数据*/
//			if(PcdWrite(nblock,&RevBuffer) != MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'写入出错，请重试或该卡已失效',4);\r\n");
//					GpuSend(buf);
//					return;
//				}
					/*5-1 向块地址读取数据*/
				if(PcdRead(nblock,&Rres)!=MI_OK)
				{

					return -1;
					
				}
				memcpy(array,&Rres,sizeof(Rres));
			}
	return -1;
}


//向指定的IC卡在指定的地址写入数据
uint8_t IC_WriteData(unsigned char IC_ID [],u8 nblock,u8 array[])
{
	int n=0;
		u8  RevBuffer ;
	 /*2防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  
			{
				/*3 选卡*/
				if (PcdSelect ( ucArray_ID ) != MI_OK)
				{
					return  -1;
				}
				/*4 设定卡*/
			if (PcdAuthState(PICC_AUTHENT1A, nblock, DefaultKey, ucArray_ID)!= MI_OK)
				{
//					sprintf(buf,"DS24(0,0,'卡认证失败，请重试或换卡',4);\r\n");
//					GpuSend(buf);
					return -1 ;
				}
				/*5 向块地址写入数据*/
				//n=sizeof(array);
				memcpy(&RevBuffer,array,sizeof(array));
			if(PcdWrite(nblock,&RevBuffer) != MI_OK)
				{

					return -1;
				}
//					/*5-1 向块地址读取数据*/
//				if(PcdRead(nblock,&Rres)!=MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'数据读取出错！',4);\r\n");
//					GpuSend(buf);
//					return;
//					
//				}
	
			}
	
	return -1;
}

///***********************************///
//对写入RF卡一般要经过以下几个步骤
//1、寻卡    status2=PcdRequest(0x52,Temp);////寻卡，输出卡类型
//2、防冲突   status2= PcdAnticoll(UID);  //防撞冲处理,输出卡片序列号,4字节
//3、选卡			 status2= PcdSelect(UID);  //选卡，卡序列，4字节
//  第 4 步之前需要需要先认证   status2= PcdAuthState(PICC_AUTHENT1A, 1, Password_Buffer, UID);
//				验证秘钥A，块地址，秘钥，卡序号
//4、读、写卡     status2=PcdWrite(1,writeData);  //块地址，data

///***********************************///
void IC_test_ ( )
{
  //先后存放IC卡的类型和UID(IC卡序列号)
	uint8_t ucStatusReturn;          //返回状态
	u8 nblock =8;
 // while ( 1 )
  { 
       /*1寻卡*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )                                   
			 /*若失败再次寻卡*/
      ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		   
		if ( ucStatusReturn == MI_OK  )
		{
      /*2防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  
			{
//				/*3 选卡*/
//				if (PcdSelect ( ucArray_ID ) != MI_OK)
//				{
//					return  ;
//				}
//				/*4 设定卡*/
//			if (PcdAuthState(PICC_AUTHENT1A, nblock, DefaultKey, ucArray_ID)!= MI_OK)
//				{
//					sprintf(buf,"DS24(0,0,'卡认证失败，请重试或换卡',4);\r\n");
//					GpuSend(buf);
//					return  ;
//				}
//				/*5 向块地址写入数据*/
//			if(PcdWrite(nblock,&RevBuffer) != MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'写入出错，请重试或该卡已失效',4);\r\n");
//					GpuSend(buf);
//					return;
//				}
//					/*5-1 向块地址读取数据*/
//				if(PcdRead(nblock,&Rres)!=MI_OK)
//				{
//					GpuSend("CLS(0);\r\n"); 
//					sprintf(buf,"DS24(0,0,'数据读取出错！',4);\r\n");
//					GpuSend(buf);
//					return;
//					
//				}
				}
		}	
  }	
}