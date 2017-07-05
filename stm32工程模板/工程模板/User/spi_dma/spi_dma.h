/**
 * \file  	spi_dam.h   
 * \brief  	use spi to transfer data though dma ,spi_dma.h head file    
 *
 * \version v0.1   
 * \date    2017-6-29  
 * \author  Danphy  
 */


#ifndef __SPI_DMA_H
#define __SPI_DMA_H

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

#define SPI_SEND_BUFF_SIZE 255														/*!< use to define spi send buff size */
#define SPI_RECEIVE_BUFF_SIZE 255													/*!< use to define spi receive buff size */
#define SPI_DR_ADDR (0x40013000 + 0x0c)										/*!< the spi data register */

#define SPI_DMA_RX_CHANNEL DMA1_Channel2									/*!< the SPI RX dma channel */
#define SPI_DMA_TX_CHANNEL DMA1_Channel3									/*!< the SPI_TX dma channel */

#define SEND_ONLY 0																				/*!< dedine the flag SEND ONLY */
#define SEND_RECEIVE 1																		/*!< this definenation means send and receive in the same time */

#define CS_L GPIO_ResetBits(GPIOA, GPIO_Pin_4)						/*!< use to control spi select pin low */
#define CS_H GPIO_SetBits(GPIOA, GPIO_Pin_4)							/*!< use to control spi select pin high */

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
 void spi_dma_init(void);
 
 
 
 /**
 * \brief    : use spi dma to send data
 * \detail   : in this fuction ,if we only want to send data ,we just disable the RX dma ,
 *								in spi master mode , if we want to receive data we have to transfer data . 
 *
 * \attention : we have to use software to select the chip by pull dowm some pin
 * \param[in] :buffer : the pointer point to the date we want to send 
 * \param[in]	:len : the data length
 * \param[in]	:type : SEND_ONLY: 0 :we only send the data.
 *									  	SEND_RECEIVE: we send the data and receive the data,in master mode
 *
 * \retval : 1:success to send the data
 * \retval : 0 the bus is busy.
 * \retval : -1 the len is greater than the SPI_SEND_BUFF_SIZE.
 */
 char spi_dma_send(u8 *buffer, u16 len, u8 type);
 
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
 char spi_read(u8 *rxbuffer, u8 *rx_len);
 
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
 char get_spi_read_data_size(u8 *rx_len);
 
#endif
