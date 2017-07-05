/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_pwm_output.h" 
#include "spi_dma.h"

u8 testbuff[0xFF]; 												/* this buff is used to test */
u8 testbuff2[0xFF];
u16 i, j;


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	u8 len = 0;
	for (i = 0; i<0xFF; i++) {
		
		testbuff[i] = i;
	}
	spi_dma_init();
	

	  /* add your code here ^_^. */

	while (1) {
		spi_dma_send(testbuff, 255, SEND_ONLY);
	}	

}

/*********************************************END OF FILE**********************/

