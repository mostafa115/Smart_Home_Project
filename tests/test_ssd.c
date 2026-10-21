#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "SSD_interface.h"

#include "fake_dio.h"
#include "unit.h"
#include "tests.h"

/* Segments a..g that must be lit for each digit. Written independently of
 * the encoding table in SSD_interface.h. */
static const u8 expected_segments[10][7] = {
	/* a  b  c  d  e  f  g */
	{  1, 1, 1, 1, 1, 1, 0 },	/* 0 */
	{  0, 1, 1, 0, 0, 0, 0 },	/* 1 */
	{  1, 1, 0, 1, 1, 0, 1 },	/* 2 */
	{  1, 1, 1, 1, 0, 0, 1 },	/* 3 */
	{  0, 1, 1, 0, 0, 1, 1 },	/* 4 */
	{  1, 0, 1, 1, 0, 1, 1 },	/* 5 */
	{  1, 0, 1, 1, 1, 1, 1 },	/* 6 */
	{  1, 1, 1, 0, 0, 0, 0 },	/* 7 */
	{  1, 1, 1, 1, 1, 1, 1 },	/* 8 */
	{  1, 1, 1, 1, 0, 1, 1 },	/* 9 */
};

/* Segments are spread over different ports so a port/pin mix-up shows up */
static const u8 segment_port[7] = { DIO_u8PORTC, DIO_u8PORTA, DIO_u8PORTF, DIO_u8PORTC, DIO_u8PORTB, DIO_u8PORTE, DIO_u8PORTG };
static const u8 segment_pin[7]  = { DIO_u8PIN0,  DIO_u8PIN3,  DIO_u8PIN5,  DIO_u8PIN7,  DIO_u8PIN1,  DIO_u8PIN4,  DIO_u8PIN2 };

static ssd_t make_display(void)
{
	ssd_t display = {
		.COM_TYPE = Cathode,
		.PORT_0 = DIO_u8PORTC, .PIN_0 = DIO_u8PIN0,
		.PORT_1 = DIO_u8PORTA, .PIN_1 = DIO_u8PIN3,
		.PORT_2 = DIO_u8PORTF, .PIN_2 = DIO_u8PIN5,
		.PORT_3 = DIO_u8PORTC, .PIN_3 = DIO_u8PIN7,
		.PORT_4 = DIO_u8PORTB, .PIN_4 = DIO_u8PIN1,
		.PORT_5 = DIO_u8PORTE, .PIN_5 = DIO_u8PIN4,
		.PORT_6 = DIO_u8PORTG, .PIN_6 = DIO_u8PIN2,
		.EnablePort = DIO_u8PORTD, .EnablePin = DIO_u8PIN7,
	};
	return display;
}

void test_ssd_draws_every_digit(void)
{
	ssd_t display = make_display();
	u8 digit, segment;

	for (digit = 0; digit < 10; digit++) {
		fake_dio_reset();
		SSD_u8SetNumber(digit, &display);
		for (segment = 0; segment < 7; segment++)
			CHECK_EQ_AT(fake_dio_level(segment_port[segment], segment_pin[segment]),
				    expected_segments[digit][segment], digit * 10 + segment);
	}
}

void test_ssd_only_touches_segment_pins(void)
{
	ssd_t display = make_display();
	u16 i;
	u8 segment, is_segment_pin;

	fake_dio_reset();
	SSD_u8SetNumber(8, &display);

	CHECK_EQ(fake_dio_write_count(), 7);
	for (i = 0; i < fake_dio_write_count(); i++) {
		const fake_dio_write_t *w = fake_dio_write_at(i);

		is_segment_pin = 0;
		for (segment = 0; segment < 7; segment++)
			if (w->port == segment_port[segment] && w->pin == segment_pin[segment])
				is_segment_pin = 1;
		CHECK_EQ_AT(is_segment_pin, 1, i);
	}
}

void test_ssd_enable_and_disable(void)
{
	ssd_t display = make_display();

	fake_dio_reset();
	SSD_u8Enable(&display);
	CHECK_EQ(fake_dio_level(DIO_u8PORTD, DIO_u8PIN7), DIO_u8PIN_LOW);

	SSD_u8Disable(&display);
	CHECK_EQ(fake_dio_level(DIO_u8PORTD, DIO_u8PIN7), DIO_u8PIN_HIGH);
	CHECK_EQ(fake_dio_write_count(), 2);
}
