CC = gcc
CFLAGS = -Wall -Wextra -g -std=gnu99 
BINDIR = bin
SRCDIR = src
EXEC = equation 
HDIR = lib/aihelper

default: equation

equation: $(SRCDIR)/equation.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $< -I$(HDIR) lib/aihelper/aihelper.o

logic: $(SRCDIR)/logic.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $< -I$(HDIR) lib/aihelper/aihelper.o

xor: $(SRCDIR)/xor.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $< -I$(HDIR) lib/aihelper/aihelper.o

run: $(EXEC) 
	$(BINDIR)/$<
