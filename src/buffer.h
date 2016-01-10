/*
 * Implements rudimentary character buffering
 */

#ifndef DWMSTATUS_BUFFER_H
# define DWMSTATUS_BUFFER_H

# include <stdlib.h>
# include <stdio.h>

typedef struct {
	size_t len, cap;
	char *base;
} buffer_t;

extern buffer_t *buffer_new();

extern void buffer_free(buffer_t *buf);

extern void buffer_reset(buffer_t *buf);

extern size_t buffer_len(buffer_t *buf);

extern size_t buffer_realloc(buffer_t *buf, size_t n);

extern size_t buffer_nputs(buffer_t *buf, const char *s, size_t n);
extern size_t buffer_puts(buffer_t *buf, const char *s);

extern size_t buffer_gets(buffer_t *buf, char *s, size_t n);

extern void buffer_putc(buffer_t *buf, int c);

extern int buffer_getc(buffer_t *buf);

extern long buffer_fgetd(buffer_t *buf, FILE *fp, int delim);

extern long buffer_fget(buffer_t *buf, FILE *fp);


/* formatted print to buffer
 */
extern size_t buffer_printf(buffer_t *buf, const char *fmt, ...);

#endif /* DWMSTATUS_BUFFER_H */
