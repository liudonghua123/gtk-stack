ALL_EXES=$(shell ls *.exe 2>/dev/null)
.PHONY:  all clean
.PRECIOUS: %.exe

CC=gcc
CFLAGS=-g -Wall
GTKFLAGS=$(shell pkg-config --cflags gtk+-3.0)
GTKLIBS=$(shell pkg-config --libs gtk+-3.0)
PWD=$(shell pwd)

clean:
	@echo cleanning $(shell ls *.exe 2>/dev/null)
	$(shell sh -c "rm *.exe 2>/dev/null")

%.exe: %.c
	@echo building $<
	$(CC) $(GTKFLAGS) -o $@ $< $(GTKLIBS) $(CFLAGS) 

run_%: %.exe
	@echo running $<
	$(PWD)/$<

gtk-stack.exe: gtk-stack.c stack.c
	$(CC) $(GTKFLAGS) -o $@ $^ $(GTKLIBS) $(CFLAGS) 