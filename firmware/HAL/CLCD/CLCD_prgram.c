/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : HAL              ************/
/****************************     swc    : CLCD             ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"
#include "DIO_register.h"
#include <util/delay.h>

static u8 Global_su8Counter = 0;

void CLCD_voidSendCommand(u8 Copy_u8Command){

		// Set RS pin to low for command

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	//Set RW pin low for write

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/* Send command by Data Port */

	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);

	/* Set Enable Pulse */

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);




}


void CLCD_voidSendData(u8 Copy_u8Data){

	if(Global_su8Counter == 16){
		Global_su8Counter = 0 ;
		CLCD_voidGoToXY(1,0);
	}

		/* Set RS pin to high for Data */

		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

		/* Set RW pin low for write */

		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

		/* Send Data by Data Port */

		DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Data);

		/* Set Enable Pulse */

		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);


		Global_su8Counter++ ;

}

void CLCD_voidSendString(const char * Copy_pcString){


u8 counter = 0 ;


	if(Global_su8Counter == 16){
		Global_su8Counter = 0 ;
		CLCD_voidGoToXY(1,0);
	}
	while((Copy_pcString[counter]) != '\0'){

		CLCD_voidSendData(Copy_pcString[counter]);
		counter++;

	}

	Global_su8Counter+= counter ;
}

void CLCD_voidGoToXY(u8 Copy_u8XPos , u8 Copy_u8YPos ) {

	u8 Local_u8Address;
	Global_su8Counter = Copy_u8YPos ;
	if(Copy_u8XPos == 0){

		/* location is at first line */
		Local_u8Address = Copy_u8YPos ;
	}

	else if(Copy_u8XPos == 1){

		/* location is at second line */
		Local_u8Address = Copy_u8YPos + 0x40 ;
	}
	/* set bit number 7 for set DDRAM Address command then send the command */
CLCD_voidSendCommand(Local_u8Address + 128);

}

void CLCD_voidWriteSpecialCharacter(u8 * Copy_pu8Pattern , u8 Copy_pu8PatternNumber , u8 Copy_u8XPos , u8 Copy_u8YPos  ) {

	u8 Local_u8CGRAMAddress , Counter ;

	/* Set CGRAM Address whose each block is 8 byte */

	Local_u8CGRAMAddress = Copy_pu8PatternNumber * 8 ;

/* Send CGRAM Address command to lcd with setting bit 6 , clearing bit 7 */

	CLCD_voidSendCommand(Local_u8CGRAMAddress + 64 ) ;

	/* write the pattern into  CGRAM*/
	for(Counter = 0 ; Counter < 8 ; Counter++){
	CLCD_voidSendData(Copy_pu8Pattern[Counter]);

	}

	/* Go back to DDRAM to display the pattern */

CLCD_voidGoToXY(Copy_u8XPos , Copy_u8YPos);

/* Display the pattern written in the CGRAM */

CLCD_voidSendData(Copy_pu8PatternNumber);
}

void CLCD_voidWriteNumber(u32 Copy_u32Number , u8 Copy_u8X , u8 Copy_u8Y ){

	u8 Local_u8Digits = 0 , Local_u8Iterator = 0;
	u32  Local_u32TempNumber = Copy_u32Number ;

	if(Copy_u32Number == 0 ){
		CLCD_voidGoToXY(Copy_u8X,Copy_u8Y);
		CLCD_voidSendData('0');
	}else {

	while(Local_u32TempNumber != 0){
		Local_u32TempNumber /= 10 ;
		Local_u8Digits++ ;
	}

	for(Local_u8Iterator = Local_u8Digits ; Local_u8Iterator > 0 ; Local_u8Iterator-- ){

		CLCD_voidGoToXY(Copy_u8X, Copy_u8Y + Local_u8Iterator - 1 );

		switch(Copy_u32Number % 10){
		case 0 : CLCD_voidSendData('0'); break ;
		case 1 : CLCD_voidSendData('1'); break ;
		case 2 : CLCD_voidSendData('2'); break ;
		case 3 : CLCD_voidSendData('3'); break ;
		case 4 : CLCD_voidSendData('4'); break ;
		case 5 : CLCD_voidSendData('5'); break ;
		case 6 : CLCD_voidSendData('6'); break ;
		case 7 : CLCD_voidSendData('7'); break ;
		case 8 : CLCD_voidSendData('8'); break ;
		case 9 : CLCD_voidSendData('9'); break ;
		}
		Copy_u32Number /= 10 ;
	}
	}
}

void CLCD_voidClearLCD(void){

	CLCD_voidSendCommand(1);
	Global_su8Counter = 0 ;
}

void CLCD_voidInit(void){

	/* wait for more than 30 ms after VDD rises 4.5 v */

	_delay_ms(40);

	/* Function set command : 2 lines and 5 * 8 Font size */
	CLCD_voidSendCommand(0b00111000);

	/* Display on /off control : Enable screen , Disable cursor and no blink cursor  */
	CLCD_voidSendCommand(0b00001100);

	/* Display clear */
	CLCD_voidSendCommand(1);


}
