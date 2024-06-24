CC = gcc
CFLAGS = -Wall -Wextra -g -std=gnu99 
BINDIR = bin
SRCDIR = src
EXEC = main

default: main

main: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $<

logic: $(SRCDIR)/logic.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $<

xor: $(SRCDIR)/xor.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $<

run: $(EXEC) 
	$(BINDIR)/$<
