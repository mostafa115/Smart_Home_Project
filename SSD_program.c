/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal   *************/
/****************************     Layer  : HAL             *************/
/****************************     swc    : SEVEN_SEGMENT   *************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SSD_interface.h"
#include "DIO_interface.h"

static u8 number = 0;
void SSD_u8SetNumber(u8 Copy_u8Number, ssd_t * Copy_pu8sst){

	number = Copy_u8Number ;
	switch(Copy_u8Number){
	case 0: Copy_u8Number = number0 ;     break ;
	case 1: Copy_u8Number = number1 ;     break ;
	case 2: Copy_u8Number = number2 ;     break ;
	case 3: Copy_u8Number = number3 ;     break ;
	case 4: Copy_u8Number = number4 ;     break ;
	case 5: Copy_u8Number = number5 ;     break ;
	case 6: Copy_u8Number = number6 ;     break ;
	case 7: Copy_u8Number = number7 ;     break ;
	case 8: Copy_u8Number = number8 ;     break ;
	case 9: Copy_u8Number = number9 ;     break ;
	default : break ;
	}
		DIO_u8SetPinValue(Copy_pu8sst -> PORT_0 , Copy_pu8sst -> PIN_0 , !((Copy_u8Number >> 0) & 1 ));
		DIO_u8SetPinValue(Copy_pu8sst -> PORT_1 , Copy_pu8sst -> PIN_1 , !((Copy_u8Number >> 1) & 1 ) );
		DIO_u8SetPinValue(Copy_pu8sst -> PORT_2 , Copy_pu8sst -> PIN_2 , !((Copy_u8Number >> 2) & 1 ));
		DIO_u8SetPinValue(Copy_pu8sst -> PORT_3 , Copy_pu8sst -> PIN_3 , !((Copy_u8Number >> 3) & 1 ));
		DIO_u8SetPinValue(Copy_pu8sst -> PORT_4 , Copy_pu8sst -> PIN_4 , !((Copy_u8Number >> 4) & 1 ));
		DIO_u8SetPinValue(Copy_pu8sst -> PORT_5 , Copy_pu8sst -> PIN_5 , !((Copy_u8Number >> 5) & 1 ));
		DIO_u8SetPinValue(Copy_pu8sst -> PORT_6 , Copy_pu8sst -> PIN_6 , !((Copy_u8Number >> 6) & 1 ));
}


void SSD_u8Enable(ssd_t * Copy_pu8sst){
		DIO_u8SetPinValue(Copy_pu8sst -> EnablePort ,Copy_pu8sst -> EnablePin , DIO_u8PIN_LOW);
}



void SSD_u8Disable(ssd_t * Copy_pu8sst){
		DIO_u8SetPinValue(Copy_pu8sst -> EnablePort ,Copy_pu8sst -> EnablePin , DIO_u8PIN_HIGH);
}
