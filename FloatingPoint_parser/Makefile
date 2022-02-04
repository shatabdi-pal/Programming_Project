# This Makefile is set up for CS201 A3
# NOTE: All indented lines are indented with a tab character.
#       This is required.

CC=gcc
# flag all warnings. default optimization level.
CFLAGS=-Wall -Og 
# set up for use in gdb
DFLAGS=-g
LIBS= -lm
# For additional libraries, e.g. -lm
PROGS=	fp_parse 

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< $(LDFLAGS) $(LIBS) -o $@

clean:
	rm -f $(PROGS) *.o ~*

