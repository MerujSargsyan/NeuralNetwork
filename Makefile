CC = gcc
CFLAGS = -Wall -Wextra -g -std=gnu99 
BINDIR = bin
SRCDIR = src

all: main

main: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $<

run: main
	$(BINDIR)/main
