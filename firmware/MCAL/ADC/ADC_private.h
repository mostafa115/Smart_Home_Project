/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : ADC              ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define 		IDLE								1
#define 		BUSY								0

#define 		DIV_By_2      						0
#define 		DIV_By_4      						2
#define 		DIV_By_8      						3
#define 		DIV_By_16      						4
#define 		DIV_By_32      						5
#define 		DIV_By_64      						6
#define 		DIV_By_128      					7

#define 		bits_10           				 	0
#define 		bits_8            				 	1

#define    		FREE_RUNNING                        0
#define         AUTO_TRIGGER						1

#define 		Free_Running_Mode					0
#define         Analog_Comparator					0b00100000
#define         EXTI_Request_0						0b01000000
#define         Timer_0_Compare_Match				0b01100000
#define         Timer_0_Overflow					0b10000000
#define         Timer_Compare_Match_B				0b10100000
#define         Timer_1_Overflow					0b11000000
#define         Timer_1_Capture						0b11100000



#define 		ADC_Reference_Selection_Mask		0b00111111

#define 		ADC_Presc_Mask    					0b11111000

#define			ADC_Channel_Mask        			0b11100000

#define         ADC_Auto_Trigger_Mask               0b00011111


#endif
