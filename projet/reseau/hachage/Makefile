#makefile du dossier hachage

DEPS=Hachage.h ../liste/Reseau.h

CC=gcc 
CFLAGS=-g -Wall -Wextra -lm -pedantic

Hachage.o: Hachage.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)