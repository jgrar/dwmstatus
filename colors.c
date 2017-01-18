#include <string.h>

#include "buffer.h"

#include "colors.h"

const char *colors[] = {
	"\x01", "\x02", "\x03",
};

void
setcolor (buffer_t *buf, color_t color) {
	//buffer_write(buf, colors[color], strlen(colors[color]));
	buffer_printf(buf, colors[color]);
}

void
setcolor1 (buffer_t *buf) {
	setcolor(buf, COLOR1);
}

void
setcolor2 (buffer_t *buf) {
	setcolor(buf, COLOR2);
}

void
setcolor3 (buffer_t *buf) {
	setcolor(buf, COLOR3);
}

