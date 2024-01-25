/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : HAL              ************/
/****************************     swc    : DC_MOTOR         ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "DC_MOTOR_private.h"
#include "DC_MOTOR_config.h"
#include "DC_MOTOR_interface.h"

void DCMOTOR_voidRotateClockWise(void){
	DIO_u8SetPinValue(relay2_Port,relay2_TransistorBase_Pin,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(relay1_Port,relay1_TransistorBase_Pin,DIO_u8PIN_HIGH);
}
void DCMOTOR_voidRotateUntiClockWise(void){
	DIO_u8SetPinValue(relay1_Port,relay1_TransistorBase_Pin,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(relay2_Port,relay2_TransistorBase_Pin,DIO_u8PIN_HIGH);
}
void DCMOTOR_voidStop(void){
	DIO_u8SetPinValue(relay1_Port,relay1_TransistorBase_Pin,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(relay2_Port,relay2_TransistorBase_Pin,DIO_u8PIN_LOW);
}
