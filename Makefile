CC = gcc
CFLAGS = -Wall -Wextra -g -std=gnu99 
BINDIR = bin
SRCDIR = src
EXEC = main
HDIR = lib/aihelper

default: main

main: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $<

logic: $(SRCDIR)/logic.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $<

xor: $(SRCDIR)/xor.c $(HDIR)/aihelper.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $< -I$(HDIR) lib/aihelper/aihelper.o

run: $(EXEC) 
	$(BINDIR)/$<
