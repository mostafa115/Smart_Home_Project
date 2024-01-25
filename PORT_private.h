/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : PORT             ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/


#ifndef PORT_PRIVATE_H
#define PORT_PRIVATE_H

#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)                CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)         0b##b7##b6##b5##b4##b3##b2##b1##b0

#define PORTA_DIR                   CONC(PORTA_PIN7_DIR,PORTA_PIN6_DIR,PORTA_PIN5_DIR,PORTA_PIN4_DIR,PORTA_PIN3_DIR,PORTA_PIN2_DIR,PORTA_PIN1_DIR,PORTA_PIN0_DIR)
#define PORTB_DIR                   CONC(PORTB_PIN7_DIR,PORTB_PIN6_DIR,PORTB_PIN5_DIR,PORTB_PIN4_DIR,PORTB_PIN3_DIR,PORTB_PIN2_DIR,PORTB_PIN1_DIR,PORTB_PIN0_DIR)
#define PORTC_DIR                   CONC(PORTC_PIN7_DIR,PORTC_PIN6_DIR,PORTC_PIN5_DIR,PORTC_PIN4_DIR,PORTC_PIN3_DIR,PORTC_PIN2_DIR,PORTC_PIN1_DIR,PORTC_PIN0_DIR)
#define PORTD_DIR                   CONC(PORTD_PIN7_DIR,PORTD_PIN6_DIR,PORTD_PIN5_DIR,PORTD_PIN4_DIR,PORTD_PIN3_DIR,PORTD_PIN2_DIR,PORTD_PIN1_DIR,PORTD_PIN0_DIR)
#define PORTE_DIR                   CONC(PORTE_PIN7_DIR,PORTE_PIN6_DIR,PORTE_PIN5_DIR,PORTE_PIN4_DIR,PORTE_PIN3_DIR,PORTE_PIN2_DIR,PORTE_PIN1_DIR,PORTE_PIN0_DIR)
#define PORTF_DIR                   CONC(PORTF_PIN7_DIR,PORTF_PIN6_DIR,PORTF_PIN5_DIR,PORTF_PIN4_DIR,PORTF_PIN3_DIR,PORTF_PIN2_DIR,PORTF_PIN1_DIR,PORTF_PIN0_DIR)
#define PORTG_DIR                   CONC(PORTG_PIN7_DIR,PORTG_PIN6_DIR,PORTG_PIN5_DIR,PORTG_PIN4_DIR,PORTG_PIN3_DIR,PORTG_PIN2_DIR,PORTG_PIN1_DIR,PORTG_PIN0_DIR)

#define PORTA_INITIAL_VALUE         CONC(PORTA_PIN7_VALUE,PORTA_PIN6_VALUE,PORTA_PIN5_VALUE,PORTA_PIN4_VALUE,PORTA_PIN3_VALUE,PORTA_PIN2_VALUE,PORTA_PIN1_VALUE,PORTA_PIN0_VALUE)
#define PORTB_INITIAL_VALUE         CONC(PORTB_PIN7_VALUE,PORTB_PIN6_VALUE,PORTB_PIN5_VALUE,PORTB_PIN4_VALUE,PORTB_PIN3_VALUE,PORTB_PIN2_VALUE,PORTB_PIN1_VALUE,PORTB_PIN0_VALUE)
#define PORTC_INITIAL_VALUE         CONC(PORTC_PIN7_VALUE,PORTC_PIN6_VALUE,PORTC_PIN5_VALUE,PORTC_PIN4_VALUE,PORTC_PIN3_VALUE,PORTC_PIN2_VALUE,PORTC_PIN1_VALUE,PORTC_PIN0_VALUE)
#define PORTD_INITIAL_VALUE         CONC(PORTD_PIN7_VALUE,PORTD_PIN6_VALUE,PORTD_PIN5_VALUE,PORTD_PIN4_VALUE,PORTD_PIN3_VALUE,PORTD_PIN2_VALUE,PORTD_PIN1_VALUE,PORTD_PIN0_VALUE)
#define PORTE_INITIAL_VALUE         CONC(PORTE_PIN7_VALUE,PORTE_PIN6_VALUE,PORTE_PIN5_VALUE,PORTE_PIN4_VALUE,PORTE_PIN3_VALUE,PORTE_PIN2_VALUE,PORTE_PIN1_VALUE,PORTE_PIN0_VALUE)
#define PORTF_INITIAL_VALUE         CONC(PORTF_PIN7_VALUE,PORTF_PIN6_VALUE,PORTF_PIN5_VALUE,PORTF_PIN4_VALUE,PORTF_PIN3_VALUE,PORTF_PIN2_VALUE,PORTF_PIN1_VALUE,PORTF_PIN0_VALUE)
#define PORTG_INITIAL_VALUE         CONC(PORTG_PIN7_VALUE,PORTG_PIN6_VALUE,PORTG_PIN5_VALUE,PORTG_PIN4_VALUE,PORTG_PIN3_VALUE,PORTG_PIN2_VALUE,PORTG_PIN1_VALUE,PORTG_PIN0_VALUE)

#endif