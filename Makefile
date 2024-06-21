CC = gcc
CFLAGS = -Wall -Wextra -g 
BINDIR = bin
SRCDIR = src

all: main

main: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $<

run: main
	$(BINDIR)/main
