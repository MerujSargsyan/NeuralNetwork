CC = gcc
CFLAGS = -Wall -Wextra -g -std=gnu99 
BINDIR = bin
CODEDIR = src/code
EXEC = equation 
HDIR = lib/aihelper

default: equation

equation: $(CODEDIR)/equation.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $< -I$(HDIR) lib/aihelper/aihelper.o

logic: $(CODEDIR)/logic.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $< -I$(HDIR) lib/aihelper/aihelper.o

xor: $(CODEDIR)/xor.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $< -I$(HDIR) lib/aihelper/aihelper.o

lib: aihelper.o

%.o: $(HDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(HDIR)/$@

run: $(EXEC) 
	$(BINDIR)/$<

clean: 
	rm -rf $(BINDIR)/*.dSYM
