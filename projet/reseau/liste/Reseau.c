#include "Reseau.h"

//Commande pour verifier les fuites de memoire:
//valgrind --leak-check=yes ./ReconstitueReseau
//Fonctions supplémentaires 
Noeud* creer_noeud(double x,double y, int num){
  /*Fonction qui creer un noeud*/
  Noeud * nv = (Noeud *)malloc(sizeof(Noeud));
	if (!nv){
		printf("Erreur d'allocation Noeud*\n");
		return NULL;
	}
	nv->num = num;
  nv->x = x;
  nv->y = y;
  nv->voisins = NULL;
  return nv;
}

void liberer_cellNoeud(CellNoeud* cellN){
	CellNoeud *tmp_celln;
	CellNoeud *voisin;
	Noeud *nd;
	while (cellN){
		nd = cellN->nd;
	
		if (nd){
			voisin = nd->voisins;
			while (voisin){
				tmp_celln = voisin;
				voisin = voisin->suiv;
				free(tmp_celln);
			}
			free(nd);
		}
		tmp_celln = cellN;
		cellN = cellN->suiv;
		free(tmp_celln);
	}
}

CellNoeud *creer_cellnoeud(){
	CellNoeud *nv = malloc(sizeof(CellNoeud));
  if (!nv){
    printf("Erreur dans l'allocation d'un CellNoeud");
    return NULL;
  }
	nv->suiv = NULL;
	nv->nd = NULL;
	return nv;
}

void inserer_noeud(Reseau *R, Noeud* n){
  /*Insere un noeud dans un reseau*/
	R->nbNoeuds++;
  CellNoeud *nv = malloc(sizeof(CellNoeud));
  if (!nv){
    printf("Erreur d'allocation du CellNoeud dans inserer_noeud()\n");
    return;
	}
  nv->nd = n;
  nv->suiv= R->noeuds;
  R->noeuds = nv;
}

Reseau *creer_reseau(int nbNoeuds, int gamma){
	Reseau *nv = malloc (sizeof(Reseau));
	if (!nv){
		printf("Erreur d'allocation de Reseau\n");
		return NULL;
	}
	nv->nbNoeuds = nbNoeuds;
	nv->gamma = gamma;
	nv->commodites = NULL;
	nv->noeuds = NULL;
	return nv;
}

void liberer_reseau(Reseau *R){
  /*Libere la memoire allouee pour un reseau*/
	if (!R){
		printf("Reseau == NULL: pas de libération nécessaire\n");
		return ;
	}
	liberer_cellNoeud(R->noeuds);
	liberer_cellcommodite(R->commodites);
  free(R);
}

CellCommodite *creer_commoditie(Noeud *extrA , Noeud *extrB){
	CellCommodite *nv = malloc(sizeof(CellCommodite));
	if (!nv){
		printf("Erreur d'allocation de commodités\n");
		return NULL;
	}
	nv->extrA = extrA;
	nv->extrB = extrB;
	nv->suiv = NULL;
  return nv;
}

void liberer_cellcommodite(CellCommodite *cell){
	CellCommodite *tmp;
	while (cell){
		tmp = cell;
		cell = cell->suiv;
		free(tmp);
	}
}

//Q2.1
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
  /*Fonction qui retourne un Noeud correspondant au point (x,y) dans la liste chainee noeud de R. Si ce noeud existe, on renvoie le noeud, sinon on creer un nouveau noeud et on le rajoute*/
  CellNoeud *cn = R->noeuds;
  while (cn){
    Noeud *n = cn->nd;
    if (n->x == x && n->y == y)
      return n;
    cn = cn->suiv;
  }
  Noeud *nouv = creer_noeud(x,y,R->nbNoeuds + 1);
	//R->nbNoeuds est incrémenté dans inserer_noeud()
	if (!nouv){
		printf("Erreur d'allocation dans rechercheCreeNoeudListe()\n");
		return NULL;
	}
  inserer_noeud(R, nouv);
  return nouv;
}

//Q2.2
Noeud *trouverNoeudR(Reseau *R, double x, double y){
	/*la fonction retourne un noeud dans R*/
	CellNoeud *cn= R->noeuds;
	while (cn){
		if (cn->nd->x == x && cn->nd->y == y){
			return cn->nd;
		}
		cn = cn->suiv;
	}
	return NULL;
}

int existeLiaison(Noeud *pren, Noeud *curn){
  /*Fonction supplémentaire pour reconstitueReseauListe()
  qui vérifie si le noeud curn existe déjà dans la liste des voisins du noeud pren*/
	CellNoeud *voisin =pren->voisins;
	while (voisin){
		if (curn->num == voisin->nd->num)
			return 1;
		voisin = voisin->suiv;
	}
	return 0;//retourne 0 si le numéro du noeud courant n'existe pas encore dans la liste des voisins du noeud précédent, et 1 sinon
}


Reseau* reconstitueReseauListe(Chaines *C){
	Reseau *R = creer_reseau(0,C->gamma);
	CellCommodite *commod = NULL;
	CellChaine *chaine = C->chaines;//pointeurs pour parcourir la chaine dans C
	CellPoint *pt = NULL;//pointeurs pour parcourir la chaine dans C
	Noeud *pren = NULL;//stocker un noeud précédent
	Noeud *curn = NULL;//stocker un noeud courant
	CellNoeud *curcelln = NULL;//un CellNoeud courant
	CellNoeud *precelln = NULL;//un CellNoeud précédent

	while (chaine){
		pt = chaine->points;
		pren=NULL;
		while (pt){
			Noeud *pnd = rechercheCreeNoeudListe(R, pt->x, pt->y);
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
			//if (pren->x == curn->x && pren->y == curn->y)
				//break;
			pt = pt->suiv;
		}
		chaine = chaine->suiv;
	}
	return R;
}

//Q3.1
int nbCommodites(Reseau *R){
  /*Donne le nombre de commodites*/
  int num=0;
  CellCommodite* cell_commod = R->commodites;
  if (!R->commodites){
    printf("Pas de commodités dans le réseau.\n");
    return num;
  }
  while(cell_commod != NULL){
    num++;
    cell_commod = cell_commod->suiv;
  }
  return num;
}

//Q3.1 
int nbLiaisons(Reseau *R){
  /*Donne le nombre de liaisons*/
 CellNoeud *cellnd = R->noeuds;
 Noeud *nd = NULL;
 CellNoeud *voisin = NULL;
 int cpt  = 0;
 if (!cellnd)
	return 0;
 while (cellnd){
	 if (!cellnd->nd){
		 printf("cellnoeud->nd non initialisé\n");
		 return -1;
	 }
	 nd = cellnd->nd;
	 voisin = nd->voisins;
	 while (voisin){
		 if (voisin->nd->num < nd->num)
		 	cpt++;
		 voisin = voisin->suiv;
	 }
	 cellnd = cellnd->suiv;
 } 
 return cpt;
}

//Q3.2
void ecrireReseau(Reseau *R, FILE *f){
  /*Ecrit un reseau dans un fichier*/
  fprintf(f,"NbNoeuds: %d\n", R->nbNoeuds);
  fprintf(f,"NbLiaisons: %d\n", nbLiaisons(R));
  fprintf(f,"NbCommodites: %d\n", nbCommodites(R));
  fprintf(f,"Gamma: %d\n\n", R->gamma);
	
	CellNoeud *cn = R->noeuds;
	//afficher les noeuds et ses voisins
	CellNoeud *voisin = NULL;
	Noeud *n = NULL;
	CellCommodite *com = R->commodites;
	if (!cn)
		fprintf(f,"R->noeuds est vide\n");
	while(cn){
		fprintf(f, "v %d %lf %lf\n", cn->nd->num,  cn->nd->x, cn->nd->y);
		cn = cn->suiv;
	}
	fprintf(f, "\n");
	//afficher les liaisons
	cn  = R->noeuds;
	while(cn){
		n = cn->nd;
		voisin  = n->voisins;
		while (voisin){
			if(voisin->nd->num > n->num)
				fprintf(f, "l %d %d\n", n->num, voisin->nd->num);
			voisin = voisin->suiv;
		}
		cn = cn->suiv;
	}
	fprintf(f, "\n");
	//afficher les commodités
	while (com){
		fprintf(f, "k %d %d\n", com->extrA->num, com->extrB->num);
		com = com->suiv;
	}
}