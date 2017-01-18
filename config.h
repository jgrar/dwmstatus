#ifndef CONFIG_H
# define CONFIG_H

# include "colors.h"
# include "mpd.h"
# include "vol.h"
# include "mem.h"
# include "cpu.h"
# include "clock.h"

static unsigned int delay = 1;

static const initfn_t Initfns[] = {
	initcpu,
};

static const statusfn_t Statusfns[] = {
	setcolor2,
	mpd_status,
	vol,
	mem,
	cpu,
	clock_status,
};

#endif /* CONFIG_H */
