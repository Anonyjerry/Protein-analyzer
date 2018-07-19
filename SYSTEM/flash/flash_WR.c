
#include "flash_WR.h"
#include "stm32f10x.h"
#include "stm32f10x_flash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

//对Flash操作，主要应对于标定系统


//STM32F103RB ????????,???   
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;      //Flash??????  


uint8_t  flashReadStr(uint32_t add,uint8_t str[],uint8_t num)
{
	uint8_t Temp_Data[] ="" ;
	static uint8_t tmp[] ="" ;
	unsigned char Temp = 0; 
  int ReadNum = 0;
	int i =0;
	int n =0;
	ReadNum =ReadFlashNBtye (10, Temp_Data,num*2); 
  Temp = (unsigned char)ReadNum;  
	if(Temp>0)
	{
		for(i=0;i<num*2;i++)
		{
			tmp[n++]=Temp_Data[i++];
		}
		memcpy(str,tmp,n);
		return 1;
	}
	else {return 0;}
	
	//return tmp;
}

uint16_t Flash_Write_Without_check(uint32_t iAddress, uint8_t *buf, uint16_t iNumByteToWrite) {
    uint16_t i;
    volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
    i = 0;
    
//    FLASH_UnlockBank1();
    while((i < iNumByteToWrite) && (FLASHStatus == FLASH_COMPLETE))
    {
      FLASHStatus = FLASH_ProgramHalfWord(iAddress, *(uint16_t*)buf);
      i = i+2;
      iAddress = iAddress + 2;
      buf = buf + 2;
    }
    
    return iNumByteToWrite;
}


/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @note   This function can be used for all STM32F10x devices.
  * @param  Address: specifies the address to be programmed.
  * @param  buf: specifies the data to be programmed.
  * @param  iNbrToWrite: the number to read from flash
  * @retval if success return the number to write, without error
  *  
  */
int Flash_Read(uint32_t iAddress, uint8_t *buf, int32_t iNbrToRead) {
        int i = 0;
        while(i < iNbrToRead ) {
           *(buf + i) = *(__IO uint8_t*) iAddress++;
           i++;
        }
        return i;
}


/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @note   This function can be used for all STM32F10x devices.
  * @param  Address: specifies the address to be programmed.
  * @param  buf: specifies the data to be programmed.
  * @param  iNbrToWrite: the number to write into flash
  * @retval if success return the number to write, -1 if error
  *  
  */
int Flash_Write(uint32_t iAddress, uint8_t *buf, uint32_t iNbrToWrite) 
	{
                /* Unlock the Flash Bank1 Program Erase controller */
        uint32_t secpos;
        uint32_t iNumByteToWrite = iNbrToWrite;
				uint16_t secoff;
				uint16_t secremain;  
				uint16_t i = 0;    
        uint8_t tmp[FLASH_PAGE_SIZE];
        
        FLASH_UnlockBank1();
				secpos=iAddress & (~(FLASH_PAGE_SIZE -1 )) ;//???? 
				secoff=iAddress & (FLASH_PAGE_SIZE -1);     //???????
				secremain=FLASH_PAGE_SIZE-secoff;           //???????? 
		{
			volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
		
        
        
        if(iNumByteToWrite<=secremain) secremain = iNumByteToWrite;//???4096???
       
        while( 1 ) 
					{
            Flash_Read(secpos, tmp, FLASH_PAGE_SIZE);   //??????
            for(i=0;i<secremain;i++) 
						{       //????
							if(tmp[secoff+i]!=0XFF)break;       //???? 
						}
            if(i<secremain) 
							{  //????
                FLASHStatus = FLASH_ErasePage(secpos); //??????
                if(FLASHStatus != FLASH_COMPLETE)
                  return -1;
                for(i=0;i<secremain;i++) {   //??
                        tmp[i+secoff]=buf[i];   
                }
                Flash_Write_Without_check(secpos ,tmp ,FLASH_PAGE_SIZE);//??????  
              }
							else {
                Flash_Write_Without_check(iAddress,buf,secremain);//???????,??????????.
              }
            
            if(iNumByteToWrite==secremain) //?????
                break;
            else {
                secpos += FLASH_PAGE_SIZE;
                secoff = 0;//?????0 
                buf += secremain;  //????
                iAddress += secremain;//?????    
                iNumByteToWrite -= secremain;  //?????
                if(iNumByteToWrite>FLASH_PAGE_SIZE) secremain=FLASH_PAGE_SIZE;//??????????
                else secremain = iNumByteToWrite;  //??????????
            }
            
         }
			 }
        FLASH_LockBank1();
        return iNbrToWrite; 
}
	


/****************************************************************  
*Name:      ReadFlashNBtye   
*Other:       
****************************************************************/  
int ReadFlashNBtye(uint32_t ReadAddress, uint8_t *ReadBuf, int32_t ReadNum)   
{  
        int DataNum = 0; 
				uint32_t ReadAdd = 0;
        ReadAddress = (uint32_t)STARTADDR + ReadAddress;   
        while(DataNum < ReadNum)   
        {  
          *(ReadBuf + DataNum) = *(__IO uint8_t*) ReadAddress++;  
					 
           DataNum++;  
        }  
        return DataNum;  
}  

  
/****************************************************************  
*Name:      WriteFlashOneWord  
*Other:     
****************************************************************/  
  
void WriteFlashOneWord(uint32_t WriteAddress,uint32_t WriteData)  
{  
    FLASH_UnlockBank1();  
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);   
    FLASHStatus = FLASH_ErasePage(STARTADDR);  
  
    if(FLASHStatus == FLASH_COMPLETE)  
    {  
        FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress, *(uint16_t*)WriteData);    //flash.c ?API??   
    }  
    FLASH_LockBank1();  
}   


void WriteFlashData(uint32_t WriteAddress, uint8_t data[], uint32_t num)
{
    uint32_t i = 0;
    uint16_t temp = 0;

    FLASH_UnlockBank1();    //??flash
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 

    FLASHStatus = 1;        //?????????
    FLASHStatus = FLASH_ErasePage(STARTADDR);//????
    if(FLASHStatus == FLASH_COMPLETE)//flash????
    {
        FLASHStatus = 1;    //?????????
        for(i=0; i<num; i++)
        {
            temp = (uint16_t)data[i];
            FLASHStatus = FLASH_ProgramHalfWord(STARTADDR+WriteAddress+i*2, temp);//16
        }
    }

    FLASHStatus = 1;    //?????????

    FLASH_LockBank1();  //??flash
} 







