/**
 * \file  	spi_dam.c   
 * \brief  	use spi to transfer data though dma     
 *
 * \version v0.1   
 * \date    2017-6-29  
 * \author  Danphy  
 */
#include "spi_dma.h"  

static u8 g_spi_send_buff[SPI_SEND_BUFF_SIZE] = {0};				 /*use to save the spi send data */
static u8 g_spi_receive_buff[SPI_RECEIVE_BUFF_SIZE] = {0};	 /* use to save the spi receive data */
static u16 g_receive_num = 0;															 /* use to define how many data will put into g_spi_receive_buff */

/**
 * \brief    : use to init spi and dma
 * \detail   : init spi1 GPIO DMA RCC ,spi is in master mode. the dma should not enable ,we should enable when we try to send data or receive data
 * \attention :do not cs when the spi is initting, because dma data size at least 1 size data, the 1 size data will push
 * \param[in]:
 * \param[in]:
 * \param[in]:
 *
 * \retval : none 
 * \retval :
 */
 void spi_dma_init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
  
  /* Enable SPI1 and GPIO clocks */
  /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO, 
       SPI_FLASH_SPI_MISO_GPIO, SPI_FLASH_SPI_DETECT_GPIO 
       and SPI_FLASH_SPI_SCK_GPIO Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);

  /*!< SPI_FLASH_SPI Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
 
  
  /*!< Configure SPI_FLASH_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	/**************************************************
	*conifg the TX dma 
	**************************************************/
	DMA_DeInit(SPI_DMA_TX_CHANNEL);      

	/*开启DMA时钟*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = SPI_DR_ADDR; 

	/*内存地址(要传输的变量的指针)*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_spi_send_buff;

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST ;	

	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = 1;

	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 

	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	

	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 

	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
	//qDMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 

	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium ;  

	/*禁止内存到内存的传输	*/
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	/*配置DMA1的4通道*/		   
	DMA_Init(SPI_DMA_TX_CHANNEL, &DMA_InitStructure); 

	/* we should not enable dma . we should enable dma when the we try to send the data */
	DMA_Cmd (SPI_DMA_TX_CHANNEL, ENABLE);					
	//DMA_ITConfig(USART2_DMA_CHAN_TX, DMA_IT_TC, ENABLE);  //配置DMA发送完成后产生中断
	
	
	
	/**************************************************
	*conifg the RX dma 
	**************************************************/
	DMA_DeInit(SPI_DMA_RX_CHANNEL);      

	/*开启DMA时钟*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = SPI_DR_ADDR; 

	/*内存地址(要传输的变量的指针)*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_spi_receive_buff;

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC ;	

	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = SPI_RECEIVE_BUFF_SIZE;

	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 

	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	

	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 

	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
	//qDMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 

	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium ;  

	/*禁止内存到内存的传输	*/
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	/*配置DMA1的4通道*/		   
	DMA_Init(SPI_DMA_RX_CHANNEL, &DMA_InitStructure); 	   
	
	/* we should not enable dma . we should enable dma when the we try to receive the data */
	//DMA_Cmd (SPI_DMA_RX_CHANNEL, ENABLE);					
	//DMA_ITConfig(USART2_DMA_CHAN_TX, DMA_IT_TC, ENABLE);  //配置DMA发送完成后产生中断

  /* SPI1 configuration */
  // W25X16: data input on the DIO pin is sampled on the rising edge of the CLK. 
  // Data on the DO and DIO pins are clocked out on the falling edge of CLK.
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);

  /* Enable SPI1  */
  SPI_Cmd(SPI1, ENABLE);
}


 /**
 * \brief    : use spi dma to send data
 * \detail   : in this fuction ,if we only want to send data ,we just disable the RX dma ,
 *								in spi master mode , if we want to receive data we have to transfer data . 
 *
 * \param[in] :buffer : the pointer point to the date we want to send 
 * \param[in]	:len : the data length
 * \param[in]	:type : this parameter should be:
 *										SEND_ONLY: 0 :we only send the data.
 *									  	SEND_RECEIVE: we send the data and receive the data,in master mode
 *
 * \retval : 1:success to send the data
 * \retval : 0 the bus is busy.
 * \retval : -1 the len is greater than the SPI_SEND_BUFF_SIZE.
 */
 char spi_dma_send(u8 *buffer, u16 len, u8 type)
{

	
	if (DMA_GetFlagStatus(DMA1_FLAG_TC3) != RESET) { 																		/* dma is busy, return 0 */
		
		DMA_ClearFlag(DMA1_FLAG_TC3);																											/* clear dma transmit complete flag */ 
		if (len <= SPI_SEND_BUFF_SIZE) {
				
			if (!type) {
				
				DMA_Cmd (SPI_DMA_RX_CHANNEL, DISABLE);																				/* close the dma rx transfer */
			} else {
				
				DMA_SetCurrDataCounter(SPI_DMA_RX_CHANNEL, len);																	
				DMA_Cmd (SPI_DMA_RX_CHANNEL, ENABLE);																					/* open the dma rx transfer */
				g_receive_num = len ;																													/* put the len to the gobal parameter g_receive_num */
			}
			memcpy(g_spi_send_buff, buffer, len);				           													/* copy the send data to the g_DMA_tx_buffer */
			DMA_Cmd (SPI_DMA_TX_CHANNEL, DISABLE);	
			DMA_SetCurrDataCounter(SPI_DMA_TX_CHANNEL, len);
			DMA_Cmd (SPI_DMA_TX_CHANNEL, ENABLE);	
			
			return 1;																																				/* success to config spi and dma  */
			
		} else {																																					/* the len is greater than SPI_SEND_BUFF_SIZE */
			
			
			if (type) {																																			/* disable the rx spi dma */
				
			DMA_Cmd (SPI_DMA_RX_CHANNEL, ENABLE);			
			}

			return (char)-1;
		}
	} else {
		
		return 0;																																					/* the dma spi haven't transmit finish yet */
	}
	
}


 /**
 * \brief    : read the data from g_spi_receive_buff,
 * \detail   : 
 *
 * \attention:we have to use fuction(spi_dma_send) before we use this fuction
 *	 
 * \param[out]: *buffer : a pointer point to the buffer where we want to save the data	
 * \param[in\out]: *len : a pointer point to the len  the max we can receive ,and return the num we actually read
 *
 * \retval : 1: success to read the data and the dma transmit complete.
 * \retval : 0: we can get some data but the dma transmit haven't compelete.
 * \retval : -1:there is no data in the buffer, the dma channel is disable 
 */
 char spi_read(u8 *rxbuffer, u8 *rx_len)
{
	if (SPI_DMA_RX_CHANNEL->CCR & DMA_CCR1_EN) { 													/* SPI_DMA_RX_CHANNEL is ENABLE */
		
		if (DMA_GetFlagStatus(DMA1_FLAG_TC2) == SET) {											/* dma receive compelete */
			
			if (*rx_len > g_receive_num) {																		/* we can receive all the data that we can get */
				
				memcpy(rxbuffer, g_spi_receive_buff, g_receive_num);
				*rx_len  = g_receive_num;																				/* change the g_receive_num */
				
				} else {                                                         //todo : if we do not have enough place to store data, we just abadon it for now,
																																				//        later we have to fix it
				
				memcpy(rxbuffer, g_spi_receive_buff, *rx_len);
			}
			
			DMA_ClearFlag(DMA1_FLAG_TC2);																			/* clear the DMA1_FLAG_TC2 flag */
			DMA_Cmd(SPI_DMA_RX_CHANNEL, DISABLE);															/* disable the SPI_DMA_RX_CHANNEL */
			
			return 1 ;																												/* success to read the data from g_spi_receive_buff */
			
		} else {																														/* dma receive haven't compelete */
			
			memcpy(rxbuffer, g_spi_receive_buff, 
												g_receive_num - DMA_GetCurrDataCounter(SPI_DMA_RX_CHANNEL));/* read the data that wecan get from buffer */
			return 0;
		}
		
	} else {																															/* SPI_DMA_RX_CHANNEL is DISABLE */
		
		*rx_len = 0;
		return (char)-1;
	}

}

/**
 * \brief    : get how many data we can read in the g_spi_receive_buff
 * \detail   : 
 *
 * \attention:we have to use fuction(spi_dma_send) before we use this fuction
 *	 
 * \param[out]: *len : return how many bytes we can read now
 *
 * \retval : 1: dma transmit complete, return the num of the data we can read in the buffer.
 * \retval : 0: dma transmit do not complete ,return how many data we can read now
 * \retval : -1:the dma rx channel is diable
 */
 char get_spi_read_data_size(u8 *rx_len)
{
	if (SPI_DMA_RX_CHANNEL->CCR & DMA_CCR1_EN) { 													/* SPI_DMA_RX_CHANNEL is ENABLE */
		
		if (DMA_GetFlagStatus(DMA1_FLAG_TC2) == SET) {											/* dma receive compelete */
			
			*rx_len = g_receive_num;
			return 1;
			
		} else {			
																																				/* dma receive haven't compelete */
			*rx_len = g_receive_num - DMA_GetCurrDataCounter(SPI_DMA_RX_CHANNEL);
			return 0;
		}
		
	} else {																															/* SPI_DMA_RX_CHANNEL is DISABLE */
		
		*rx_len = 0;
		return (char)-1;
	}
}
