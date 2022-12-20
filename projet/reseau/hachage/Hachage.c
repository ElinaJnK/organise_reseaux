#include "Hachage.h"

//Fonctions complémentaires
TableHachage* creer_hachage(int taille){
  TableHachage *nh = (TableHachage *)malloc(sizeof(TableHachage));
	if (!nh){
		printf("Erreur d'allocation hachage\n");
		return NULL;
	}
	nh->tabcn = (CellNoeud**)malloc(sizeof(CellNoeud*) * taille);
	nh->taille  = taille;
	nh->nbrElem = 0;
	for (int i = 0; i < taille; i ++){
		nh->tabcn[i]=NULL;
	}
  return nh;
}

Noeud* existeDansH(TableHachage *H, double x, double y){
  /*Fonction qui verifie si un point (x,y) existe dans H*/
  //On calcule tout d'abord la valeur avec notre 
  //fonction de hachage 
  int res = clef(fonction_cle(x,y), H->taille);
	CellNoeud *cellnd = NULL;
	if (!H || !H->tabcn){
		printf("le tableau d'hachage est NULL\n");
		return NULL;
	}
	cellnd = H->tabcn[res];
	while (cellnd){
		if (cellnd->nd->x == x && cellnd->nd->y == y)
			return cellnd->nd;
		cellnd = cellnd->suiv;
	}
	return NULL;
}

void free_hachage(TableHachage *H){
  /*Fonction pour libérer la table de hachage.*/
	for (int i = 0; i < H->taille; i++){
		CellNoeud *tmp;
		CellNoeud *cn = H->tabcn[i];
		while (cn){
			tmp = cn;
			cn = cn->suiv;
			free(tmp);
		}
	}
	free(H->tabcn);
	free(H);
}

void free_hachagecn(TableHachage *H){
  /*Fonction pour libérer la table de hachage.*/
	free(H->tabcn);
	free(H);
}

//Fonctions obligatoires

//Q4.2
int fonction_cle(double x, double y){
  /*Fonction qui va attribuer une cle a un noeud 
  selon ses valeurs x et y*/
  return y+(x+y)*(x+y+1)/2;
}

//Q4.3
int clef(int k,int M){
  /*Fonction cle que l'on va preferer utiliser*/
  double A = (sqrt(5)-1)/2;
  //Pour récupérer la partie entière
  int kA = k*A;
  int res= M*((k*A) - kA);
  return res;
}

//Q4.4
Noeud* rechercheCreeNoeudHachage(Reseau* R,TableHachage* H, double x, double y){
  /*Fonction qui retourne un Noeud du reseau R correspondant au point (x, y) dans la
  table de hachage H. 
  Noter que si ce point existe dans H, la fonction retourne un point existant dans
  H et que, dans le cas contraire, la fonction cree un nœud et l’ajoute 
  dans H ainsi que dans la liste des
  nœuds du reseau de R.*/
  //on verifie ici s'il existe
  if (existeDansH(H, x, y)){
    return existeDansH(H, x, y);
  }
  //on regarde ou on va le placer 
	int cle_i = clef(fonction_cle(x,y), H->taille);

	//création d'un cellnoeud et d'un noeud
	CellNoeud *nvcellnd = creer_cellnoeud();
	H->nbrElem++;
	Noeud *n = creer_noeud(x, y, R->nbNoeuds + 1);
	nvcellnd->nd = n;
	inserer_noeud(R, n);
	//mettre le cellnoeud dans le tableau d'hachage
	nvcellnd->suiv = H->tabcn[cle_i];
	H->tabcn[cle_i]=nvcellnd;
	return nvcellnd->nd;
}

//Q4.5

Reseau* reconstitueReseauHachage(Chaines *C, int m){
	Reseau *R = creer_reseau(0,C->gamma);
	CellCommodite *commod = NULL;
	CellChaine *chaine = C->chaines;//pointeurs pour parcourir la chaine dans C
	CellPoint *pt = NULL;//pointeurs pour parcourir la chaine dans C
	Noeud *pren = NULL;//stocker un noeud précédent
	Noeud *curn = NULL;//stocker un noeud courant
	CellNoeud *curcelln = NULL;//un CellNoeud courant
	CellNoeud *precelln = NULL;//un CellNoeud précédent
	TableHachage *H = creer_hachage(m);

	while (chaine){
		pt = chaine->points;
		pren=NULL;
		while (pt){
			Noeud *pnd = rechercheCreeNoeudHachage(R,H,pt->x, pt->y);
			if (pren){//si on n'est pas au début de la chaîne
				curn = pnd;
				//vérifier s'il la liaison existe déjà dans la liste des voisins du noeud précédent
				if (existeLiaison(pren, curn) == 0){
					precelln = creer_cellnoeud();
					precelln->nd = curn;
					precelln->suiv = pren->voisins;
					pren->voisins = precelln;
				}
				//vérifier s'il la liaison existe déjà dans la liste des voisins du noeud courant
				if (existeLiaison(curn, pren) == 0){
					curcelln = creer_cellnoeud();
					curcelln->nd = pren;
					curcelln->suiv = curn->voisins;
					curn->voisins = curcelln;
				}
				pren = curn;
			}
			else {//si on est au début de la chaîne
				//hypothèse : une chaine a au moins 2 points
				pren = pnd;
				commod = creer_commoditie(pren,NULL);
				commod->suiv = 	R->commodites;
				R->commodites = commod;
			}
			if (!pt->suiv){
				commod->extrB = pnd;
			}
			pt = pt->suiv;
		}
		chaine = chaine->suiv;
	}
  free_hachage(H);
	return R;
}
