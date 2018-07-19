#include "MessageSendandReceive.h"
#include "sys.h"
#include "string.h"
#include "delay.h"
#include "wifi_function.h"
#include "wifi_config.h"
#include "usart_TFT.h"	
typedef struct messagepackage
{
	uint16_t id;
	uint8_t SetorRequest;
	
}CMD_Queue;

char *Receive_msg[32] ={0} ;

struct  STRUCT_USARTx Esp8266_Fram_ = { 0 };


/*
消息发送函数

*/
void Message_que_Send(struct MSG_FRAM sendmsg)
{
  

		memcpy(sendmsg.self_mac,"0000000000000",sizeof("0000000000000")-1);
		sendmsg.self_mac[sizeof(sendmsg.self_mac)-1] = ';';
		memcpy(sendmsg.obj_mac,"1000000000000",sizeof("1000000000000")-1);
		sendmsg.obj_mac[sizeof(sendmsg.obj_mac)-1] = ';';
		memcpy(sendmsg.cli_id,"0000000",sizeof("0000000")-1);
		sendmsg.cli_id[sizeof(sendmsg.cli_id)-1] = ';';
		sendmsg.seq_id = 0x1001;
		sendmsg.msg_type = 1;
	
	
	
//		memcpy(sendmsg.msg.Data_RX_BUF ,"rtj;uhtr;yf",sizeof("rtj;uhtr;yf"));

	
		memcpy(buf,&sendmsg,sizeof ( sendmsg ));
			buf[35] = ';';//如何解决这里的问题  结构体分割的地方
		ESP8266_SendString ( DISABLE, buf, strlen ( buf ), Multiple_ID_0 );			

}

/*
消息接收解析函数

*/
u8 Message_que_receive(struct STRUCT_USARTx msg)
{
	char *delimiters = ";";
	char *ptr ;
  u8 count = 0;
	ptr = strtok(msg.Data_RX_BUF,delimiters);
	while(ptr!=NULL)
		{
			Receive_msg[count++] = ptr;
			ptr = strtok(NULL,delimiters);
		}

//根据分割的数据去解析每段内容


	
	return count;
}





