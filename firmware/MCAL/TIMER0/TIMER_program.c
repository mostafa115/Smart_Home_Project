/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : TIMER            ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_interface.h"
#include "TIMER_register.h"
#include "TIMER_private.h"
#include "TIMER_config.h"

static void (*TIMER0_pvCallBackFunc) (void) = NULL ;

void Timer0_voidInit(void)
{
		/* Choose Timer Wave Generation Mode */
#if TIMO_MODE == TIM0_NORMAL
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
#elif  TIMO_MODE == TIM0_CTC
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
#elif  TIMO_MODE == TIM0_FAST_PWM
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
#elif  TIMO_MODE == TIM0_PHASE_PWM
	SET_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
	/* set normal if there is no selection*/
#else
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
#endif

	/* Choose Compare Match Output Mode */

#if TIMO_WAVE == TIM0_TOGL_OC0
	SET_BIT(TCCR0,TCCR0_COM00);
	CLR_BIT(TCCR0,TCCR0_COM01);
#elif TIMO_WAVE == TIM0_CLEAR_OC0
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);
#elif TIMO_WAVE == TIM0_SET_OC0
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);
#elif TIMO_WAVE == TIM0_FAST_INVERT_OC0
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);
#elif TIMO_WAVE == TIM0_FAST_NONINVERT_OC0
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);
#elif TIMO_WAVE == TIM0_PHASE_INVERT_OC0
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);
#elif TIMO_WAVE == TIM0_PHASE_NONINVERT_OC0
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);
	/*default is oco diconnected */
#else
	CLR_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);

#endif

	/* Initialize Compare match value
	OCR0 = OCR0_init ;
*/
	/* Prescaler Division by prescaler init
	TCCR0=TCCR0&Prescaler_Mask;
	TCCR0=TCCR0|PRESCALER_init;
	*/
}

u8 Timer0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorStatus = OK ;

	if(Copy_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc ;
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER ;
	}

	return Local_u8ErrorStatus ;
}

void Timer0_voidSetCompMatchValue(u8 Copy_u8CompMatchValue )
{
	OCR0 = Copy_u8CompMatchValue ;
}

void Timer0_voidInterruptEnable(void)
{
	/* Output Compare match interrupt enable */
		SET_BIT(TIMSK,TIMSK_OCIE0);
}

void Timer0_voidSetPrescalerValue(u8 Copy_u8PrescalerValue)
{
	/* Set Prescaler Division by User */
		TCCR0=TCCR0&Prescaler_Mask;
		TCCR0=TCCR0|Copy_u8PrescalerValue;
}

void __vector_15(void)__attribute__((signal));
void __vector_15(void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
	else
	{
		// Do Nothing
	}
}
