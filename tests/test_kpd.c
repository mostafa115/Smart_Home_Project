#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KPD_config.h"
#include "KPD_interface.h"

#include "fake_dio.h"
#include "unit.h"
#include "tests.h"

#define RELEASE_AFTER_READS  3

static const u8 row_pins[4]    = { KPD_ROW0_PIN, KPD_ROW1_PIN, KPD_ROW2_PIN, KPD_ROW3_PIN };
static const u8 column_pins[4] = { KPD_COLUMN0_PIN, KPD_COLUMN1_PIN, KPD_COLUMN2_PIN, KPD_COLUMN3_PIN };
static const u8 keymap[4][4]   = KPD_ARR_VAL;

static int pressed_row = -1;
static int pressed_column = -1;
static int reads_until_release;

/* A pressed key connects its column to its row. With pull-ups on the rows,
 * the row reads LOW only while that column is driven LOW. */
static u8 keypad_matrix(u8 port, u8 pin)
{
	if (port != KPD_PORT || pressed_row < 0 || pin != row_pins[pressed_row])
		return DIO_u8PIN_HIGH;
	if (fake_dio_level(KPD_PORT, column_pins[pressed_column]) != DIO_u8PIN_LOW)
		return DIO_u8PIN_HIGH;
	if (reads_until_release == 0)
		return DIO_u8PIN_HIGH;

	reads_until_release--;
	return DIO_u8PIN_LOW;
}

/* Same state PORT_voidInt leaves behind: every column idles HIGH */
static void keypad_setup(int row, int column)
{
	u8 c;

	fake_dio_reset();
	for (c = 0; c < 4; c++)
		DIO_u8SetPinValue(KPD_PORT, column_pins[c], DIO_u8PIN_HIGH);

	pressed_row = row;
	pressed_column = column;
	reads_until_release = RELEASE_AFTER_READS;
	fake_dio_set_read_hook(keypad_matrix);
}

static int all_columns_idle(void)
{
	u8 c;

	for (c = 0; c < 4; c++)
		if (fake_dio_level(KPD_PORT, column_pins[c]) != DIO_u8PIN_HIGH)
			return 0;
	return 1;
}

void test_kpd_no_key_pressed(void)
{
	keypad_setup(-1, -1);

	CHECK_EQ(KPD_u8GetPressedKey(), KPD_No_Pressed_Key);
	CHECK(all_columns_idle());
}

void test_kpd_maps_every_key(void)
{
	int row, column;

	for (row = 0; row < 4; row++) {
		for (column = 0; column < 4; column++) {
			int key = row * 4 + column;

			keypad_setup(row, column);
			CHECK_EQ_AT(KPD_u8GetPressedKey(), keymap[row][column], key);
			CHECK_EQ_AT(reads_until_release, 0, key);
			CHECK_EQ_AT(all_columns_idle(), 1, key);
		}
	}
}
