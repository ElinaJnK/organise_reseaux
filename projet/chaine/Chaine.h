#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define LENBUF 10000

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

//fonctions demandées
Chaines* lectureChaines(FILE *f);
void ecrireChaines(Chaines *C, FILE *f);
void afficheChainesSVG(Chaines *C, char* nomInstance);
double longueurTotale(Chaines *C);
//Q1.3
void afficheChainesSVG(Chaines *C, char* nomInstance);
//Q1.4
double longueurChaine(CellChaine *c);
//Q1.5
int comptePointsTotal(Chaines *C);
//Q6.2
Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax,int ymax);

//fonctions "maison"
CellPoint	*creer_cellpoint(double x, double y);
Chaines *creer_chaines(int nb_chaine, int gamma);
CellChaine *creer_cellchaine(int num);
CellPoint *inserer_cellpoint(CellChaine *cc, double x, double y);
CellChaine *inserer_cellchaine(Chaines *ptrc, int num);
int compte_cellpoints(CellChaine *cellC);
//desallocation
void free_cellchaine(CellChaine *cell);
void free_cellpoint(CellPoint *cell);
void free_chaines(Chaines *cell);
//affichage
void aff_cellpoint(CellPoint *cell);
void aff_cellchaine(CellChaine *cell);
void aff_chaines(Chaines *cell);
#endif