#makefile du dossier chaine

DEPS=Chaine.h ../SVGwriter.h

CC=gcc 
CFLAGS=-g -Wall -Wextra -lm

PROGS=ChaineMain

OBJS=Chaine.o ChaineMain.o

ChaineMain: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(PROGS)

re: fclean all

.PHONY: clean flcean re all