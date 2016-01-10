#include <stdlib.h>

#include <unistd.h>

#include <X11/Xlib.h>

#include "buffer.h"
#include "util.h"

Display *Dpy;
static buffer_t *Statusbuf;

typedef void (*initfn_t)();

typedef void (*statusfn_t)(buffer_t *status);

#include "dwmstatus.h"

static void
init () {
	Dpy = XOpenDisplay(NULL);

	if (!Dpy) {
		die("No display, exiting");
	}

	Statusbuf = buffer_new();

	int i;
	for (i = 0; i < NELEMS(Initfns); i++) {
		if (Initfns[i]) {
			Initfns[i]();
		}
	}
}

static void
set_status () {
	int i;
	for (i = 0; i < NELEMS(Statusfns); i++) {
		if (Statusfns[i]) {
			Statusfns[i](Statusbuf);
		}
	}

	char s[buffer_len(Statusbuf) + 1];
	buffer_gets(Statusbuf, s, NELEMS(s));

	XStoreName(Dpy, DefaultRootWindow(Dpy), s);
	XSync(Dpy, False);

	buffer_reset(Statusbuf);
}

int
main () {
	init();

	while (1) {
		set_status();
		sleep(delay);
	}
}
