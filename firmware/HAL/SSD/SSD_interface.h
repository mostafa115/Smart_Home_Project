/***********************************************************************/
/***********************************************************************/
/****************************     Author : Mostafa Gamal   *************/
/****************************     Layer  : HAL             *************/
/****************************     swc    : SEVEN_SEGMENT   *************/
/****************************     Version: 1.00             ************/
/***********************************************************************/
/***********************************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_
#define Anode    1
#define Cathode  0
#define number0  0b11000000
#define number1  0b11111001
#define number2  0b10100100
#define number3  0b10110000
#define number4  0b10011001
#define number5  0b10010010
#define number6  0b10000010
#define number7  0b11111000
#define number8  0b10000000
#define number9  0b10010000

typedef struct{
	u8 COM_TYPE ;
	u8 PORT_0 ;
	u8 PIN_0 ;
	u8 PORT_1 ;
	u8 PIN_1 ;
	u8 PORT_2 ;
	u8 PIN_2 ;
	u8 PORT_3 ;
	u8 PIN_3 ;
	u8 PORT_4 ;
	u8 PIN_4  ;
	u8 PORT_5 ;
	u8 PIN_5 ;
	u8 PORT_6 ;
	u8 PIN_6 ;
	u8 EnablePort;
	u8 EnablePin ;

}ssd_t;

void SSD_u8SetNumber(u8 Copy_u8Number, ssd_t * Copy_pu8sst);
void SSD_u8Enable(ssd_t * Copy_pu8sst);

void SSD_u8Disable(ssd_t * Copy_pu8sst);

#endif
