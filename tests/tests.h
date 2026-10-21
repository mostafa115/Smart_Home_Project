#ifndef TESTS_H_
#define TESTS_H_

void test_bit_math_set_clear_toggle_get(void);

void test_ssd_draws_every_digit(void);
void test_ssd_only_touches_segment_pins(void);
void test_ssd_enable_and_disable(void);

void test_kpd_no_key_pressed(void);
void test_kpd_maps_every_key(void);

void test_dc_motor_directions(void);
void test_dc_motor_never_energises_both_relays(void);

#endif
