#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "buffer.h"
#include "util.h"

#include "cpu.h"

#define CPU_STAT_FILE "/proc/stat"
#define CPU_USAGE_ICON "\uE30D"

static long double previdle;
static long double prevtotal;

void
initcpu () {
	cpu(NULL);
}

void
cpu (buffer_t *buf) {
	FILE *fp = fopen(CPU_STAT_FILE, "r");

	long double user, nice, system, idle = 0, iowait, irq, softirq, steal,
		nonidle, total = 0, totald, idled, percent = NAN;

	if (fp) {
		fscanf(fp, 
			"cpu %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf",
			&user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal
		);

		fclose(fp);

		/* TODO: somewhere in here i'm supposed to divide by
		 * sysconf(_SC_CLK_TCK) ...I think */
		idle = idle + iowait;
		nonidle = user + nice + system + irq + softirq + steal;

		total = idle + nonidle;

		totald = total - prevtotal;
		idled = idle - previdle;

		previdle = idle;
		prevtotal = total;

		percent = (totald - idled) / totald * 100;
	} else {
		fprintf(stderr, "couldn't open: \""CPU_STAT_FILE"\": %s\n", strerror(errno));
		percent = 0.0 / 0.0; // FIXME: give me a NaN!
	}

	if (buf) {
		buffer_printf(buf, " "CPU_USAGE_ICON " %02.0Lf%% ", percent);
	}

}

