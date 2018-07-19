#include "sys.h"
#include "usart_TFT.h"	  


//Һ����//PA.2  //PA3



char buf[512]; 
char cmd[9];
u8 cjs;	//cjs:cmd�������
u8 iscmd;		//==1 ��ʾ����cmd��¼��
u8 iswaiting;	//=1 ��ʾ�ȴ�������
u8 iscmdok;	//==1 ��ʾ�������
 
void uart2_init(u32 bound)
	{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART2��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//USART2_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.2
   
  //USART2_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3  

  //Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���1 

}
void GpuSend(char *buf1)
{	
	u8 i=0;
	
	while (buf1[i]!=0)
	{	
			USART_SendData(USART2, buf1[i]);
			while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
			i++;
	}
}

//void USART2_IRQHandler(void)                	//����1�жϷ������
//{
//	u8	gc;
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)    
//	{	
//		gc=USART_ReceiveData(USART2);  
//			if (gc=='[')
//			{	cjs=0;
//				iscmd=1;
//			}
//			else if(gc==']')
//			{	iscmd=0;
//				iscmdok=1;
//			}
//			else if (iscmd==1)
//			{	cmd[cjs]=gc;
//				cjs++;
//				if (cjs==8)
//				{	iscmd=0;
//					cjs=0;
//				}
//			}
//	}
//} 













