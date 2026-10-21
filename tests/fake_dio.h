#ifndef FAKE_DIO_H_
#define FAKE_DIO_H_

#define FAKE_DIO_PORTS     7
#define FAKE_DIO_PINS      8
#define FAKE_DIO_UNSET     0xff

typedef struct {
	u8 port;
	u8 pin;
	u8 value;
} fake_dio_write_t;

/* Decides what an input pin reads. Without a hook a pin reads back the last
 * level written to it, or HIGH (pull-up) if it was never written. */
typedef u8 (*fake_dio_read_hook_t)(u8 port, u8 pin);

void fake_dio_reset(void);
void fake_dio_set_read_hook(fake_dio_read_hook_t hook);

u8  fake_dio_level(u8 port, u8 pin);
u16 fake_dio_write_count(void);
const fake_dio_write_t *fake_dio_write_at(u16 index);

#endif
