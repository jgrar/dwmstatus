#ifndef DWMSTATUS_TEST_H
# define DWMSTATUS_TEST_H

# include <stdlib.h>
# include <assert.h>
# include "../util.h"

typedef bool (*testfn_t)();

# define PASS() return true

# define FAIL(...) do { \
	fprintf(stderr, __VA_ARGS__); \
	return false; \
} while (0)

# define TESTS static const testfn_t tests[]

# define RUN_TESTS() \
	int main () { \
		int i; \
		for (i = 0; i < NELEMS(tests); i++) { \
			assert(tests[i]()); \
		} \
		exit(EXIT_SUCCESS); \
	}

#endif /* DWMSTATUS_TEST_H */
