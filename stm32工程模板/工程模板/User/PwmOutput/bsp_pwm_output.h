#ifndef __PWM_OUTPUT_H
#define	__PWM_OUTPUT_H

#include "stm32f10x.h"

void TIM3_PWM_Init(void);

#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define CHANNEL_4 4

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
u8 timer3_PWM_comfig(u8 channel, u32 period, u16 clock_div, u16 duty_cycle);


/**
 * \brief    :use to config pwm output gpio according to the channel about timer3 
 *
 * \param[in] channel :config the pwm channel
 * \retval : none
 */
static void timer3_PWM_gpio_config(u8 channel);


/**
 * \brief    :use to config pwm output gpio according to the channel about timer3 
 *
 * \param[in] channel :config the pwm channel
 * \param[in]:duty_cycle: this parameter indicate the duty cycle ,this parameter should be 1~1000,unit is 0.1% 
 * \retval : none
 */
 void timer3_PWM_set_duty_cycle(u8 channel, u16 duty_cycle);

#endif /* __PWM_OUTPUT_H */

