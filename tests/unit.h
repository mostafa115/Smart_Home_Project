#ifndef UNIT_H_
#define UNIT_H_

void unit_check_eq(long actual, long expected, const char *expr, long index, const char *file, int line);
int  unit_run(const char *name, void (*test)(void));
int  unit_summary(void);

#define UNIT_NO_INDEX  (-1L)

#define CHECK(cond) \
	unit_check_eq((long)((cond) != 0), 1L, #cond, UNIT_NO_INDEX, __FILE__, __LINE__)

#define CHECK_EQ(actual, expected) \
	unit_check_eq((long)(actual), (long)(expected), #actual " == " #expected, UNIT_NO_INDEX, __FILE__, __LINE__)

/* Same as CHECK_EQ, but reports which loop iteration failed */
#define CHECK_EQ_AT(actual, expected, index) \
	unit_check_eq((long)(actual), (long)(expected), #actual " == " #expected, (long)(index), __FILE__, __LINE__)

#endif
