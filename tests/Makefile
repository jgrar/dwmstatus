CFLAGS := $(CFLAGS) -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os

tests := $(patsubst %.c, %, $(wildcard *.c))

all: $(tests)
	for test in $(tests); \
	do \
		./$$test; \
	done

$(tests): %-test: %-test.c ../%.o ../%.h test.h ../util.h
	$(CC) $(CFLAGS) -o$@ $(filter-out %.h, $^)

# deal w/ it
../%o:
	$(MAKE) -C ../ $(patsubst ../%, %, $@)
clean:
	$(RM) $(tests)

.PHONY: all clean
