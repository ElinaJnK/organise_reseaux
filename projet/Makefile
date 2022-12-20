#makefile du dossier liste

DEPS=SVGwriter.h

CC=gcc 
CFLAGS=-g -Wall -Wextra -lm

SVGwriter.o: SVGwriter.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)