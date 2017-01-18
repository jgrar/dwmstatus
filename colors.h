#ifndef DWMSTATUS_COLORS_H
# define DWMSTATUS_COLORS_H

# include "buffer.h"

typedef enum {
	COLOR1,
	COLOR2,
	COLOR3,

	NORMAL = COLOR1,
	SELECTED = COLOR2,
	URGENT = COLOR3,
} color_t;

extern void setcolor(buffer_t *buf, color_t color);

extern void setcolor1(buffer_t *buf);

extern void setcolor2(buffer_t *buf);

extern void setcolor3(buffer_t *buf);

#endif /* DWMSTATUS_COLORS_H */
