#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "MTWI_interface.h"
#include "EEPROM_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "TIM1.h"
#include "STEPPER_MOTOR_interface.h"
#include "DC_MOTOR_interface.h"
#include "ADC_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"
#include "SSD_interface.h"
#include "UART_interface.h"

#define BLINDS_OPEND      1
#define BLINDS_CLOSED     0

void ISR_LM45_With7Segments_InTimer0(void);

/* Seven Segment 1 */

static ssd_t Seven_Segment1 = {Cathode,DIO_u8PORTF,DIO_u8PIN2 ,DIO_u8PORTF,DIO_u8PIN3,DIO_u8PORTF,DIO_u8PIN4 , DIO_u8PORTF,DIO_u8PIN5,DIO_u8PORTF,DIO_u8PIN6 ,
		DIO_u8PORTF,DIO_u8PIN7 , DIO_u8PORTD , DIO_u8PIN7 , DIO_u8PORTB ,DIO_u8PIN7 };

/* Seven Segment 2 */

static ssd_t Seven_Segment2 = {Cathode,DIO_u8PORTF,DIO_u8PIN2 ,DIO_u8PORTF,DIO_u8PIN3,DIO_u8PORTF,DIO_u8PIN4 , DIO_u8PORTF,DIO_u8PIN5,DIO_u8PORTF,DIO_u8PIN6 ,
		DIO_u8PORTF,DIO_u8PIN7 , DIO_u8PORTD , DIO_u8PIN7 , DIO_u8PORTD ,DIO_u8PIN6 };

static u8 Global_u8ReadKeyValue = 0xff , Global_u8BlindsState = 0 , Global_Password_u8Flag = 0 , Global_Password_u8ChangeFlag = 0, Global_u8BlindsOpenFlag = 0 , Global_u8BlindsCloseFlag = 0 , Global_u8FanFlag = 0 , Global_u8ExhaustFanFlag = 0   ;

/*For Receiving Data From TTL */
static u8 Global_u8Rx_Data = 0 ;

/* For Transmitting Message To User */
void send_voidChar(void);

/* For Receiving Message From User */

void receive_voidChar(void);


int main(void)
{

	u8  Local_u8PasswordStateAddress = 0x5E ,Local_u8PasswordState = 0 , Local_u8ReadPassword = 0, Local_CounterSetPassword = 0 ;
	static u16 Local_u16SetPassword = 0 , Local_u16RealPassword = 0  , Local_u16CheckPassword = 0 , Local_u16ChangePassword = 0 ;

	/* Initializing Configuration Of Ports */
	PORT_voidInt();

	/* Initialize Uart */
	UART_voidInit();

	/*Using Asynchronous Uart */
	UARTRX_vidSetISR(receive_voidChar);
	UARTTX_vidSetISR(send_voidChar);

	/* Initialize Two wire Interface Communication Protocol */
	TWI_vMasterInit();

	/* Initialize Character LCD */
	CLCD_voidInit();

	/* Initialize Timer 1 For Servo Motor */
	TIM1_voidInit();

	/* Interrupt Capture Unit Value Depending on Function To Get 1 m high and 19 m Low  */
	TIM1_voidSetIcuRegValue(40000);
	TIM1_voidEnable(2); // 2 to congigure prescaler 8

	/* Initialize ADC */
	ADC_voidInit();

	/* Initialize Timer 0 */

	Timer0_voidInit();
	/* Passing This Function to MCAL Layer as a call back Function */
	Timer0_u8SetCallBack(ISR_LM45_With7Segments_InTimer0);
	/* Compare Match Value */
	Timer0_voidSetCompMatchValue(250);

	/* Prescaler 64 */

	Timer0_voidSetPrescalerValue(PRESCALER_64);
	/* Enable Interrupt Of Timer 0 */
	Timer0_voidInterruptEnable();
	GIE_voidEnable();

	/* First Frame ProtoType Projct */

	CLCD_voidSendString("Final Project");
	_delay_ms(2500);
	CLCD_voidClearLCD();

	/* Second Frame Ask For First Time Password */


	EEPROM_vRead(Local_u8PasswordStateAddress,&Local_u8PasswordState);
	Local_u8PasswordState = 0 ;
	/* Check if there is Password or no in EEPROM and if no let admin Set Password */
	if(Local_u8PasswordState != 0x01 )
	{
		EEPROM_vWrite(Local_u8PasswordStateAddress,0x01);
		CLCD_voidSendString("Welcome Jimmy");
		_delay_ms(2500);
		CLCD_voidClearLCD();
		CLCD_voidSendString("Please Enter ");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("Password :");

		while(Global_u8ReadKeyValue != '=')
		{
			do{
				Global_u8ReadKeyValue = KPD_u8GetPressedKey();
			}while(Global_u8ReadKeyValue == 0xff);
			CLCD_voidClearLCD();
			if(Global_u8ReadKeyValue != '=')
			{
				Local_u16SetPassword = ( Local_u16SetPassword * 10 ) + Global_u8ReadKeyValue ;
				CLCD_voidWriteNumber(Local_u16SetPassword , 0 , 0);
			}
			_delay_ms(200);
		}

		/* Set Password in EEPROM Memory */

		EEPROM_vWrite(0x00,(u8)Local_u16SetPassword);
		Local_u16SetPassword >>= 8 ;
		EEPROM_vWrite(0x01,(u8)Local_u16SetPassword);
		CLCD_voidClearLCD();
		CLCD_voidSendString("Password Saved ");
		_delay_ms(2500);
		CLCD_voidClearLCD();
		CLCD_voidSendString("Thank You ");
		_delay_ms(2500);
		CLCD_voidClearLCD();

		/* Set Global Key variable as not Pressed */

		Global_u8ReadKeyValue = 0xff ;

		/* Read Password From Our memory */

		EEPROM_vRead(0x01,&Local_u8ReadPassword);
		Local_u16RealPassword = Local_u8ReadPassword ;
		Local_u16RealPassword <<= 8 ;
		EEPROM_vRead(0x00,&Local_u8ReadPassword);
		Local_u16RealPassword |= Local_u8ReadPassword ;
	}



	while(1)
	{

		if(Global_Password_u8Flag == 1 )
		{

			/* Clear Password Flag */

			Global_Password_u8Flag = 0 ;

			/* If User Wants To Change Password */
			if(1 == Global_Password_u8Flag)
			{
				CLCD_voidSendString("To Change Enter");
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("Current Password");
			}
			else
			{
				/* Ask Guest for A password */
				CLCD_voidSendString("Enter Password");
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("To Open the Door");
				Local_u16CheckPassword = 0 ;
			}

			/* Get Password From the Guest */
			Local_u16CheckPassword = 0 ;
			while(Global_u8ReadKeyValue != '=')
			{
				do{
					Global_u8ReadKeyValue = KPD_u8GetPressedKey();
				}while(Global_u8ReadKeyValue == 0xff);
				CLCD_voidClearLCD();
				if(Global_u8ReadKeyValue != '=')
				{
					Local_u16CheckPassword = ( Local_u16CheckPassword * 10 ) + Global_u8ReadKeyValue ;
					CLCD_voidWriteNumber(Local_u16CheckPassword , 0 , 0);
				}
				_delay_ms(200);
			}
			Global_u8ReadKeyValue = 0xff ;
			CLCD_voidClearLCD();

			/* Check Guest's Password */

			if(Local_u16CheckPassword == Local_u16RealPassword)
			{
				if(1 == Global_Password_u8ChangeFlag)
				{
					CLCD_voidClearLCD();
					CLCD_voidSendString("Enter New");
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("Password ");
					while(Global_u8ReadKeyValue != '=')
					{
						do{
							Global_u8ReadKeyValue = KPD_u8GetPressedKey();
						}while(Global_u8ReadKeyValue == 0xff);
						CLCD_voidClearLCD();
						if(Global_u8ReadKeyValue != '=')
						{
							Local_u16ChangePassword = ( Local_u16ChangePassword * 10 ) + Global_u8ReadKeyValue ;
							CLCD_voidWriteNumber(Local_u16ChangePassword , 0 , 0);
						}
						_delay_ms(200);
					}

					EEPROM_vWrite(0x00,0xff);
					EEPROM_vWrite(0x01,0xff);

					/* Save New Password In EEPROM */

					EEPROM_vWrite(0x00,(u8)Local_u16ChangePassword);
					Local_u16ChangePassword >>= 8 ;
					EEPROM_vWrite(0x01,(u8)Local_u16ChangePassword);
					CLCD_voidClearLCD();
					CLCD_voidSendString("Password Saved ");
					_delay_ms(2500);
					CLCD_voidClearLCD();
					CLCD_voidSendString("Thank You ");
					_delay_ms(2500);
					CLCD_voidClearLCD();
					Global_u8ReadKeyValue = 0xff ;
					Global_Password_u8ChangeFlag = 0 ;

					/* Read Password From Our memory */

					EEPROM_vRead(0x01,&Local_u8ReadPassword);
					Local_u16RealPassword = Local_u8ReadPassword ;
					Local_u16RealPassword <<= 8 ;
					EEPROM_vRead(0x00,&Local_u8ReadPassword);
					Local_u16RealPassword |= Local_u8ReadPassword ;

				}

				else
				{
					CLCD_voidClearLCD();
					CLCD_voidSendString("Welcome Jimmy");
					/* Refresh  Servo */
					TIM1_voidSetCmpARegValue(1000);
					//TIM1_voidSetCmpARegValue(4000);
					/* Open Door By Timer 1 */
					TIM1_voidSetCmpARegValue(4000);
					DIO_u8SetPinValue(DIO_u8PORTG,DIO_u8PIN2,DIO_u8PIN_LOW);
					_delay_ms(1000);
					DIO_u8SetPinValue(DIO_u8PORTG,DIO_u8PIN2,DIO_u8PIN_HIGH);
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("Door Opened");
					_delay_ms(3000);
					Local_CounterSetPassword = 0 ;
					/* Close Door By Timer 1 */
					CLCD_voidClearLCD();
					TIM1_voidSetCmpARegValue(1500);//OCR1A
					_delay_ms(10);
					CLCD_voidSendString("Door Closed");
					_delay_ms(1000);
					CLCD_voidClearLCD();
				}


			}
			else if (Local_CounterSetPassword == 2 )
			{
				CLCD_voidClearLCD();
				CLCD_voidSendString("3 Times Wrong ");
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("Password");
				_delay_ms(3000);
				CLCD_voidClearLCD();
				CLCD_voidSendString("Door Closed ");
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("Go Away");
				CLCD_voidClearLCD();
			}
			else
			{
				CLCD_voidClearLCD();
				CLCD_voidSendString("Try Again ");
				Local_CounterSetPassword++ ;
				CLCD_voidGoToXY(1,0);
				//CLCD_voidWriteNumber(Local_u16RealPassword,1,0);
				_delay_ms(2000);
				CLCD_voidClearLCD();
			}

			/* Clear Password Flag */
			Global_Password_u8Flag = 0 ;
		}
		else
		{
			/* Blinds Section */
			CLCD_voidClearLCD();
			CLCD_voidSendString("To Open blinds>>");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("Stick To Switch1");
			_delay_ms(1000);
			if(Global_u8BlindsOpenFlag == 1 )
			{
				StepperMotor_voidRotateCounterCloclWise(360);
				StepperMotor_voidRotateCounterCloclWise(360);
				Global_u8BlindsOpenFlag = 0 ;
			}
			CLCD_voidClearLCD();
			CLCD_voidSendString("To Close blinds>>");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("Stick To Switch2");
			_delay_ms(1000);
			if(Global_u8BlindsCloseFlag == 1 )
			{
				StepperMotor_voidRotateCloclWise(360);
				StepperMotor_voidRotateCloclWise(360);
				Global_u8BlindsCloseFlag = 0 ;
			}
			/* Fan Section */
			CLCD_voidClearLCD();
			CLCD_voidSendString("To Open Fan>>");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("Stick To Dip1");
			_delay_ms(1000);

			/* Exhaust Fan Section */
			CLCD_voidClearLCD();
			CLCD_voidSendString("To Open Exhaust");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("Fan Dip7");
			_delay_ms(1000);
			CLCD_voidClearLCD();

			if(Global_u8FanFlag == 1)
			{
				DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_LOW);
				DCMOTOR_voidRotateClockWise();
				Global_u8FanFlag = 0 ;
			}
			else if(1 == Global_u8ExhaustFanFlag)
			{
				DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_LOW);
				DCMOTOR_voidRotateUntiClockWise();
				Global_u8ExhaustFanFlag = 0 ;
			}
			else
			{
				DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_HIGH);
			}

		}



	}
}

void ISR_LM45_With7Segments_InTimer0(void)
{
	static u16 Local_u8Counter = 0 , Local_u16LM35DigitalValue = 0 , Local_u16Temp = 0 , Local_u16SSDValue = 0 ;
	static u8 Local_u8BlindsOpenStatus = 1 , Local_u8BlindsCloseStatus = 1 , Local_u8FanOpenStatus = 1 ,Local_u8KeyValue = 0 , Local_u8ExhaustFanOpenStatus = 1 ;

	/* Fan Section */

	if(1 == Local_u8Counter)
	{
		DIO_u8GetPinValue(DIO_u8PORTB,DIO_u8PIN4,&Local_u8FanOpenStatus);

		if( (Local_u8FanOpenStatus == 0 ) || (Global_u8Rx_Data == '0') || (Local_u16Temp > 40) )
		{
			Global_u8FanFlag = 1 ;
		}
	}

	/* Exhaust Fan Section */

	if(3 == Local_u8Counter )
	{
		DIO_u8GetPinValue(DIO_u8PORTB,DIO_u8PIN6,&Local_u8ExhaustFanOpenStatus);

		if( (Local_u8ExhaustFanOpenStatus == 0 ) || (Global_u8Rx_Data == '1') )
		{
			Global_u8ExhaustFanFlag = 1 ;
		}
	}
	/* 7 Segment_1 */
	if(10 == Local_u8Counter)
	{
		SSD_u8Disable(&Seven_Segment2);
		Local_u16LM35DigitalValue = ADC_u16GetChannelReadingSynch(0);
		Local_u16Temp = ((Local_u16LM35DigitalValue * 60)/ 1023) ;
		Local_u16SSDValue = Local_u16Temp ;
		if(Local_u16SSDValue > 40 )
		{
			DIO_u8SetPinValue(DIO_u8PORTG,DIO_u8PIN0,DIO_u8PIN_HIGH);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTG,DIO_u8PIN0,DIO_u8PIN_LOW);
		}
		Local_u16SSDValue %= 10 ;
		SSD_u8SetNumber(Local_u16SSDValue,&Seven_Segment1);
		SSD_u8Enable(&Seven_Segment1);


	}


	/* LDR Section */
	else if (12 == Local_u8Counter )
	{
		if((ADC_u16GetChannelReadingSynch(1) < 50 )|| ('3' == Global_u8Rx_Data) )
		{
			DIO_u8SetPinValue(DIO_u8PORTG,DIO_u8PIN1, DIO_u8PIN_HIGH) ;
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTG,DIO_u8PIN1, DIO_u8PIN_LOW) ;
		}
	}

	/* Blinds Section */
	else if(14 == Local_u8Counter)
	{
		DIO_u8GetPinValue(DIO_u8PORTB, DIO_u8PIN0,&Local_u8BlindsOpenStatus);
		DIO_u8GetPinValue(DIO_u8PORTB, DIO_u8PIN1,&Local_u8BlindsCloseStatus);

		if( (((0 == Local_u8BlindsOpenStatus) || ('4' == Global_u8Rx_Data)) && (Global_u8BlindsState == BLINDS_CLOSED) ) )
		{
			Global_u8BlindsOpenFlag = 1 ;
			Global_u8BlindsState = BLINDS_OPEND ;
		}
		else if ( ( (0 == Local_u8BlindsCloseStatus || ('5' == Global_u8Rx_Data)) && (Global_u8BlindsState == BLINDS_OPEND) ) )
		{
			Global_u8BlindsCloseFlag = 1 ;
			Global_u8BlindsState = BLINDS_CLOSED ;
		}
		else
		{
			//Do Nothing
		}
	}

	else if (5 == Local_u8Counter)
	{
		Local_u8KeyValue = KPD_u8GetPressedKey();
		if('*' == Local_u8KeyValue)
		{
			Global_Password_u8Flag = 1 ;
		}
	}

	else if (18 == Local_u8Counter )
	{

		if('#' == Local_u8KeyValue)
		{
			Global_Password_u8Flag = 1 ;
			Global_Password_u8ChangeFlag = 1 ;
		}
		Local_u8KeyValue = 0xff ;
	}


	/* 7 Segment 2 */
	else if (20 == Local_u8Counter)
	{
		Local_u8Counter = 0 ;
		SSD_u8Disable(&Seven_Segment1);
		Local_u16LM35DigitalValue = ADC_u16GetChannelReadingSynch(0);
		Local_u16Temp = ((Local_u16LM35DigitalValue * 60)/ 1023) ;
		Local_u16SSDValue = Local_u16Temp ;
		Local_u16SSDValue /= 10 ;
		Local_u16SSDValue %= 10 ;
		SSD_u8SetNumber(Local_u16SSDValue,&Seven_Segment2);
		SSD_u8Enable(&Seven_Segment2);

	}
	Local_u8Counter++ ;
}

/* Sending Message By UART */
void send_voidChar(void)
{
	/* Future Feature */
}

/* Receiving Message By UART */
void receive_voidChar(void)
{
	Global_u8Rx_Data = UART_u8ReceiveData();

	enable_tx();
	UART_voidSendData_Asynch(Global_u8Rx_Data);
	disable_tx();
	if('2' == Global_u8Rx_Data)
	{
		DCMOTOR_voidStop();
	}
}

