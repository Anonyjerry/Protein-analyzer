#include "rc522_function.h"
#include "rc522_config.h"
#include "stm32f10x.h"
#include "delay.h"

#define   macRC522_DELAY()  delay_us ( 200 )

/*
 * ��������SPI_RC522_SendByte
 * ����  ����RC522����1 Byte ����
 * ����  ��byte��Ҫ���͵�����
 * ����  : RC522���ص�����
 * ����  ���ڲ�����
 */
void SPI_RC522_SendByte ( u8 byte )
{
    u8 counter;	
    for(counter=0;counter<8;counter++)
    {     
			if ( byte & 0x80 )
					macRC522_MOSI_1 ();
			else 
					macRC522_MOSI_0 ();

			macRC522_DELAY();
		
			macRC522_SCK_0 ();

			macRC522_DELAY();
			 
			macRC522_SCK_1();

			macRC522_DELAY();
			 
			byte <<= 1; 
			
    } 
	
}

/*
 * ��������SPI_RC522_ReadByte
 * ����  ����RC522����1 Byte ����
 * ����  ����
 * ����  : RC522���ص�����
 * ����  ���ڲ�����
 */
u8 SPI_RC522_ReadByte ( void )
{
	u8 counter;
	u8 SPI_Data;


	for(counter=0;counter<8;counter++)
	{
			SPI_Data <<= 1;
	 
			macRC522_SCK_0 ();


		macRC522_DELAY();
		
			if ( macRC522_MISO_GET() == 1)
					SPI_Data |= 0x01;

			macRC522_DELAY();

			macRC522_SCK_1 ();
	
			macRC522_DELAY();
			
	}
	
	return SPI_Data;
	
}

/*
 * ��������ReadRawRC
 * ����  ����RC522�Ĵ���
 * ����  ��ucAddress���Ĵ�����ַ
 * ����  : �Ĵ����ĵ�ǰֵ
 * ����  ���ڲ�����
 */
u8 ReadRawRC ( u8 ucAddress )
{
	u8 ucAddr, ucReturn;
	
	
	ucAddr = ( ( ucAddress << 1 ) & 0x7E ) | 0x80;
	
	macRC522_CS_Enable();
	
	SPI_RC522_SendByte ( ucAddr );
	
	ucReturn = SPI_RC522_ReadByte ();
	
	macRC522_CS_Disable();
	
	
	return ucReturn;
	
	
}

/*
 * ��������WriteRawRC
 * ����  ��дRC522�Ĵ���
 * ����  ��ucAddress���Ĵ�����ַ
 *         ucValue��д��Ĵ�����ֵ
 * ����  : ��
 * ����  ���ڲ�����
 */
void WriteRawRC ( u8 ucAddress, u8 ucValue )
{  
	u8 ucAddr;
	
	
	ucAddr = ( ucAddress << 1 ) & 0x7E;
	
	macRC522_CS_Enable();
	
	SPI_RC522_SendByte ( ucAddr );
	
	SPI_RC522_SendByte ( ucValue );
	
	macRC522_CS_Disable();	

	
}

/*
 * ��������SetBitMask
 * ����  ����RC522�Ĵ�����λ
 * ����  ��ucReg���Ĵ�����ַ
 *         ucMask����λֵ
 * ����  : ��
 * ����  ���ڲ�����
 */
void SetBitMask ( u8 ucReg, u8 ucMask )  
{
    u8 ucTemp;
	
	
    ucTemp = ReadRawRC ( ucReg );
	
    WriteRawRC ( ucReg, ucTemp | ucMask );         // set bit mask
	
	
}

/*
 * ��������ClearBitMask
 * ����  ����RC522�Ĵ�����λ
 * ����  ��ucReg���Ĵ�����ַ
 *         ucMask����λֵ
 * ����  : ��
 * ����  ���ڲ�����
 */
void ClearBitMask ( u8 ucReg, u8 ucMask )  
{
    u8 ucTemp;
	
	
    ucTemp = ReadRawRC ( ucReg );
	
    WriteRawRC ( ucReg, ucTemp & ( ~ ucMask) );  // clear bit mask
	
	
}

/*
 * ��������PcdAntennaOn
 * ����  ���������� 
 * ����  ����
 * ����  : ��
 * ����  ���ڲ�����
 */
void PcdAntennaOn ( void )
{
    u8 uc;
	
	
    uc = ReadRawRC ( TxControlReg );
	
    if ( ! ( uc & 0x03 ) )
			SetBitMask(TxControlReg, 0x03);

		
}


/*
 * ��������PcdAntennaOff
 * ����  ���������� 
 * ����  ����
 * ����  : ��
 * ����  ���ڲ�����
 */
void PcdAntennaOff ( void )
{
  ClearBitMask ( TxControlReg, 0x03 );
}

/*
 * ��������PcdRese
 * ����  ����λRC522 
 * ����  ����
 * ����  : ��
 * ����  ���ⲿ����
 */
void PcdReset ( void )
{
	macRC522_Reset_Disable();
	
	delay_us ( 1 );
	
	macRC522_Reset_Enable();
	
	delay_us ( 1 );
	
	macRC522_Reset_Disable();
	
	delay_us ( 1 );
	
	WriteRawRC ( CommandReg, 0x0f );
	
	while ( ReadRawRC ( CommandReg ) & 0x10 );
	
	delay_us ( 1 );
	
  WriteRawRC ( ModeReg, 0x3D );            //���巢�ͺͽ��ճ���ģʽ ��Mifare��ͨѶ��CRC��ʼֵ0x6363
	
  WriteRawRC ( TReloadRegL, 30 );          //16λ��ʱ����λ    
	WriteRawRC ( TReloadRegH, 0 );			     //16λ��ʱ����λ
	
  WriteRawRC ( TModeReg, 0x8D );				   //�����ڲ���ʱ��������
	
  WriteRawRC ( TPrescalerReg, 0x3E );			 //���ö�ʱ����Ƶϵ��
	
	WriteRawRC ( TxAutoReg, 0x40 );				   //���Ʒ����ź�Ϊ100%ASK	
	
}

/*
 * ��������M500PcdConfigISOType
 * ����  ������RC522�Ĺ�����ʽ
 * ����  ��ucType��������ʽ
 * ����  : ��
 * ����  ���ⲿ����
 */
void M500PcdConfigISOType ( u8 ucType )
{
	if ( ucType == 'A')                     //ISO14443_A
  {
		ClearBitMask ( Status2Reg, 0x08 );
		
    WriteRawRC ( ModeReg, 0x3D );//3F
		
		WriteRawRC ( RxSelReg, 0x86 );//84
		
		WriteRawRC( RFCfgReg, 0x7F );   //4F
		
		WriteRawRC( TReloadRegL, 30 );//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 
		
		WriteRawRC ( TReloadRegH, 0 );
		
		WriteRawRC ( TModeReg, 0x8D );
		
		WriteRawRC ( TPrescalerReg, 0x3E );
		
		delay_us ( 2 );
		
		PcdAntennaOn ();//������
		
   }
 
}

/*
 * ��������PcdComMF522
 * ����  ��ͨ��RC522��ISO14443��ͨѶ
 * ����  ��ucCommand��RC522������
 *         pInData��ͨ��RC522���͵���Ƭ������
 *         ucInLenByte���������ݵ��ֽڳ���
 *         pOutData�����յ��Ŀ�Ƭ��������
 *         pOutLenBit���������ݵ�λ����
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ڲ�����
 */
char PcdComMF522 ( u8 ucCommand, u8 * pInData, u8 ucInLenByte, u8 * pOutData, u32 * pOutLenBit )		
{
    char cStatus = MI_ERR;
    u8 ucIrqEn   = 0x00;
    u8 ucWaitFor = 0x00;
    u8 ucLastBits;
    u8 ucN;
    u32 ul;
	
	
    switch ( ucCommand )
    {
       case PCD_AUTHENT:		//Mifare��֤
          ucIrqEn   = 0x12;		//��������ж�����ErrIEn  ��������ж�IdleIEn
          ucWaitFor = 0x10;		//��֤Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ
          break;
			 
       case PCD_TRANSCEIVE:		//���շ��� ���ͽ���
          ucIrqEn   = 0x77;		//����TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
          ucWaitFor = 0x30;		//Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ�� �����жϱ�־λ
          break;
			 
       default:
         break;
			 
    }
   
    WriteRawRC ( ComIEnReg, ucIrqEn | 0x80 );		//IRqInv��λ�ܽ�IRQ��Status1Reg��IRqλ��ֵ�෴ 
    ClearBitMask ( ComIrqReg, 0x80 );			//Set1��λ����ʱ��CommIRqReg������λ����
    WriteRawRC ( CommandReg, PCD_IDLE );		//д��������
    SetBitMask ( FIFOLevelReg, 0x80 );			//��λFlushBuffer����ڲ�FIFO�Ķ���дָ���Լ�ErrReg��BufferOvfl��־λ�����
    
    for ( ul = 0; ul < ucInLenByte; ul ++ )
		  WriteRawRC ( FIFODataReg, pInData [ ul ] );    		//д���ݽ�FIFOdata
			
    WriteRawRC ( CommandReg, ucCommand );					//д����
   
    
    if ( ucCommand == PCD_TRANSCEIVE )
			SetBitMask(BitFramingReg,0x80);  				//StartSend��λ�������ݷ��� ��λ���շ�����ʹ��ʱ����Ч
    
    ul = 1000;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
		
    do 														//��֤ ��Ѱ���ȴ�ʱ��	
    {
         ucN = ReadRawRC ( ComIrqReg );							//��ѯ�¼��ж�
         ul --;
    } while ( ( ul != 0 ) && ( ! ( ucN & 0x01 ) ) && ( ! ( ucN & ucWaitFor ) ) );		//�˳�����i=0,��ʱ���жϣ���д��������
		
    ClearBitMask ( BitFramingReg, 0x80 );					//��������StartSendλ
		
    if ( ul != 0 )
    {
			if ( ! ( ReadRawRC ( ErrorReg ) & 0x1B ) )			//�������־�Ĵ���BufferOfI CollErr ParityErr ProtocolErr
			{
				cStatus = MI_OK;
				
				if ( ucN & ucIrqEn & 0x01 )					//�Ƿ�����ʱ���ж�
				  cStatus = MI_NOTAGERR;   
					
				if ( ucCommand == PCD_TRANSCEIVE )
				{
					ucN = ReadRawRC ( FIFOLevelReg );			//��FIFO�б�����ֽ���
					
					ucLastBits = ReadRawRC ( ControlReg ) & 0x07;	//�����յ����ֽڵ���Чλ��
					
					if ( ucLastBits )
						* pOutLenBit = ( ucN - 1 ) * 8 + ucLastBits;   	//N���ֽ�����ȥ1�����һ���ֽڣ�+���һλ��λ�� ��ȡ����������λ��
					else
						* pOutLenBit = ucN * 8;   					//�����յ����ֽ������ֽ���Ч
					
					if ( ucN == 0 )		
            ucN = 1;    
					
					if ( ucN > MAXRLEN )
						ucN = MAXRLEN;   
					
					for ( ul = 0; ul < ucN; ul ++ )
					  pOutData [ ul ] = ReadRawRC ( FIFODataReg );   
					
					}
					
      }
			
			else
				cStatus = MI_ERR;   
			
    }
   
   SetBitMask ( ControlReg, 0x80 );           // stop timer now
   WriteRawRC ( CommandReg, PCD_IDLE ); 
		 
		
   return cStatus;
				
}

/*
 * ��������PcdRequest
 * ����  ��Ѱ��
 * ����  ��ucReq_code��Ѱ����ʽ
 *                     = 0x52��Ѱ��Ӧ�������з���14443A��׼�Ŀ�
 *                     = 0x26��Ѱδ��������״̬�Ŀ�
 *         pTagType����Ƭ���ʹ���
 *                   = 0x4400��Mifare_UltraLight
 *                   = 0x0400��Mifare_One(S50)
 *                   = 0x0200��Mifare_One(S70)
 *                   = 0x0800��Mifare_Pro(X))
 *                   = 0x4403��Mifare_DESFire
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdRequest ( u8 ucReq_code, u8 * pTagType )
{
   char cStatus;  
	 u8 ucComMF522Buf [ MAXRLEN ]; 
   u32 ulLen;
	

   ClearBitMask ( Status2Reg, 0x08 );	//����ָʾMIFARECyptol��Ԫ��ͨ�Լ����п�������ͨ�ű����ܵ����
   WriteRawRC ( BitFramingReg, 0x07 );	//	���͵����һ���ֽڵ� ��λ
   SetBitMask ( TxControlReg, 0x03 );	//TX1,TX2�ܽŵ�����źŴ��ݾ����͵��Ƶ�13.56�������ز��ź�

   ucComMF522Buf [ 0 ] = ucReq_code;		//���� ��Ƭ������

   cStatus = PcdComMF522 ( PCD_TRANSCEIVE,	ucComMF522Buf, 1, ucComMF522Buf, & ulLen );	//Ѱ��  
  
   if ( ( cStatus == MI_OK ) && ( ulLen == 0x10 ) )	//Ѱ���ɹ����ؿ����� 
   {    
       * pTagType = ucComMF522Buf [ 0 ];
       * ( pTagType + 1 ) = ucComMF522Buf [ 1 ];
   }
	 
   else
     cStatus = MI_ERR;

   
   return cStatus;
	 	 
}

/*
 * ��������PcdAnticoll
 * ����  ������ײ
 * ����  ��pSnr����Ƭ���кţ�4�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdAnticoll ( u8 * pSnr )
{
    char cStatus;
    u8 uc, ucSnr_check = 0;
    u8 ucComMF522Buf [ MAXRLEN ]; 
	  u32 ulLen;
    

    ClearBitMask ( Status2Reg, 0x08 );		//��MFCryptol Onλ ֻ�гɹ�ִ��MFAuthent����󣬸�λ������λ
    WriteRawRC ( BitFramingReg, 0x00);		//����Ĵ��� ֹͣ�շ�
    ClearBitMask ( CollReg, 0x80 );			//��ValuesAfterColl���н��յ�λ�ڳ�ͻ�����
   
    ucComMF522Buf [ 0 ] = 0x93;	//��Ƭ����ͻ����
    ucComMF522Buf [ 1 ] = 0x20;
   
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, & ulLen);//�뿨Ƭͨ��
	
    if ( cStatus == MI_OK)		//ͨ�ųɹ�
    {
			for ( uc = 0; uc < 4; uc ++ )
			{
         * ( pSnr + uc )  = ucComMF522Buf [ uc ];			//����UID
         ucSnr_check ^= ucComMF522Buf [ uc ];
      }
			
      if ( ucSnr_check != ucComMF522Buf [ uc ] )
				cStatus = MI_ERR;    
				 
    }
    
    SetBitMask ( CollReg, 0x80 );
		
		
    return cStatus;
			
}

/*
 * ��������CalulateCRC
 * ����  ����RC522����CRC16
 * ����  ��pIndata������CRC16������
 *         ucLen������CRC16�������ֽڳ���
 *         pOutData����ż�������ŵ��׵�ַ
 * ����  : ��
 * ����  ���ڲ�����
 */
void CalulateCRC ( u8 * pIndata, u8 ucLen, u8 * pOutData )
{
    u8 uc, ucN;
	
	
    ClearBitMask(DivIrqReg,0x04);
	
    WriteRawRC(CommandReg,PCD_IDLE);
	
    SetBitMask(FIFOLevelReg,0x80);
	
    for ( uc = 0; uc < ucLen; uc ++)
	    WriteRawRC ( FIFODataReg, * ( pIndata + uc ) );   

    WriteRawRC ( CommandReg, PCD_CALCCRC );
	
    uc = 0xFF;
	
    do 
    {
        ucN = ReadRawRC ( DivIrqReg );
        uc --;
    } while ( ( uc != 0 ) && ! ( ucN & 0x04 ) );
		
    pOutData [ 0 ] = ReadRawRC ( CRCResultRegL );
    pOutData [ 1 ] = ReadRawRC ( CRCResultRegM );
			
}

/*
 * ��������PcdSelect
 * ����  ��ѡ����Ƭ
 * ����  ��pSnr����Ƭ���кţ�4�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdSelect ( u8 * pSnr )
{
    char ucN;
    u8 uc;
	  u8 ucComMF522Buf [ MAXRLEN ]; 
    u32  ulLen;
    
    
    ucComMF522Buf [ 0 ] = PICC_ANTICOLL1;
    ucComMF522Buf [ 1 ] = 0x70;
    ucComMF522Buf [ 6 ] = 0;
	
    for ( uc = 0; uc < 4; uc ++ )
    {
    	ucComMF522Buf [ uc + 2 ] = * ( pSnr + uc );
    	ucComMF522Buf [ 6 ] ^= * ( pSnr + uc );
    }
		
    CalulateCRC ( ucComMF522Buf, 7, & ucComMF522Buf [ 7 ] );
  
    ClearBitMask ( Status2Reg, 0x08 );

    ucN = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, & ulLen );
    
    if ( ( ucN == MI_OK ) && ( ulLen == 0x18 ) )
      ucN = MI_OK;  
    else
      ucN = MI_ERR;    

		
    return ucN;		
}

/*
 * ��������PcdAuthState
 * ����  ����֤��Ƭ����
 * ����  ��ucAuth_mode��������֤ģʽ
 *                     = 0x60����֤A��Կ
 *                     = 0x61����֤B��Կ
 *         u8 ucAddr�����ַ
 *         pKey������
 *         pSnr����Ƭ���кţ�4�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdAuthState ( u8 ucAuth_mode, u8 ucAddr, u8 * pKey, u8 * pSnr )
{
    char cStatus;
	  u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;
    
	
    ucComMF522Buf [ 0 ] = ucAuth_mode;
    ucComMF522Buf [ 1 ] = ucAddr;
	
    for ( uc = 0; uc < 6; uc ++ )
	    ucComMF522Buf [ uc + 2 ] = * ( pKey + uc );   
	
    for ( uc = 0; uc < 6; uc ++ )
	    ucComMF522Buf [ uc + 8 ] = * ( pSnr + uc );   

    cStatus = PcdComMF522 ( PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, & ulLen );
	
    if ( ( cStatus != MI_OK ) || ( ! ( ReadRawRC ( Status2Reg ) & 0x08 ) ) )
      cStatus = MI_ERR;   
    		
    return cStatus;			
}

/*
 * ��������PcdWrite
 * ����  ��д���ݵ�M1��һ��
 * ����  ��u8 ucAddr�����ַ
 *         pData��д������ݣ�16�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdWrite ( u8 ucAddr, u8 * pData )
{
    char cStatus;
	  u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;
     
    
    ucComMF522Buf [ 0 ] = PICC_WRITE;
    ucComMF522Buf [ 1 ] = ucAddr;
	
    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
 
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
      cStatus = MI_ERR;   
        
    if ( cStatus == MI_OK )
    {
			//memcpy(ucComMF522Buf, pData, 16);
      for ( uc = 0; uc < 16; uc ++ )
			  ucComMF522Buf [ uc ] = * ( pData + uc );  
			
      CalulateCRC ( ucComMF522Buf, 16, & ucComMF522Buf [ 16 ] );

      cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 18, ucComMF522Buf, & ulLen );
			
			if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
        cStatus = MI_ERR;   
			
    } 	
    return cStatus;
	
}

/*
 * ��������PcdRead
 * ����  ����ȡM1��һ������
 * ����  ��u8 ucAddr�����ַ
 *         pData�����������ݣ�16�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdRead ( u8 ucAddr, u8 * pData )
{
    char cStatus;
	  u8 uc, ucComMF522Buf [ MAXRLEN ]; 
    u32 ulLen;
    

    ucComMF522Buf [ 0 ] = PICC_READ;
    ucComMF522Buf [ 1 ] = ucAddr;
	
    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
   
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );
	
    if ( ( cStatus == MI_OK ) && ( ulLen == 0x90 ) )
    {
			for ( uc = 0; uc < 16; uc ++ )
        * ( pData + uc ) = ucComMF522Buf [ uc ];   
    }
		
    else
      cStatus = MI_ERR;   		
    return cStatus;
}

/*
 * ��������PcdHalt
 * ����  �����Ƭ��������״̬
 * ����  ����
 * ����  : ״ֵ̬
 *         = MI_OK���ɹ�
 * ����  ���ⲿ����
 */
char PcdHalt( void )
{
	u8 ucComMF522Buf [ MAXRLEN ]; 
	u32  ulLen;
  

  ucComMF522Buf [ 0 ] = PICC_HALT;
  ucComMF522Buf [ 1 ] = 0;
	
  CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
 	PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

  return MI_OK;
	
}

void IC_CMT ( u8 * UID, u8 * KEY, u8 RW, u8 * Dat )
{
  u8 ucArray_ID [ 4 ] = { 0 };//�Ⱥ���IC�������ͺ�UID(IC�����к�)
  
	
  PcdRequest ( 0x52, ucArray_ID );//Ѱ��

  PcdAnticoll ( ucArray_ID );//����ײ
  
  PcdSelect ( UID );//ѡ����
  
  PcdAuthState ( 0x60, 0x10, KEY, UID );//У��
	

	if ( RW )//��дѡ��1�Ƕ���0��д
    PcdRead ( 0x10, Dat );
   
   else 
     PcdWrite ( 0x10, Dat );

   PcdHalt (); 
}



