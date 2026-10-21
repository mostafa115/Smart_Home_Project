#include "STD_TYPES.h"
#include "DIO_interface.h"

#include "fake_dio.h"

#define FAKE_DIO_LOG_SIZE  256

static u8 levels[FAKE_DIO_PORTS][FAKE_DIO_PINS];
static fake_dio_write_t write_log[FAKE_DIO_LOG_SIZE];
static u16 write_count;
static fake_dio_read_hook_t read_hook;

void fake_dio_reset(void)
{
	u8 port, pin;

	for (port = 0; port < FAKE_DIO_PORTS; port++)
		for (pin = 0; pin < FAKE_DIO_PINS; pin++)
			levels[port][pin] = FAKE_DIO_UNSET;
	write_count = 0;
	read_hook = NULL;
}

void fake_dio_set_read_hook(fake_dio_read_hook_t hook)
{
	read_hook = hook;
}

u8 fake_dio_level(u8 port, u8 pin)
{
	return levels[port][pin];
}

u16 fake_dio_write_count(void)
{
	return write_count;
}

const fake_dio_write_t *fake_dio_write_at(u16 index)
{
	return &write_log[index];
}

u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	if (Copy_u8Port >= FAKE_DIO_PORTS || Copy_u8Pin >= FAKE_DIO_PINS)
		return NOK;

	levels[Copy_u8Port][Copy_u8Pin] = Copy_u8Value;
	if (write_count < FAKE_DIO_LOG_SIZE) {
		write_log[write_count].port = Copy_u8Port;
		write_log[write_count].pin = Copy_u8Pin;
		write_log[write_count].value = Copy_u8Value;
		write_count++;
	}
	return OK;
}

u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	u8 pin;

	if (Copy_u8Port >= FAKE_DIO_PORTS)
		return NOK;

	for (pin = 0; pin < FAKE_DIO_PINS; pin++)
		DIO_u8SetPinValue(Copy_u8Port, pin, (Copy_u8Value >> pin) & 1);
	return OK;
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_pu8Value)
{
	if (Copy_u8Port >= FAKE_DIO_PORTS || Copy_u8Pin >= FAKE_DIO_PINS)
		return NOK;

	if (read_hook != NULL)
		*Copy_pu8Value = read_hook(Copy_u8Port, Copy_u8Pin);
	else if (levels[Copy_u8Port][Copy_u8Pin] == FAKE_DIO_UNSET)
		*Copy_pu8Value = DIO_u8PIN_HIGH;
	else
		*Copy_pu8Value = levels[Copy_u8Port][Copy_u8Pin];
	return OK;
}
