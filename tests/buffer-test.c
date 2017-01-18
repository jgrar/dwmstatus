//#include <stdlib.h>
//#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../buffer.h"

#include "test.h"

#define DUMP_BUFFER() \
	printf("base: \"%s\" len: %lu cap: %lu\n", buf->base, buf->len, buf->cap);

// TODO:
bool
test_buffer_read () {
	PASS();
}

// TODO:
bool
test_buffer_write () {
	PASS();
}

// TODO: these tests suck
bool
test_buffer_printf () {
	size_t n = 0;
	buffer_t *buf = buffer_new();

	if (!buf) {
		FAIL("buffer_new() failed\n");
	}

	n = buffer_printf(buf, "%s", "Hello, world!");
	DUMP_BUFFER();
	printf("n: %lu, strlen(\"Hello, world!\"): %lu\n", n, strlen("Hello, world!"));
	if (n != strlen("Hello, world!")) {
		FAIL("buffer_printf() \"Hello world!\" failed\n");
	}


	n = buffer_printf(buf, "%d %d", 345, 543);
	DUMP_BUFFER();
	printf("n: %lu, strlen(\"345 543\"): %lu\n", n, strlen("345 543"));
	if (n != strlen("345 543")) {
		FAIL("buffer_printf() \"345 543\" failed\n");
	}


	n = buffer_printf(buf, "%s",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	);
	DUMP_BUFFER();

	if (n !=
		strlen(
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		)
	) {
		FAIL("buffer_printf() - big print failed");
	}

	PASS();
}

TESTS = {
	test_buffer_read,
	test_buffer_write,
	test_buffer_printf,
};

RUN_TESTS()
