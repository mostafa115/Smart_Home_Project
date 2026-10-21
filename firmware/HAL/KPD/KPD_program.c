/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : HAL              ************/
/****************************     swc    : KEYPAD           ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"

u8 KPD_u8GetPressedKey(void){

	u8 Local_u8PressedKey = KPD_No_Pressed_Key ;

	u8 Local_u8ColumnIdx , Local_u8RowIdx , Local_u8_PinState ;

	static u8 KPD_ARR[ROW_NUM][COLUMN_NUM]   = KPD_ARR_VAL ;

	static u8 KPD_u8COLUMNARR[COLUMN_NUM] = {KPD_COLUMN0_PIN , KPD_COLUMN1_PIN , KPD_COLUMN2_PIN , KPD_COLUMN3_PIN } ;

	static u8 KPD_u8ROWARR[ROW_NUM] = {KPD_ROW0_PIN , KPD_ROW1_PIN , KPD_ROW2_PIN , KPD_ROW3_PIN } ;

	for(Local_u8ColumnIdx = 0 ; Local_u8ColumnIdx < COLUMN_NUM ; Local_u8ColumnIdx ++){

		/* Activate Current Column */

		DIO_u8SetPinValue(KPD_PORT , KPD_u8COLUMNARR[Local_u8ColumnIdx] , DIO_u8PIN_LOW) ;

		for(Local_u8RowIdx = 0 ; Local_u8RowIdx < ROW_NUM ; Local_u8RowIdx ++){

			/* Read the Current Row */

			DIO_u8GetPinValue(KPD_PORT , KPD_u8ROWARR[Local_u8RowIdx], &Local_u8_PinState) ;

			/* check if switch presseed */

			if( DIO_u8PIN_LOW == Local_u8_PinState ){

				Local_u8PressedKey = KPD_ARR[Local_u8RowIdx][Local_u8ColumnIdx] ;

				/* Polling (busy waiting ) until the key is released */
				while(Local_u8_PinState == DIO_u8PIN_LOW){

					DIO_u8GetPinValue(KPD_PORT , KPD_u8ROWARR[Local_u8RowIdx], &Local_u8_PinState) ;
				}
				/* Deactivate Current Column */
					DIO_u8SetPinValue(KPD_PORT , KPD_u8COLUMNARR[Local_u8ColumnIdx] , DIO_u8PIN_HIGH ) ;
				return Local_u8PressedKey ;
			}

		}
		/* Deactivate Current Column */
		DIO_u8SetPinValue(KPD_PORT , KPD_u8COLUMNARR[Local_u8ColumnIdx] , DIO_u8PIN_HIGH ) ;
 }

 return Local_u8PressedKey ;
}
