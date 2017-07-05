/**
  ******************************************************************************
  * @file    bsp_pwm_output.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   tim3�����·pwm bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_pwm_output.h" 

// /**
//  * @brief  ����TIM3�������PWMʱ�õ���I/O
//  * @param  ��
//  * @retval ��
//  */
//static void TIM3_GPIO_Config(void) 
//{
//  GPIO_InitTypeDef GPIO_InitStructure;

//	/* ����TIM3CLK Ϊ 72MHZ */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

//  /* GPIOA and GPIOB clock enable */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 

//  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);

//  /*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//}

///**
//  * @brief  ����TIM3�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
//  * @param  ��
//  * @retval ��
//  */
///*
// * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT ���¼���
// *                    TIMx_CCR(��ƽ�����仯)
// * �ź�����=(TIMx_ARR +1 ) * ʱ������
// * ռ�ձ�=TIMx_CCR/(TIMx_ARR +1)
// */
//static void TIM3_Mode_Config(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;

//	/* PWM�źŵ�ƽ����ֵ */
// 	u16 CCR1_Val = 500;        
//// 	u16 CCR2_Val = 375;
//// 	u16 CCR3_Val = 250;
//// 	u16 CCR4_Val = 125;

///* ----------------------------------------------------------------------- 
//    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50%
//    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR+1)* 100% = 37.5%
//    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR+1)* 100% = 25%
//    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR+1)* 100% = 12.5%
//  ----------------------------------------------------------------------- */

//  /* Time base configuration */		 
//  TIM_TimeBaseStructure.TIM_Period = 999;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
//  TIM_TimeBaseStructure.TIM_Prescaler = 0;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
//  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

//  /* PWM1 Mode configuration: Channel1 */
//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
//  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
//  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��1
//  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

////  /* PWM1 Mode configuration: Channel2 */
////  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
////  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
////  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //ʹ��ͨ��2
////  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

////  /* PWM1 Mode configuration: Channel3 */
////  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
////  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
////  TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��3
////  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

////  /* PWM1 Mode configuration: Channel4 */
////  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
////  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
////  TIM_OC4Init(TIM3, &TIM_OCInitStructure);	//ʹ��ͨ��4
////  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
////  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR

//  /* TIM3 enable counter */
//  TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3	
//}


///**
//  * @brief  TIM3 ���PWM�źų�ʼ����ֻҪ�����������
//  *         TIM3���ĸ�ͨ���ͻ���PWM�ź����
//  * @param  ��
//  * @retval ��
//  */
//void TIM3_PWM_Init(void)
//{
//	TIM3_GPIO_Config();
//	TIM3_Mode_Config();	
//}



/**
 * \brief    :use to config pwm output gpio according to the channel about timer3 
 *
 * \param[in] channel :config the pwm channel
 * \retval : none
 */
static void timer3_PWM_gpio_config(u8 channel)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	switch (channel) {
	case CHANNEL_1:																								/* this case config channel 1 */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

		/*GPIOA Configuration: TIM3 channel 1  as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;
	
	
	case CHANNEL_2: 																							/* this case config channel 2 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

		/*GPIOA Configuration: TIM3 channel  2 as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;
	
	case CHANNEL_3: 																							/* this case config channel 3 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

		/*GPIOA Configuration: TIM3 channel 3 as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
		GPIO_Init(GPIOB, &GPIO_InitStructure);		
		break;
	
	case CHANNEL_4:																								/* this case config channel 4 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

		/*GPIOA Configuration: TIM3 channel 3 as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
		GPIO_Init(GPIOB, &GPIO_InitStructure);		
		break;
	
	default: 
		return ;	
		break;
	}
}

/**
 * \brief    :TIM3_PWM_Config use to config the timer3 pwm output 
 * \detail   :set the timerbase the gpio and the channel to config the pwm output 
 *
 * \param[in] channel :config the pwm channel
 * \param[in]:period : the pwm period unit 0.1us
 * \param[in]:duty_cycle: this parameter indicate the duty cycle ,this parameter should be 1~1000,unit is 0.1% 
 * \param[in]:clock_div: timer3 division this parameter decide the timer division  the timer frequence is 72Mhz/clock_div
 * \retval : 0: failure to config the timer pwm output,there is the confilct between clock_div andperiod 
						 1: success to config the timer pwm output
 */
u8 timer3_PWM_comfig(u8 channel, u32 period, u16 clock_div, u16 duty_cycle) 
{
	

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	u16 CCR_Val; /* PWM�źŵ�ƽ����ֵ */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 	
	if ((clock_div * 655360 / 72) < period ||			/* one tick * 65535 is smaller than period  1*65536/(72000000/clock_div)<period * 10e-7 */
			(clock_div * 10 / 72) > period ||
				clock_div > 0xFFFF) {					/* period is smaller than one tick 1/(72000000/clock_div) >period * 10e-7*/
																								/* there is some conficlt between clock_div and duty_cycle */
		
		return 0;
	}
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
		/* Time base configuration */		 

	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;	//����ʱ�ӷ�Ƶϵ����4��Ƶ(�����ò���),��72Mhz
	TIM_TimeBaseStructure.TIM_Prescaler = clock_div - 1;
	TIM_TimeBaseStructure.TIM_Period = period * 72 / 10 / clock_div - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	CCR_Val = TIM_TimeBaseStructure.TIM_Period * duty_cycle / 1000;
	
	timer3_PWM_gpio_config(channel);											 /* config the gpio according to the channel */
	
		/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = CCR_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR_ValʱΪ�ߵ�ƽ		}
	

	
	switch (channel) {
		
	case CHANNEL_1:
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��1
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);		
		break;
	
	case CHANNEL_2:
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��2
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		break;
	
	case CHANNEL_3:
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��3
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		break;
	
	case CHANNEL_4:
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��4
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
		break;
	default:
		return 0;
	}
	
	  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3
	return 1;
}

/**
 * \brief    :use to config pwm output gpio according to the channel about timer3 
 *
 * \param[in] channel :config the pwm channel
 * \param[in]:duty_cycle: this parameter indicate the duty cycle ,this parameter should be 1~1000,unit is 0.1% 
 * \retval : none
 */
 void timer3_PWM_set_duty_cycle(u8 channel, u16 duty_cycle)
{
	switch (channel) {
	case CHANNEL_1: 
		TIM3->CCR1 = TIM3->ARR * duty_cycle/1000;
		break;
	
	case CHANNEL_2: 
		TIM3->CCR2 = TIM3->ARR * duty_cycle/1000;
		break;
	
	case CHANNEL_3: 
		TIM3->CCR3 = TIM3->ARR * duty_cycle/1000;
		break;
	
	case CHANNEL_4:
		TIM3->CCR4 = TIM3->ARR * duty_cycle/1000;
		break;
	
	default: 
		
		break;
	
	}
}

/*********************************************END OF FILE**********************/
