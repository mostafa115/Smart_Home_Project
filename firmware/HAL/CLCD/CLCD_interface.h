/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal    ************/
/****************************     Layer  : HAL              ************/
/****************************     swc    : CLCD             ************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_


void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidSendString(const char * Copy_pcString);

void CLCD_voidWriteSpecialCharacter(u8 * Copy_pu8Pattern , u8 Copy_pu8PatternNumber , u8 Copy_u8XPos , u8 Copy_u8YPos  ) ;

void CLCD_voidGoToXY(u8 Copy_u8XPos , u8 Copy_u8YPos ) ;

void CLCD_voidWriteNumber(u32 Copy_u32Number , u8 Copy_u8X , u8 Copy_u8Y );
void CLCD_voidClearLCD(void);

void CLCD_voidInit(void);




#endif 
