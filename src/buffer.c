/*
 * Implements rudimentary character buffering
 */
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "util.h"
#include "buffer.h"

buffer_t *
buffer_new () {
	buffer_t *buf = calloc(1, sizeof *buf);

	if (!buf) {
		die("failed to allocate buffer_t");
	}

	return buf;
}

void
buffer_free (buffer_t *buf) {
	free(buf->base);
	free(buf);
}

void
buffer_reset (buffer_t *buf) {
	buf->len = 0;
}

size_t
buffer_len (buffer_t *buf) {
	return buf->len;
}

size_t
buffer_realloc (buffer_t *buf, size_t n) {
	n += buf->cap;
	char *base = realloc(buf->base, n);

	if (!base) {
		die("could not reallocate buffer");
	}

	buf->base = base;
	buf->cap = n;

	return n;
}

size_t
buffer_nputs (buffer_t *buf, const char *s, size_t n) {
	if (buf->cap - buf->len < n) {
		buffer_realloc(buf, n - (buf->cap - buf->len) + 1);
	}

	n = strlen(strncpy(buf->base + buf->len, s, n));
	buf->len += n;

	return n;
}

size_t
buffer_puts (buffer_t *buf, const char *s) {
	return buffer_nputs(buf, s, strlen(s) + 1);
}

size_t
buffer_gets (buffer_t *buf, char *s, size_t n) {
	return strlen(strncpy(s, buf->base, n));
}

void
buffer_putc (buffer_t *buf, int c) {
	/* TODO: stub */
	return;
}

int
buffer_getc (buffer_t *buf) {
	/* TODO: stub */
	return '\0';
}

long
buffer_fgetd (buffer_t *buf, FILE *fp, int delim) {
	int c;
	long p, q;

	if ((p = ftell(fp)) == -1) {
		return -1;
	}

	while (1) {
		c = fgetc(fp);

		if (c == EOF) {
			return -1;
		}
		if (c == delim) {
			break;
		}
	}

	if ((q = ftell(fp)) == -1) {
		return -1;
	}

	if (fseek(fp, p, SEEK_SET) == -1) {
		return -1;
	}

	if (buf->cap - buf->len < q - p) {
		buffer_realloc(buf, q - p + 1);
	}

	fgets(buf->base + buf->len, q - p + 1, fp);
	buf->len += q - p;

	return q - p;
}

long
buffer_fget (buffer_t *buf, FILE *fp) {
	return buffer_fgetd(buf, fp, '\n');
}


size_t buffer_printf (buffer_t *buf, const char *fmt, ...) {

	int n;
	va_list ap1, ap2;

	va_start(ap1, fmt);
	va_copy(ap2, ap1);

	do {
		n = vsnprintf(buf->base + buf->len, buf->cap - buf->len, fmt, ap1);

		if (n >= buf->cap - buf->len) {
			buffer_realloc(buf, n - (buf->cap - buf->len) + 1);
			va_copy(ap1, ap2);
		} else {
			break;
		}

	} while (1);

	va_end(ap1);
	va_end(ap2);

	buf->len += n;
	return n;
}
