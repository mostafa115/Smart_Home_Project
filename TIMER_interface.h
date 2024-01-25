/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : TIMER            ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define 	PRESCALER_1      			1
#define 	PRESCALER_8     			2
#define 	PRESCALER_32     			3
#define 	PRESCALER_64     			4
#define 	PRESCALER_128     			5
#define 	PRESCALER_256    			6
#define 	PRESCALER_1024   			7


#define 	ETERNAL_CLOCK_RISING     	7
#define 	ETERNAL_CLOCK_FALLING    	6

void Timer0_voidInit(void);
void Timer0_voidSetCompMatchValue(u8 Copy_u8CompMatchValue );
void Timer0_voidInterruptEnable(void);
void Timer0_voidSetPrescalerValue(u8 Copy_u8PrescalerValue);
u8 Timer0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));

#endif 


