/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : HAL              ************/
/****************************     swc    : STEPPER_MOTOR         ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef STEPPER_MOTOR_INTERFACE_H_
#define STEPPER_MOTOR_INTERFACE_H_

void StepperMotor_voidRotateCloclWise(u16 Copy_u16Angle);
void StepperMotor_voidRotateCounterCloclWise(u16 Copy_u16Angle);
void StepperMotor_voidStop(void);


#endif
