#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <X11/Xlib.h>

#include "util.h"

#define DELAY 1

#if 0
#include "mpd.h"
#include "vol.h"
#include "ram.h"
#include "cpu.h"
#include "clock.h"
#endif

#include "colors.h"
#include "cpu.h"

typedef void (*initfn_t)();
typedef int (*statusfn_t)(char *buf, size_t m);

static const initfn_t initfns[] = { initcpu };

static const statusfn_t statusfns[] = { setcolor1, cpu };

static char statusbuf[BUFSIZ];

static void
init () {
	int i;
	for (i = 0; i < NELEMS(initfns); i++) {
		if (initfns[i] != NULL) {
			initfns[i]();
		}
	}
}

static void
setstatus (void) {

	Display *dpy = XOpenDisplay(NULL);

	if (!dpy) {
		die("Could not open display");
	}

	int i, n, m = NELEMS(statusbuf) - 1;
	char *p = statusbuf;

	for (i = 0; i < NELEMS(statusfns) && m > 0; i++) {
		if (statusfns[i] != NULL) {

			n = statusfns[i](p, m);

			p += n;
			m -= n;
		}
	}

	XStoreName(dpy, DefaultRootWindow(dpy), statusbuf);
	XSync(dpy, 0);
	XCloseDisplay(dpy);
}

int main (int argc, char *argv[]) {

	init();

	while (1) {
		setstatus();
		sleep(DELAY);
	}
}
