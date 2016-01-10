#ifndef DWMSTATUS_UTIL_H
# define DWMSTATUS_UTIL_H

# include <stdlib.h>
# include <stdio.h>

# include "buffer.h"

# define dief(...) do { \
	fprintf(stderr, __VA_ARGS__); \
	exit(EXIT_FAILURE); \
} while (0)

# define die(m) dief(m "\n")

# define NELEMS(a) (sizeof (a) / sizeof (a)[0])

# ifndef NAN
# 	define NAN 0.0 / 0.0
# endif

extern int scan(buffer_t *buf, FILE *fp, const char **strings);

extern void progress(buffer_t *buf, size_t size, size_t progress,
	const char *start, const char *end,
	const char *s1, const char *s2, const char *sep);

#endif /* DWMSTATUS_UTIL_H */
