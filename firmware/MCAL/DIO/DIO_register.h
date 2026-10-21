/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : MCAL             ************/
/****************************     swc    : DIO              ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef DIO_REGISTER_H_
#define DIO_REGISTER_H_

#define PORTA 			*((volatile u8*)0X3B)
#define PINA  			*((volatile u8*)0X39)

#define PORTB 			*((volatile u8*)0X38)
#define PINB  			*((volatile u8*)0X36)

#define PORTC 			*((volatile u8*)0X35)
#define PINC  			*((volatile u8*)0X33)

#define PORTD 			*((volatile u8*)0X32)
#define PIND  			*((volatile u8*)0X30)

#define PORTE 			*((volatile u8*)0X23)
#define PINE  			*((volatile u8*)0X21)

#define PORTF 			*((volatile u8*)0X62)
#define PINF  			*((volatile u8*)0X20)

#define PORTG 			*((volatile u8*)0X65)
#define PING  			*((volatile u8*)0X63)



#endif 
