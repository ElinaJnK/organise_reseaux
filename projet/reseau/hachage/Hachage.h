#ifndef __HACHAGE_H__ 
#define __HACHAGE_H__ 
#include "../liste/Reseau.h"

/*Structure de la table de hachage*/
typedef struct hachage{
	int taille;//longeur du tableau
  //liste chainee qui va contenir toutes les
  //noeuds
	int nbrElem;
  CellNoeud **tabcn;
}TableHachage;

//Fonctions complémentaires:
TableHachage* creer_hachage(int m);
Noeud* existeDansH(TableHachage *H, double x, double y);
void free_tableHachage(TableHachage *H);
//Fonctions obligatoires
int fonction_cle(double x, double y);
int clef(int k,int M);
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
Reseau* reconstitueReseauHachage(Chaines *C, int M);

#endif