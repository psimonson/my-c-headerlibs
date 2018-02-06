# Makefile for network samples
# Create by Philip "5n4k3" Simonson
##################################################

CC=gcc
CFLAGS=-std=c89 -Wall -Wno-unused-function
LDFLAGS=
LIBS=

TARGETS=test1

.PHONY: all clean
all: test1

test1: test1.c.o
	@echo CC $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

%.c.o: %.c
	@echo CC $(CFLAGS) -c $< -o $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo Cleaning...
	@rm -f *.c.o $(TARGETS)
	@echo Done!

