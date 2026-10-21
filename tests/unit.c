#include <stdio.h>

#include "unit.h"

static int current_failed;
static int tests_run;
static int tests_failed;

void unit_check_eq(long actual, long expected, const char *expr, long index, const char *file, int line)
{
	if (actual == expected)
		return;

	if (index == UNIT_NO_INDEX)
		printf("    %s:%d: %s: got %ld, expected %ld\n", file, line, expr, actual, expected);
	else
		printf("    %s:%d: [%ld] %s: got %ld, expected %ld\n", file, line, index, expr, actual, expected);
	current_failed = 1;
}

int unit_run(const char *name, void (*test)(void))
{
	current_failed = 0;
	test();
	tests_run++;
	if (current_failed)
		tests_failed++;
	printf("%s  %s\n", current_failed ? "FAIL" : "ok  ", name);
	return current_failed;
}

int unit_summary(void)
{
	printf("\n%d tests, %d failed\n", tests_run, tests_failed);
	return tests_failed ? 1 : 0;
}
