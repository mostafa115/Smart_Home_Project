/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : ADC              ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


/* Choose Reference Selection :
 * 					options   :
 * 					 		  1- AREF    		->  Takes AREF as reference , Turned off VREF.
 * 					 		  2- AVCC    		->  Takes AVCC as reference , External  Capacitor at AREF pin.
 * 					 		  3- Internal		->  2.65 Voltage reference with External capacitor at AREF pin
 */

#define Reference_Selection     			AVCC

/* Choose ADC Resolution :
 * 				options  :
 * 						 1 - bits_8.    -> return 1 register  -> ADCH
 * 						 2 - bits_10.   -> return 2 registers -> ADCH + ADCL
 */

#define 		Resolution 					bits_10

/* Choose Division Factor :
 * 				  options :
 * 							1- DIV_By_2
 * 							2- DIV_By_4
 * 							3- DIV_By_8
 * 							4- DIV_By_16
 * 							5- DIV_By_32
 * 							6- DIV_By_64
 * 							7- DIV_By_128
 * */


#define			DIV_Factor    			DIV_By_128

/* Choose Conversion Mode :
 *                options :
 *                		  1- FREE_RUNNING.  -> Using Pooling. and you have to clear ADIF after conversion.
 * 						  2- AUTO_TRIGGER.  -> Using Interrupt.
 */

#define        Conversion_Mode          FREE_RUNNING

/* Choose Channel :
 * 					1- ADC0  -> 0  		for PINA0
 * 					2- ADC1  -> 1		for PINA1
 * 					3- ADC2  -> 2		for PINA2
 * 					4- ADC3  -> 3		for PINA3
 * 					5- ADC4  -> 4		for PINA4
 * 					6- ADC5  -> 5		for PINA5
 * 					7- ADC6  -> 6		for PINA6
 * 					8- ADC7  -> 7		for PINA7
 */

#define 	ADC_Channel    			ADC0

/* Choose Auto Trigger Source :
 * 				 options :
 * 				 		 1- Free_Running_Mode
 * 				 		 2- Analog_Comparator
 * 				 		 3- EXTI_Request_0
 * 				 		 4- Timer_0_Compare_Match
 * 				 		 5- Timer_0_Overflow
 * 				 		 6-	Timer_Compare_Match_B
 * 				 		 7- Timer_1_Overflow
 * 				 		 8- Timer_1_Capture
 */


#define  	ADC_Trigger_Source     Free_Running_Mode

#endif
