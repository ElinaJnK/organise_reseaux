#ifndef __RESEAU_H__ 
#define __RESEAU_H__ 
#include "../../chaine/Chaine.h"

typedef struct noeud Noeud;
/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
  
typedef struct cellnoeud { 
  Noeud *nd;
  struct cellnoeud *suiv; 
} CellNoeud;
/* Noeud du reseau */
struct noeud{ 
	int num;
  double x, y; 
  CellNoeud *voisins;
};
/* Liste chainee de commodites */
  
/* Pointeur vers le noeud stock\’e */
/* Cellule suivante dans la liste */
/* Numero du noeud */
/* Coordonnees du noeud*/
/* Liste des voisins du noeud */
 
typedef struct cellCommodite { 
  Noeud *extrA, *extrB; 
	struct cellCommodite *suiv;
} CellCommodite;
/* Un reseau */
typedef struct { 
  int nbNoeuds;
  int gamma;
  CellNoeud *noeuds; 
  CellCommodite *commodites;
} Reseau;
/* Noeuds aux extremites de la commodite */
/* Cellule suivante dans la liste */
/* Nombre de noeuds du reseau */
/* Nombre maximal de fibres par cable */ /* Liste des noeuds du reseau */
/* Liste des commodites a relier */
  
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y); 
Reseau* reconstitueReseauListe(Chaines *C);
void ecrireReseau(Reseau *R, FILE *f);
int nbLiaisons(Reseau *R);
int nbCommodites(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance); 


//Fonctions supplementaires
Noeud* creer_noeud(double x,double y, int num);
void inserer_noeud(Reseau *R, Noeud* n);
void liberer_cellNoeud(CellNoeud* cellN);
void liberer_reseau(Reseau *R);
Reseau *creer_reseau(int nbNoeuds, int gamma);
CellCommodite *creer_commoditie(Noeud *extrA , Noeud *extrB);
void liberer_cellcommodite(CellCommodite *cell);
CellNoeud *creer_cellnoeud();
int existeLiaison(Noeud *pren, Noeud *curn);
Noeud *trouverNoeudR(Reseau *R, double x, double y);

#endif