#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DC_MOTOR_config.h"
#include "DC_MOTOR_interface.h"

#include "fake_dio.h"
#include "unit.h"
#include "tests.h"

#define RELAY1()  fake_dio_level(relay1_Port, relay1_TransistorBase_Pin)
#define RELAY2()  fake_dio_level(relay2_Port, relay2_TransistorBase_Pin)

void test_dc_motor_directions(void)
{
	fake_dio_reset();

	DCMOTOR_voidRotateClockWise();
	CHECK_EQ(RELAY1(), DIO_u8PIN_HIGH);
	CHECK_EQ(RELAY2(), DIO_u8PIN_LOW);

	DCMOTOR_voidRotateUntiClockWise();
	CHECK_EQ(RELAY1(), DIO_u8PIN_LOW);
	CHECK_EQ(RELAY2(), DIO_u8PIN_HIGH);

	DCMOTOR_voidStop();
	CHECK_EQ(RELAY1(), DIO_u8PIN_LOW);
	CHECK_EQ(RELAY2(), DIO_u8PIN_LOW);
}

/* Both relays on at the same time would short the supply through the motor
 * circuit, even if only for one instruction while switching direction.
 * Replay every pin write and check the state after each one. */
void test_dc_motor_never_energises_both_relays(void)
{
	u8 relay1 = DIO_u8PIN_LOW, relay2 = DIO_u8PIN_LOW;
	u16 i;

	fake_dio_reset();
	DCMOTOR_voidRotateClockWise();
	DCMOTOR_voidRotateUntiClockWise();
	DCMOTOR_voidRotateClockWise();
	DCMOTOR_voidStop();
	DCMOTOR_voidRotateUntiClockWise();

	for (i = 0; i < fake_dio_write_count(); i++) {
		const fake_dio_write_t *w = fake_dio_write_at(i);

		if (w->port == relay1_Port && w->pin == relay1_TransistorBase_Pin)
			relay1 = w->value;
		if (w->port == relay2_Port && w->pin == relay2_TransistorBase_Pin)
			relay2 = w->value;
		CHECK_EQ_AT(relay1 == DIO_u8PIN_HIGH && relay2 == DIO_u8PIN_HIGH, 0, i);
	}
}
