/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : ADC              ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#define   ADC0             0
#define   ADC1             1
#define   ADC2             2
#define   ADC3             3
#define   ADC4             4
#define   ADC5             5
#define   ADC6             6
#define   ADC7             7

#define  AREF              0
#define  AVCC              64
#define  Internal		   192


void ADC_voidInit(void);

u16 ADC_u16GetChannelReadingSynch(u8 Copy_u8Channel);

void ADC_voidGetChannelReadingAsynch(u8 Copy_u8Channel , u16 * Copy_u16ReadingValue);

u8 ADC_u8ADCSetCallBack(void (*Copy_pvISRfunc)(void));

#endif
