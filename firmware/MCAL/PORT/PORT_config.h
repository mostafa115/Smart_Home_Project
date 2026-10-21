/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : PORT             ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/


#ifndef PORT_CONFIG_H
#define PORT_CONFIG_H

/* 
    Choose : 0 for input 
            1 for output 
                            */

#define PORTA_PIN0_DIR     0
#define PORTA_PIN1_DIR     0
#define PORTA_PIN2_DIR     0
#define PORTA_PIN3_DIR     0
#define PORTA_PIN4_DIR     1
#define PORTA_PIN5_DIR     1
#define PORTA_PIN6_DIR     1
#define PORTA_PIN7_DIR     1

#define PORTB_PIN0_DIR     0
#define PORTB_PIN1_DIR     0
#define PORTB_PIN2_DIR     1
#define PORTB_PIN3_DIR     1
#define PORTB_PIN4_DIR     0
#define PORTB_PIN5_DIR     0
#define PORTB_PIN6_DIR     0
#define PORTB_PIN7_DIR     1


#define PORTC_PIN0_DIR     1
#define PORTC_PIN1_DIR     1
#define PORTC_PIN2_DIR     1
#define PORTC_PIN3_DIR     0
#define PORTC_PIN4_DIR     1
#define PORTC_PIN5_DIR     1
#define PORTC_PIN6_DIR     1
#define PORTC_PIN7_DIR     1


#define PORTD_PIN0_DIR     1
#define PORTD_PIN1_DIR     1
#define PORTD_PIN2_DIR     0
#define PORTD_PIN3_DIR     1
#define PORTD_PIN4_DIR     1
#define PORTD_PIN5_DIR     1
#define PORTD_PIN6_DIR     1
#define PORTD_PIN7_DIR     1

#define PORTE_PIN0_DIR     1
#define PORTE_PIN1_DIR     1
#define PORTE_PIN2_DIR     1
#define PORTE_PIN3_DIR     1
#define PORTE_PIN4_DIR     1
#define PORTE_PIN5_DIR     1
#define PORTE_PIN6_DIR     1
#define PORTE_PIN7_DIR     1

#define PORTF_PIN0_DIR     0
#define PORTF_PIN1_DIR     0
#define PORTF_PIN2_DIR     1
#define PORTF_PIN3_DIR     1
#define PORTF_PIN4_DIR     1
#define PORTF_PIN5_DIR     1
#define PORTF_PIN6_DIR     1
#define PORTF_PIN7_DIR     1

#define PORTG_PIN0_DIR     1
#define PORTG_PIN1_DIR     0
#define PORTG_PIN2_DIR     1
#define PORTG_PIN3_DIR     1
#define PORTG_PIN4_DIR     0
#define PORTG_PIN5_DIR     0
#define PORTG_PIN6_DIR     0
#define PORTG_PIN7_DIR     0




/* 
    Choose : 0 for Low if  the direction is output 
                or floating if the direction is input 
             
             1 for high if the direction is output 
             and pull up if the direction is input 
              
                            */


#define PORTA_PIN0_VALUE     1
#define PORTA_PIN1_VALUE     1
#define PORTA_PIN2_VALUE     1
#define PORTA_PIN3_VALUE     1
#define PORTA_PIN4_VALUE     0
#define PORTA_PIN5_VALUE     0
#define PORTA_PIN6_VALUE     0
#define PORTA_PIN7_VALUE     0

#define PORTB_PIN0_VALUE     1
#define PORTB_PIN1_VALUE     1
#define PORTB_PIN2_VALUE     0
#define PORTB_PIN3_VALUE     0
#define PORTB_PIN4_VALUE     1
#define PORTB_PIN5_VALUE     1
#define PORTB_PIN6_VALUE     1
#define PORTB_PIN7_VALUE     0



#define PORTC_PIN0_VALUE     0
#define PORTC_PIN1_VALUE     0
#define PORTC_PIN2_VALUE     0
#define PORTC_PIN3_VALUE     1
#define PORTC_PIN4_VALUE     0
#define PORTC_PIN5_VALUE     0
#define PORTC_PIN6_VALUE     0
#define PORTC_PIN7_VALUE     0



#define PORTD_PIN0_VALUE     0
#define PORTD_PIN1_VALUE     0
#define PORTD_PIN2_VALUE     0
#define PORTD_PIN3_VALUE     0
#define PORTD_PIN4_VALUE     0
#define PORTD_PIN5_VALUE     1
#define PORTD_PIN6_VALUE     0
#define PORTD_PIN7_VALUE     0

#define PORTE_PIN0_VALUE     0
#define PORTE_PIN1_VALUE     0
#define PORTE_PIN2_VALUE     0
#define PORTE_PIN3_VALUE     0
#define PORTE_PIN4_VALUE     0
#define PORTE_PIN5_VALUE     0
#define PORTE_PIN6_VALUE     0
#define PORTE_PIN7_VALUE     0

#define PORTF_PIN0_VALUE     0
#define PORTF_PIN1_VALUE     0
#define PORTF_PIN2_VALUE     0
#define PORTF_PIN3_VALUE     0
#define PORTF_PIN4_VALUE     0
#define PORTF_PIN5_VALUE     0
#define PORTF_PIN6_VALUE     0
#define PORTF_PIN7_VALUE     0

#define PORTG_PIN0_VALUE     0
#define PORTG_PIN1_VALUE     0
#define PORTG_PIN2_VALUE     1
#define PORTG_PIN3_VALUE     1
#define PORTG_PIN4_VALUE     0
#define PORTG_PIN5_VALUE     0
#define PORTG_PIN6_VALUE     0
#define PORTG_PIN7_VALUE     0

#endif 
