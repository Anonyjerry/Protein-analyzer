#ifndef __RED_H
#define __RED_H 
#include "sys.h"   


#define RDATA 	PBin(9)	 	//�������������

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0      		   

extern u8 RmtCnt;			//�������µĴ���

void Remote_Init(void);    	//���⴫��������ͷ���ų�ʼ��
u8 Remote_Scan(void);
void Remote_Main(void);
#endif















