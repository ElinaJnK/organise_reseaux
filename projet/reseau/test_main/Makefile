#makefile du dossier test_main

Pl=../liste/
Ph=../hachage/
Pa=../arbre/
Pch=../../chaine/

DEPS=$(Pl)Reseau.h $(Pa)ArbreQuat.h $(Ph)Hachage.h $(Pch)Chaine.h ../../SVGwriter.h

CC=gcc 
CFLAGS=-g -Wall -Wextra -lm

PROGS=ReconstitueReseau exercice_6_vitesse

OBJS=$(Pl)Reseau.o $(Pa)ArbreQuat.o $(Ph)Hachage.o $(Pch)Chaine.o ../../SVGwriter.o 

OBJS2 =  exercice_6_vitesse.o ReconstitueReseau.o

exercice_6_vitesse: exercice_6_vitesse.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

ReconstitueReseau:ReconstitueReseau.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

all: ReconstitueReseau exercice_6_vitesse
	+$(MAKE) -C ../liste
	+$(MAKE) -C ../hachage
	+$(MAKE) -C ../arbre
	+$(MAKE) -C ../../.

clean:
	rm -f $(OBJS) $(OBJS2)

fclean: clean
	rm -f $(PROGS)

re: fclean all

.PHONY: clean flcean re all