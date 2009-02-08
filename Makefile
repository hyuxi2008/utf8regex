CFLAGS = -I. -O2 -Wall

H_FILES = $(wildcard *.h)
C_FILES = $(wildcard reg*.c)
O_FILES = regex.o utf8re-wchar.o

.PHONY: all
all: regex.o test

regex.o: $(C_FILES) $(H_FILES)

test.o: test.c $(H_FILES)

test: test.o $(O_FILES)

.PHONY: clean
clean:
	$(RM) *.o test

# vim:ts=4 sw=4 noet
