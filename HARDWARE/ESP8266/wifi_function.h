#ifndef __WIFI_FUNCTION_H
#define	__WIFI_FUNCTION_H 


#include "stm32f10x.h"
#include "wifi_config.h"
#include <stdbool.h>

#define WiFi_debug 0              //限制开机WiFi初始化
#define WiFi_debug_print 0        //限制打印机or串口调试助手
#define WiFi_name "CUST WiFi"
#define WiFi_passWord "1234567890"
#define WiFi_Port "8080"

#define WiFi_connect_name "TP_LINK_02BD"
#define WiFi_connect_passWord "88888888"





#define     ESP8266_Usart( fmt, ... )             printf ( fmt, ##__VA_ARGS__ ) 


//进入调试模式，就可以打印机打印wifi指令记录
#if WiFi_debug_print 
	#define     PC_Usart( fmt, ... )              	USART3_printf ( USART3, fmt, ##__VA_ARGS__ ) //打印机or串口调试助手
#else 
	#define     PC_Usart( fmt, ... )              	USART3_printfNull ( USART3, fmt, ##__VA_ARGS__ ) //打印机or串口调试助手
#endif


#define WiFi_EN PDout(14)	//WiFi_enable
#define     ESP8266_CH_HIGH_LEVEL()             GPIO_SetBits( GPIOD, GPIO_Pin_14 )  
#define     ESP8266_CH_LOW_LEVEL()              GPIO_ResetBits( GPIOD, GPIO_Pin_14 )

#define     ESP8266_RST_HIGH_LEVEL()            GPIO_SetBits( GPIOA, GPIO_Pin_11 )
#define     ESP8266_RST_LOW_LEVEL()             GPIO_ResetBits( GPIOA, GPIO_Pin_11 )


void        ESP8266_Choose                      ( FunctionalState enumChoose );
void        ESP8266_Rst                         ( void );
void        ESP8266_AT_Test                     ( void );
bool        ESP8266_Cmd                         ( char * cmd, char * reply1, char * reply2, u32 waittime );
bool        ESP8266_Net_Mode_Choose             ( ENUM_Net_ModeTypeDef enumMode );
bool        ESP8266_JoinAP                      ( char * pSSID, char * pPassWord );
bool        ESP8266_BuildAP                     ( char * pSSID, char * pPassWord, char * enunPsdMode );
bool        ESP8266_Enable_MultipleId           ( FunctionalState enumEnUnvarnishTx );
bool        ESP8266_Link_Server                 ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id);
bool        ESP8266_StartOrShutServer           ( FunctionalState enumMode, char * pPortNum, char * pTimeOver );
bool        ESP8266_SendString                  ( FunctionalState enumEnUnvarnishTx, char * pStr, u32 ulStrLength, ENUM_ID_NO_TypeDef ucId );
char *      ESP8266_ReceiveString               ( FunctionalState enumEnUnvarnishTx );

void        ESP8266_STA_TCP_Client              ( void );
void        ESP8266_AP_TCP_Server               ( void );
void        ESP8266_StaTcpClient_ApTcpServer    ( void );


#endif    /* __WIFI_FUNCTION_H */