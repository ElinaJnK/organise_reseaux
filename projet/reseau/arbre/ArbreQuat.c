#include "ArbreQuat.h"
//Fonctions complémentaires
//valgrind --leak-check=yes ./ReconstitueReseau usa.cha 3

void libererNoeudArbre(ArbreQuat* a){
  /*Fonction de libération de l'arbre*/
  if(a){
    libererNoeudArbre(a->so);
    libererNoeudArbre(a->no);
    libererNoeudArbre(a->se);
		libererNoeudArbre(a->ne);
    free(a);
    }
}

//Q5.1
void chaineCoordMinMax(Chaines* C, double* xmin, double*
ymin, double* xmax, double* ymax){
  /*Fonction qui determine les coordonnees minimales et 
  maximales des points constituant les differentes 
  chaines du reseau*/
	
  CellPoint * cp = C->chaines->points;
  CellChaine *cha = C->chaines;
  *xmin = cp->x;
  *ymin = cp->y;
  *xmax = cp->x;
  *ymax = cp->y;
  while (cha){
    while (cp){
      if (cp->x < *xmin){
        *xmin = cp->x;
      }
      if (cp->y < *ymin){
        *ymin = cp->y;
      }
      if (cp->x > *xmax){
        *xmax = cp->x;
      }
      if (cp->y > *ymax){
        *ymax = cp->y;
      }
      cp = cp->suiv;
    }
    cha = cha->suiv;
  }
  return;
}

//Q5.2
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY){
  /*Fonction qui permet de creer une 
  cellule de l’arbre quaternaire,
  de centre (xc, yc), de longueur
  coteX et de hauteur coteY. 
  Cette fonction initialisera le nœud du reseau, 
  les arbres nord-ouest, nordest, sud-ouest et sud-est a NULL.*/
  ArbreQuat *abr = (ArbreQuat *)malloc(sizeof(ArbreQuat));
  abr->xc = xc;
  abr->yc = yc;
  abr->coteX = coteX;
  abr->coteY = coteY;
  abr->noeud = NULL;
  abr->no = NULL;
  abr->so = NULL;
  abr->se = NULL;
  abr->ne = NULL;
  return abr;
}

//Q5.3
void insererNoeudArbre(Noeud* n, ArbreQuat**a, ArbreQuat* parent){

  if((*a) == NULL){//Arbre vide
    double newCoteX=parent->coteX*1.0/2;
        double newCoteY=parent->coteY*1.0/2;
        double newXC, newYC;
        if(n->x >= parent->xc){
            newXC=parent->xc + parent->coteX*1.0/4;
        }
				else{
            newXC=parent->xc - parent->coteX*1.0/4;
        }
        if(n->y >= parent->yc){
            newYC=parent->yc + parent->coteY*1.0/4;
        }else{
            newYC=parent->yc - parent->coteY*1.0/4;
        }
        (*a) =creerArbreQuat(newXC, newYC, newCoteX, newCoteY);
    }
    else{
      if((*a)->noeud != NULL){ //Feuille
        Noeud* ntmp=(*a)->noeud;
       (*a)->noeud=NULL;
        if(ntmp->x < (*a)->xc){
          if(ntmp->y > (*a)->yc){
            insererNoeudArbre(ntmp, &((*a)->no), (*a));
          }else{
                    insererNoeudArbre(ntmp, &((*a)->so), (*a));
                }
            }else{
                if(ntmp->y > (*a)->yc){
                    insererNoeudArbre(ntmp, &((*a)->ne), (*a));
                }else{
                    insererNoeudArbre(ntmp, &((*a)->se), (*a));
                }
            }
			}
        if(n->x < (*a)->xc){
            if(n->y > (*a)->yc){
                insererNoeudArbre(n, &((*a)->no), (*a));
            }else{
                insererNoeudArbre(n, &((*a)->so), (*a));
            }
        }else{
            if(n->y > (*a)->yc){
                insererNoeudArbre(n, &((*a)->ne), (*a));
            }else{
                insererNoeudArbre(n, &((*a)->se), (*a));
            }
        }
    }
}


//Q5.4
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){
  /*Fonction qui retourne un Noeud du reseau R correspondant au point de coordonnees (x,y) dans l’arbre quaternaire. Trois cas sont à distinguer (arbre vide, feuille et cellule interne)*/
  /*Arbre vide*/
  if(*a == NULL){
    //On crée le noeud
    Noeud* nd=creer_noeud(x, y, R->nbNoeuds+1);
    if(!nd){
      fprintf(stderr, "Erreur d'allocation du Noeud\n");
      return NULL;
    }
		inserer_noeud(R, nd);
    insererNoeudArbre(nd,a,parent);
    return nd;
  	}
		else{
    /*Feuille*/
    if(((*a)->noeud != NULL)){
      if((*a)->noeud->x==x && (*a)->noeud->y==y){
        return (*a)->noeud;
	  	}
      else{
        if(((*a)->xc>=x) && ((*a)->yc>=y)){
          return rechercheCreeNoeudArbre(R,&((*a)->no),*a,x,y);}
        if(((*a)->xc>=x) && ((*a)->yc < y)){
          return rechercheCreeNoeudArbre(R,&((*a)->so),*a,x,y);}
        if(((*a)->xc < x) && ((*a)->yc>=y)){
          return rechercheCreeNoeudArbre(R,&((*a)->se),*a,x,y);}
        if(((*a)->xc < x) && ((*a)->yc <y)){
          return rechercheCreeNoeudArbre(R,&((*a)->ne),*a,x,y);}
      }
    }else{
      /*Cellule interne*/
	  if((*a != NULL)&& ((*a)->noeud == NULL)){
        if(((*a)->xc>=x) && ((*a)->yc>=y)){
          return rechercheCreeNoeudArbre(R,&((*a)->no),*a,x,y);}
        if(((*a)->xc>=x) && ((*a)->yc < y)){
          return rechercheCreeNoeudArbre(R,&((*a)->so),*a,x,y);}
        if(((*a)->xc < x) && ((*a)->yc>=y)){
          return rechercheCreeNoeudArbre(R,&((*a)->se),*a,x,y);}
        if(((*a)->xc < x) && ((*a)->yc <y)){
          return rechercheCreeNoeudArbre(R,&((*a)->ne),*a,x,y);}
      }
    }
  }
  return NULL;
}

//Q5.5
Reseau* reconstitueReseauArbre(Chaines *C){
	Reseau *R = creer_reseau(0,C->gamma);
	CellCommodite *commod = NULL;
	CellChaine *chaine = C->chaines;//pointeurs pour parcourir la chaine dans C
	CellPoint *pt = NULL;//pointeurs pour parcourir la chaine dans C
	Noeud *pren = NULL;//stocker un noeud précédent
	Noeud *curn = NULL;//stocker un noeud courant
	CellNoeud *curcelln = NULL;//un CellNoeud courant
	CellNoeud *precelln = NULL;//un CellNoeud précédent
	double xmin, ymin,  xmax,  ymax;
	ArbreQuat **a = (ArbreQuat**)malloc(sizeof(ArbreQuat*));
	(*a) = NULL;
	chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
	ArbreQuat *parent_init = creerArbreQuat((xmax - xmin) * 1.0/2, (ymax - ymin) * 1.0/2, xmax - xmin, ymax - ymin);

	while (chaine){
		pt = chaine->points;
		pren=NULL;
		while (pt){
			Noeud *pnd = rechercheCreeNoeudArbre(R, a, parent_init, pt->x, pt->y);
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
	free(parent_init);
	libererNoeudArbre((*a));
	free(a);
	return R;
}