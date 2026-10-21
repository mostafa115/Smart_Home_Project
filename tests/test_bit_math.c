#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "unit.h"
#include "tests.h"

void test_bit_math_set_clear_toggle_get(void)
{
	u8 reg = 0;

	SET_BIT(reg, 0);
	SET_BIT(reg, 7);
	CHECK_EQ(reg, 0x81);

	CLR_BIT(reg, 0);
	CHECK_EQ(reg, 0x80);

	TOGGLE_BIT(reg, 7);
	TOGGLE_BIT(reg, 3);
	CHECK_EQ(reg, 0x08);

	CHECK_EQ(GET_BIT(reg, 3), 1);
	CHECK_EQ(GET_BIT(reg, 4), 0);
}
