/**
  ******************************************************************************
  * @file    bsp_pwm_output.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   tim3输出四路pwm bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_pwm_output.h" 

// /**
//  * @brief  配置TIM3复用输出PWM时用到的I/O
//  * @param  无
//  * @retval 无
//  */
//static void TIM3_GPIO_Config(void) 
//{
//  GPIO_InitTypeDef GPIO_InitStructure;

//	/* 设置TIM3CLK 为 72MHZ */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

//  /* GPIOA and GPIOB clock enable */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 

//  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);

//  /*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//}

///**
//  * @brief  配置TIM3输出的PWM信号的模式，如周期、极性、占空比
//  * @param  无
//  * @retval 无
//  */
///*
// * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT 重新计数
// *                    TIMx_CCR(电平发生变化)
// * 信号周期=(TIMx_ARR +1 ) * 时钟周期
// * 占空比=TIMx_CCR/(TIMx_ARR +1)
// */
//static void TIM3_Mode_Config(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;

//	/* PWM信号电平跳变值 */
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
//  TIM_TimeBaseStructure.TIM_Period = 999;       //当定时器从0计数到999，即为1000次，为一个定时周期
//  TIM_TimeBaseStructure.TIM_Prescaler = 0;	    //设置预分频：不预分频，即为72MHz
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频(这里用不到)
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
//  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

//  /* PWM1 Mode configuration: Channel1 */
//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
//  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
//  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //使能通道1
//  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

////  /* PWM1 Mode configuration: Channel2 */
////  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
////  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
////  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //使能通道2
////  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

////  /* PWM1 Mode configuration: Channel3 */
////  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
////  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
////  TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //使能通道3
////  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

////  /* PWM1 Mode configuration: Channel4 */
////  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
////  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
////  TIM_OC4Init(TIM3, &TIM_OCInitStructure);	//使能通道4
////  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
////  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // 使能TIM3重载寄存器ARR

//  /* TIM3 enable counter */
//  TIM_Cmd(TIM3, ENABLE);                   //使能定时器3	
//}


///**
//  * @brief  TIM3 输出PWM信号初始化，只要调用这个函数
//  *         TIM3的四个通道就会有PWM信号输出
//  * @param  无
//  * @retval 无
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
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
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
	u16 CCR_Val; /* PWM信号电平跳变值 */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 	
	if ((clock_div * 655360 / 72) < period ||			/* one tick * 65535 is smaller than period  1*65536/(72000000/clock_div)<period * 10e-7 */
			(clock_div * 10 / 72) > period ||
				clock_div > 0xFFFF) {					/* period is smaller than one tick 1/(72000000/clock_div) >period * 10e-7*/
																								/* there is some conficlt between clock_div and duty_cycle */
		
		return 0;
	}
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
		/* Time base configuration */		 

	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;	//设置时钟分频系数：4分频(这里用不到),即72Mhz
	TIM_TimeBaseStructure.TIM_Prescaler = clock_div - 1;
	TIM_TimeBaseStructure.TIM_Period = period * 72 / 10 / clock_div - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	CCR_Val = TIM_TimeBaseStructure.TIM_Period * duty_cycle / 1000;
	
	timer3_PWM_gpio_config(channel);											 /* config the gpio according to the channel */
	
		/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = CCR_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR_Val时为高电平		}
	

	
	switch (channel) {
		
	case CHANNEL_1:
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //使能通道1
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);		
		break;
	
	case CHANNEL_2:
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);	 //使能通道2
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		break;
	
	case CHANNEL_3:
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //使能通道3
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		break;
	
	case CHANNEL_4:
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);	 //使能通道4
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
		break;
	default:
		return 0;
	}
	
	  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //使能定时器3
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
