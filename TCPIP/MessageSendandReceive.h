#ifndef _MESSAGESENDANDRECEIVE_H
#define _MESSAGESENDANDRECEIVE_H

#include "sys.h"
#include "wifi_function.h"
#include "wifi_config.h"

typedef  struct  STRUCT_USARTx                                  //串口数据帧的处理结构体
{
	char  Data_RX_BUF[ RX_BUF_MAX_LEN ];
	
  union {
    __IO u16 InfAll;
    struct {
		  __IO u16 FramLength       :15;           // 14:0 
		  __IO u16 FramFinishFlag   :1;            // 15 
	  } InfBit;
  }; 
	
} USARTx_Fram_Record, Esp8266_Fram_Record;

typedef struct MSG_FRAM
{
  char  self_mac[13];//u8 msg_len[6];//己方MAC
  char  obj_mac[13];//u8 ver_id[6];//对方MAC
  u8 cli_id[6];//APP custom ID
  u16 seq_id;//message num
  u8  msg_type;//message type 
	// struct msg_bodyT msg_body;  
  Esp8266_Fram_Record msg;
 
}msg_fram;

void Message_que_Send(struct MSG_FRAM sendmsg);
u8 Message_que_receive(struct STRUCT_USARTx msg);

#endif