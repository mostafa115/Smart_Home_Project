/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : TIMER            ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/* Initialize Prescaler :
 * 				options :
 * 						1-PRESCALER_1
 * 						2-PRESCALER_8
 * 						3-PRESCALER_64
 * 						4-PRESCALER_256
 * 						5-PRESCALER_1024
 */
#define PRESCALER_init   PRESCALER_8

/* Initialize Compare Match Value :
 * 						 Dependent on Your calculations
 */
#define OCR0_init        125

/*Choose CTC Mode :
 * 						   options :
 * 						   			1-TIM0_NORMAL.
 * 						   			2-TIM0_CTC.
 * 						   			3-TIM0_FAST_PWM.
 * 						   			4-TIM0_PHASE_PWM.
 * */

#define TIMO_MODE  TIM0_CTC

/* Choose Waveform Generation Mode :
 * 						   options :
 * 						   			1-TIM0_TOGL_OC0.
 * 						   			2-TIM0_SET_OC0.
 * 						   			3-TIM0_CLR_OC0.
 * 						   			4-TIM0_FAST_INVERT_OC0
 * 						   			5-TIM0_FAST_NONINVERT_OC0
 * 						   			6-TIM0_PHASE_INVERT_OC0
 * 						   			7-TIM0_PHASE_NONINVERT_OC0
 * 						   			8-TIM0_Default -> Make OCO Disconnected.
 * */

#define TIMO_WAVE   TIM0_SET_OC0

#endif
