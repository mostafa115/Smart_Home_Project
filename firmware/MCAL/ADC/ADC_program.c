/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : ADC              ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_register.h"

/* Global Pointer To Function to hold Address of ISR Function */

void (*ADC_pvISRfunc) (void) = NULL ;

/* Global Pointer To Transfer Value Of Reading From ISR function To the APP Layer */

u16 * Global_u16ReadingValue = NULL_POINTER ;

/* Global Variable to prevent user From calling Start conversion function before Conversion time ending */

u8 ADC_u8BusyState = IDLE ;

void ADC_voidInit(void)
{
	/* Set reference voltage */
	/*
	ADMUX &= ADC_Reference_Selection_Mask ;
	ADMUX |= Reference_Selection ;
	 */
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
	/* Activate Left adjust Result */
#if Resolution == bits_8

	SET_BIT(ADMUX,ADMUX_ADLAR);

	/*set 10 bits resolution  */
#elif Resolution == bits_10
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "Wrong Resolution Configuration"
#endif

	/* Set prescaler to divide by 128
	 * Steps : 1 - Clear 3 LSB in ACSRA Register to make sure that they are zero
	 * 		   2 - Oring this register with division factoe added by user
	 * 		    */

	ADCSRA &= ADC_Presc_Mask ;
	ADCSRA |= DIV_Factor ;

	/*Enable peripheral	*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

	/* Setting Conversion Mode */
#if Conversion_Mode == FREE_RUNNING

	/* Clearing ADC interrupt Enable and ADC Auto trigger */

	CLR_BIT(ADCSRA , ADCSRA_ADIE);
	CLR_BIT(ADCSRA , ADCSRA_ADATE);


#elif Conversion_Mode == AUTO_TRIGGER

	/* Setting ADC interrupt Enable and ADC Auto trigger */
	SET_BIT(ADCSRA , ADCSRA_ADEN);
	SET_BIT(ADCSRA , ADCSRA_ADATE);

	/* Setting auto trigger source */
	SFIOR &= ADC_Auto_Trigger_Mask ;
	SFIOR |=  AUTO_TRIGGER ;

#else
#error "Wrong Conversion Mode Configuration"
#endif

}

u16 ADC_u16GetChannelReadingSynch(u8 Copy_u8Channel)
{

	u16 Local_u16ReadingValue = 0 ;

	/* Clear the MUX bits in ADMUX register  */
	ADMUX &= ADC_Channel_Mask ;

	/* Set the required Channel into the MUX bits  */
	ADMUX |= Copy_u8Channel ;
#if Conversion_Mode == FREE_RUNNING

	/* Start Conversion  */
	SET_BIT(ADCSRA, ADCSRA_ADSC);

	/* Polling (busy waiting) until the conversion complete flag is set */

	while( (GET_BIT(ADCSRA,ADCSRA_ADIF)) == 0);

	/* Clear the conversion complete flag */
	SET_BIT(ADCSRA,ADCSRA_ADIF);

	/* If your mode is auto trigger */

#elif Conversion_Mode == AUTO_TRIGGER

	/* Do Nothing  */
#else
#error "Worng Conversion Mode Configuration"
#endif


#if Resolution == bits_8
	/* Read ADCH register if resolution is 256 */
	Local_u16ReadingValue = ADCH ;
#elif Resolution == bits_10
			/* Read ADCH + ADCL registers if resolution is 1024 */
			Local_u16ReadingValue = ADC_Reg ;
#else
#error "Wrong Resolution Configuration "
#endif

	/* Return the reading */
	return Local_u16ReadingValue ;
}

void ADC_voidGetChannelReadingAsynch(u8 Copy_u8Channel , u16 * Copy_u16ReadingValue)
{

	if(ADC_u8BusyState == IDLE)
	{
		/* Initialize Global Pointer To The address of Copy_u16ReadingValue */
		Global_u16ReadingValue = Copy_u16ReadingValue ;

		/* Make ADC Busy in order not to work until being Idle */
		ADC_u8BusyState = BUSY ;

		/* Clear the MUX bits in ADMUX register  */
		ADMUX &= ADC_Channel_Mask ;

		/* Set the required Channel into the MUX bits  */
		ADMUX |= Copy_u8Channel ;

		/* Start Conversion  */
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/* ADC Interrupt Enable */
		SET_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else
	{
		//Do Nothing
	}

}

u8 ADC_u8ADCSetCallBack(void (*Copy_pvISRfunc)(void))
{
	u8 Local_u8ErrorStatus = OK ;

	if(Copy_pvISRfunc != NULL ){
		ADC_pvISRfunc = Copy_pvISRfunc ;
	}
	else {
		Local_u8ErrorStatus = NULL_POINTER ;
	}

	return Local_u8ErrorStatus ;
}


/* ISR of ADC */

void __vector_16(void)   __attribute__((signal));
void __vector_16(void)
{
	if(ADC_pvISRfunc != NULL ){

#if Resolution == bits_8
		/* Read ADCH register if resolution is 256 */
		*Global_u16ReadingValue = ADCH ;
#elif Resolution == bits_10
				/* Read ADCH + ADCL registers if resolution is 1024 */
		*Global_u16ReadingValue = ADC_Reg ;
#else
#error "Wrong Resolution Configuration "
#endif
		ADC_pvISRfunc() ;
	}
	else{
		/* Do Nothing */
	}

	/* Make ADC IDLE To work */
	ADC_u8BusyState = IDLE ;

	/* Disable Conversion Complete Interrupt */
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
}
