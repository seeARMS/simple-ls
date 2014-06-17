# simple-ls/Makefile
# Colin Armstrong

CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g


OBJS1=simple-ls.c

all: simple-ls

simple-ls: $(OBJS1) 
	$(LD) $(LDFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f simple-ls