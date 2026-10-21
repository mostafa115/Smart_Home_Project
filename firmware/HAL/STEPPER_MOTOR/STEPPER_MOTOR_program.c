/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : HAL              ************/
/****************************     swc    : STEPPER_MOTOR    ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "STEPPER_MOTOR_config.h"
#include "STEPPER_MOTOR_interface.h"
#include "STEPPER_MOTOR_private.h"
#include "util/delay.h"

void StepperMotor_voidRotateCloclWise(u16 Copy_u16Angle){
	Copy_u16Angle /= 0.7 ;
	u16 Local_u16Counter = 0 ;
	while(Local_u16Counter < Copy_u16Angle){
		DIO_u8SetPinValue(ULN_Port,ULN_Base0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base3,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(ULN_Port,ULN_Base0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(ULN_Port,ULN_Base3,DIO_u8PIN_LOW);
		_delay_ms(2);
		DIO_u8SetPinValue(ULN_Port,ULN_Base0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(ULN_Port,ULN_Base2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base3,DIO_u8PIN_LOW);
		_delay_ms(2);
		DIO_u8SetPinValue(ULN_Port,ULN_Base0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(ULN_Port,ULN_Base1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base3,DIO_u8PIN_LOW);
		_delay_ms(2);
		Local_u16Counter ++ ;
	}
}

void StepperMotor_voidRotateCounterCloclWise(u16 Copy_u16Angle){
	Copy_u16Angle /= 0.7 ;
	u16 Local_u16Counter = 0 ;
	while(Local_u16Counter < Copy_u16Angle){
		DIO_u8SetPinValue(ULN_Port,ULN_Base0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(ULN_Port,ULN_Base1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base3,DIO_u8PIN_LOW);
		_delay_ms(2);
		DIO_u8SetPinValue(ULN_Port,ULN_Base0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(ULN_Port,ULN_Base2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base3,DIO_u8PIN_LOW);
		_delay_ms(2);
		DIO_u8SetPinValue(ULN_Port,ULN_Base0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(ULN_Port,ULN_Base3,DIO_u8PIN_LOW);
		_delay_ms(2);
		DIO_u8SetPinValue(ULN_Port,ULN_Base0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(ULN_Port,ULN_Base3,DIO_u8PIN_HIGH);
		_delay_ms(2);
		Local_u16Counter ++ ;
	}
}

void StepperMotor_voidStop(void){
	DIO_u8SetPinValue(ULN_Port,ULN_Base0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(ULN_Port,ULN_Base1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(ULN_Port,ULN_Base2,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(ULN_Port,ULN_Base3,DIO_u8PIN_LOW);
}



