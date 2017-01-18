#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "buffer.h"
#include "util.h"

#include "mem.h"

#define MEM_INFO_FILE "/proc/meminfo"
#define MEM_USAGE_ICON "\uE322"

typedef enum {
	MemTotal,
	MemFree,
	Cached,
	Buffers,
} meminfo_field_t;

static const char *Fields[] = {
	"MemTotal:",
	"MemFree:",
	"Cached:",
	"Buffers:",
	NULL
};

void
mem (buffer_t *buf) {
	buffer_t *line;

	FILE *fp = fopen(MEM_INFO_FILE, "r");

	long double percent = NAN;

	int i;

	if (fp) {
		unsigned long v[NELEMS(Fields)] = {0};
		line = buffer_new();

		while ((i = scan(line, fp, Fields)) != EOF) {
			v[i] = strtoul(line->base + strlen(Fields[i]), NULL, 10);
		}

		buffer_free(line);
		fclose(fp);

		long double used = v[MemTotal] - v[MemFree] - v[Buffers] - v[Cached];
		if (used < 0) {
			used = v[MemTotal] - v[MemFree];
		}

		percent = (used / v[MemTotal]) * 100;
	} else {
		fprintf(stderr, "Could not open \""MEM_INFO_FILE"\": %s", strerror(errno));
	}

	buffer_printf(buf, " "MEM_USAGE_ICON" %02.0Lf%% ", percent);
}
