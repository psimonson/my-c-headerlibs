# Makefile for miscellaneous samples
# Created by Philip "5n4k3" Simonson
##################################################

CC=gcc
CFLAGS=-std=c89 -g -Wall -Wno-unused-function
LDFLAGS=
LIBS=

TARGETS=test1 test2 test3 test4 test5 test6 test7

.PHONY: all clean
all: $(TARGETS)

test1: test1.c.o
	@echo CC $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

test2: test2.c.o
	@echo CC $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

test3: test3.c.o
	@echo CC $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

test4: test4.c.o
	@echo CC $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

test5: test5.c.o
	@echo CC $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

test6: test6.c.o
	@echo CC $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

test7: test7.c.o
	@echo CC $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

%.c.o: %.c
	@echo CC $(CFLAGS) -c $< -o $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo Cleaning...
	@rm -f *.tmp *.txt *.c.o $(TARGETS)
	@echo Done!

