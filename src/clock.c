#include <string.h>
#include <errno.h>

#include <time.h>

#include "clock.h"

#include "buffer.h"
#include "util.h"

# define CLOCK_ICON "\uE192"
# define CLOCK_FMT " "CLOCK_ICON" %a %d %b %R"

/* threshold and hard step values are completely arbitrary */
# define CLOCK_STATUS_REALLOC_STEP() \
	(buf->cap - buf->len) <= 1 ? /* less than threshold? */ \
		buf->cap + 16: /* hard step the capacity */ \
		(buf->cap - buf->len)

void
clock_status (buffer_t *buf) {

	size_t n;
	time_t t;
	struct tm *tp;

	t = time(NULL);
	tp = localtime(&t);

	if (tp == NULL) {
		dief("localtime failed: %s\n", strerror(errno));
	}

	do {
		n = strftime(buf->base + buf->len, buf->cap - buf->len, CLOCK_FMT, tp);

		if (n == 0 && strlen(CLOCK_FMT) > 0 && strcmp(CLOCK_FMT, "%p") != 0) {
			buffer_realloc(buf, CLOCK_STATUS_REALLOC_STEP());
		} else {
			break;
		}

	} while (1);

	buf->len += n;
}
