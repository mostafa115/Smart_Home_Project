/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : TIMER            ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define 	Prescaler_Mask    				0b11111000

#define 	TIM0_NORMAL       				10
#define 	TIM0_CTC          				20
#define	 	TIM0_FAST_PWM     				30
#define 	TIM0_PHASE_PWM    				40

/* non pwm modes */
#define 	TIM0_TOGL_OC0        			0
#define 	TIM0_SET_OC0         			1
#define 	TIM0_CLR_OC0         			2
#define     TIM0_Default                    200

/*  pwm modes */
#define 	TIM0_FAST_INVERT_OC0           	3
#define 	TIM0_FAST_NONINVERT_OC0        	4

#define 	TIM0_PHASE_INVERT_OC0          	5
#define 	TIM0_PHASE_NONINVERT_OC0       	6

#endif
