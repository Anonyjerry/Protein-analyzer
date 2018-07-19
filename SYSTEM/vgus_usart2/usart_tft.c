#include "sys.h"
#include "usart_TFT.h"	  


//液晶屏//PA.2  //PA3



char buf[512]; 
char cmd[9];
u8 cjs;	//cjs:cmd命令计数
u8 iscmd;		//==1 表示出于cmd记录中
u8 iswaiting;	//=1 表示等待按键中
u8 iscmdok;	//==1 表示有命令处理
 
void uart2_init(u32 bound)
	{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART2，GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//USART2_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
   
  //USART2_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3  

  //Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口1 

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

//void USART2_IRQHandler(void)                	//串口1中断服务程序
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













