#makefile du dossier arbre

DEPS=ArbreQuat.h ../liste/Reseau.h

CC=gcc -ggdb
CFLAGS=-g -Wall -Wextra -lm -pedantic -fsanitize=address

ArbreQuat.o: ArbreQuat.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)