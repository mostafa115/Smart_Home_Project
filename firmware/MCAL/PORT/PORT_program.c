/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : PORT             ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_interface.h"
#include "PORT_register.h"


void PORT_voidInt(void){

    DDRA = PORTA_DIR;
    DDRB = PORTB_DIR;
    DDRC = PORTC_DIR;
    DDRD = PORTD_DIR;
    DDRE = PORTE_DIR;
    DDRF = PORTF_DIR;
    DDRG = PORTG_DIR;

    PORTA = PORTA_INITIAL_VALUE ;
    PORTB = PORTB_INITIAL_VALUE ;
    PORTC = PORTC_INITIAL_VALUE ;
    PORTD = PORTD_INITIAL_VALUE ;
    PORTE = PORTE_INITIAL_VALUE ;
    PORTF = PORTF_INITIAL_VALUE ;
    PORTG = PORTG_INITIAL_VALUE ;
}
