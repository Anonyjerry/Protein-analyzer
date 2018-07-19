#ifndef __FLASH_WR_H
#define __FLASH_WR_H

#include <stdint.h>

#define  STARTADDR  0x08010000 

#define  IC_MessAddr  0    //IC卡信息存储地址
#define  Protein_Addr  128   //蛋白信息存储地址
#define  Wifi_Addr  256      //WIFI信息地址

#if defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
  #define FLASH_PAGE_SIZE    ((uint16_t)0x800)
  
#else
  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#endif


int Flash_Read(uint32_t iAddress, uint8_t *buf, int32_t iNbrToRead) ;
int Flash_Write(uint32_t iAddress, uint8_t *buf, uint32_t iNbrToWrite);

int ReadFlashNBtye(uint32_t ReadAddress, uint8_t *ReadBuf, int32_t ReadNum) ;

void WriteFlashOneWord(uint32_t WriteAddress,uint32_t WriteData);
void WriteFlashData(uint32_t WriteAddress, uint8_t data[], uint32_t num);

uint8_t flashReadStr(uint32_t add,uint8_t str[],uint8_t num);
#endif