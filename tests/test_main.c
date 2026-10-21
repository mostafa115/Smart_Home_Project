#include "unit.h"
#include "tests.h"

int main(void)
{
	unit_run("bit math: set, clear, toggle and get", test_bit_math_set_clear_toggle_get);

	unit_run("seven segment: draws digits 0-9", test_ssd_draws_every_digit);
	unit_run("seven segment: writes only segment pins", test_ssd_only_touches_segment_pins);
	unit_run("seven segment: enable drives LOW, disable drives HIGH", test_ssd_enable_and_disable);

	unit_run("keypad: no key pressed", test_kpd_no_key_pressed);
	unit_run("keypad: maps all 16 keys and waits for release", test_kpd_maps_every_key);

	unit_run("dc motor: clockwise, counter-clockwise and stop", test_dc_motor_directions);
	unit_run("dc motor: both relays are never on together", test_dc_motor_never_energises_both_relays);

	return unit_summary();
}
