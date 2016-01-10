

CFLAGS += -std=c99 -pedantic -Wall -Wno-deprecated-declarations
CFLAGS += $(shell pkg-config --cflags x11 alsa libmpdclient)

DFLAGS += -g3
OFLAGS += -Os

LDFLAGS := -lm $(shell pkg-config --libs x11 alsa libmpdclient)

ifeq ($(DEBUG),0)
	DEBUG=
endif

ifdef DEBUG
	CFLAGS += $(DFLAGS)
else 
	CFLAGS += $(OFLAGS)
endif

src := $(wildcard *.c)
obj := $(src:.c=.o)

all: dwmstatus

clean:
	$(RM) dwmstatus $(obj)
	$(MAKE) -C tests clean

test:
	$(MAKE) -C tests

dwmstatus: $(obj)
	$(CC) $(CFLAGS) -o$@ $^ $(LDFLAGS)

$(obj): %.o: %.c %.h util.h
	$(CC) -c $(CFLAGS) -o$@ $(filter %.c, $^)

.PHONY: all clean test
