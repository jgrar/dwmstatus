#include <stdio.h>
#include <string.h>

#include <math.h>

#include "buffer.h"

/* Implements basic line scanning
 *
 * each element of strings is compared to lines read from fp and
 * buffered in buf, returns the index of the string found in the 
 * NULL terminated array strings, or EOF if there are errors or.. EOF.
 */
int
scan (buffer_t *buf, FILE *fp, const char **strings) {

	int i;


	while (1) {

		buffer_reset(buf);

		if (buffer_fget(buf, fp) == -1) {
			break;
		}

		for (i = 0; strings[i]; i++) {
			if (strncmp(buf->base, strings[i], strlen(strings[i])) == 0) {
				return i;
			}
		}
	}

	return EOF;
}

/* Implements basic progress bar, like mkb
 * TODO: test size < 3
 */
void
progress(buffer_t *buf, size_t size, size_t progress,
	const char *start, const char *end,
	const char *s1, const char *s2, const char *sep) {

	int i;
	int j = round((double)progress * size / 100);

	buffer_puts(buf, start);
	for (i = 0; i < size; i++) {

		if (i < j) {
			buffer_puts(buf, s1);

		} else if (i == j) {
			buffer_puts(buf, sep);

		} else {
			buffer_puts(buf, s2);
		}
	}
	buffer_puts(buf, end);

}
