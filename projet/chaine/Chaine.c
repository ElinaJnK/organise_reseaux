#include "Chaine.h"
#include "../SVGwriter.h"
#include <math.h>

//Creation allouée, désallocation et affichage
Chaines *creer_chaines(int nb_chaine, int gamma){
	Chaines *nv = malloc(sizeof(Chaines));
  if (!nv){
    printf("Erreur d'allocation dans creer_chaines\n");
    return NULL;
  }
  nv->nbChaines = nb_chaine;
  nv->gamma = gamma;
	nv->chaines = NULL; 
	return nv;
}

void free_chaines(Chaines *cell){ 
	free_cellchaine(cell->chaines);
	free(cell);
}

void aff_chaines(Chaines *cell){
	printf("Nb_chaines : %d\n", cell->nbChaines);
	printf("Gamma : %d\n", cell->gamma);
	aff_cellchaine(cell->chaines);
}

//CellChaine
CellChaine *creer_cellchaine(int num){
	CellChaine *nv = malloc(sizeof(CellChaine)); 
	if (!nv){
    printf("Erreur d'allocation dans creer_cellchaine\n");
    return NULL;
  }
	nv->numero = num;
	nv->points = NULL;
	nv->suiv = NULL;
	return nv;
}

void free_cellchaine(CellChaine *cell){
		CellChaine *tmp;
		while (cell){
			tmp = cell;
			free_cellpoint(cell->points);
			cell = cell->suiv;
			free(tmp);
		}
}

void aff_cellchaine(CellChaine *cell){
	while (cell){
		printf("%d ",cell->numero);
		aff_cellpoint(cell->points);
		printf("\n");
		cell = cell->suiv;
	}
}

//CellPoint
CellPoint	*creer_cellpoint(double x, double y){
	CellPoint *nv = (CellPoint*)malloc(sizeof(CellPoint)); 
	if (!nv){
    printf("Erreur d'allocation dans creer_cellpoint\n");
    return NULL;
  }
	nv->x = x;
	nv->y = y;
	nv->suiv = NULL;
	return nv;
}

void free_cellpoint(CellPoint *nv){
	CellPoint *tmp;
	while(nv){
		tmp = nv;
		nv = nv->suiv;
		free(tmp);
	}
}

void aff_cellpoint(CellPoint *cell){
	while (cell){
		printf(" %5f %5f",cell->x, cell->y);
		cell = cell->suiv;
	}
}

//Insertion
CellPoint *inserer_cellpoint(CellChaine *cc, double x, double y){
	if (!cc){
		printf("Cellchaine est vide.\n");
		return NULL;
  }
	CellPoint *cp = creer_cellpoint(x, y);
	if (!cp)
    return NULL;
	cp->suiv = cc->points;
  cc->points = cp;
	return cp;
}

CellChaine *inserer_cellchaine(Chaines *ptrc, int num){
	if (!ptrc){
    printf("Cellchaine est vide.\n");
    return NULL;
  }
	CellChaine *cc = creer_cellchaine(num);
	if (!cc)
    return NULL;
	cc->suiv = ptrc->chaines;
  ptrc->chaines = cc;
	return cc;
}
//Fonctions exigées
//Q1.1
Chaines* lectureChaines(FILE *f){
  /*Fonction transformant un fichier en structure Chaines*/
  Chaines *cha;
  char ligne[LENBUF];
  int gamma, nb_chaines;
	double x,y;
	int test;
	//tester fichier existe ou lisible
	//Lire nb_chaines et gamma
  char tmp[LENBUF];
	char tmp_bis[LENBUF];
	fgets(ligne, LENBUF, f);
	test = sscanf(ligne, "%s %d",tmp_bis, &nb_chaines);
	if (test != 2){
		printf("Erreur de format. Resulat de sscanf = %d et nb_chaines = %d\n", test, nb_chaines);
    return NULL;
  }
	fgets(ligne, LENBUF, f);
  printf("%s\n", ligne);
  if ((test = sscanf(ligne, "%s %d",tmp_bis, &gamma)) != 2){
    printf("Erreur de format.. Resulat de sscanf = %d et gamma = %d\n", test, gamma);
		return NULL;
  }
  if(!(cha = creer_chaines(nb_chaines, gamma)))
		return NULL;
	//Lire des coordonnées
  int i,nb_points;
  int k = 0;
	while(fgets(ligne, LENBUF, f)!= NULL){
		sscanf(ligne ," %d %d %[^\n]", &i ,&nb_points,tmp);
		CellChaine *c = inserer_cellchaine(cha, i);
		k = 0;
    while(k < nb_points){
			sscanf(tmp, " %lf %lf %[^\n]", &x, &y, tmp);
			CellPoint *cp = inserer_cellpoint(c, x, y);
			k++;
    }

	}
	return cha;
}

//Q1.2
void ecrireChaines(Chaines *C, FILE *f){
	/*Ecrit dans un fichier une chaine en respectant 
  le format d'origine*/
  fprintf(f,"NbChain: %d\n", C->nbChaines);
  fprintf(f,"Gamma: %d\n", C->gamma);

	CellPoint *ptrP;
	CellChaine *ptrC = C->chaines;
	int nb_cellP;
	int i = 0;

  while (ptrC){
		ptrP = ptrC->points;
		nb_cellP = compte_cellpoints(ptrC);
		fprintf(f,"%d %d",i, nb_cellP);
		while (ptrP){
    	fprintf(f," %5lf %5lf", ptrP->x ,ptrP->y);
			ptrP = ptrP->suiv;
		}
		i++;
		fprintf(f, "\n");
		ptrC = ptrC->suiv;
  }
}

//Q1.3
void afficheChainesSVG(Chaines *C, char* nomInstance){
    int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}

//Q1.4
double longueurChaine(CellChaine *c){
  /*Fonction qui calcule la longueur physique d'une chaine
  Attention: ne pas oublier d'utiliser -lm lors de la compilation*/
  int n = compte_cellpoints(c);
  double sum=0;
  CellPoint *cp = c->points;
  CellPoint *cp_suiv = cp->suiv; 
  for(int i = 0; i< n-1; i++){
    sum += sqrt(pow(cp_suiv->x - cp->x,2)+pow(cp_suiv->y - cp->y,2));
    cp = cp_suiv;
    cp_suiv = cp_suiv->suiv;
  }
  return sum;
}

double longueurTotale(Chaines *C){
  /*Fonction qui calcule la longueur totale des chaines*/
  double sum;
  CellChaine *cc = C->chaines;
  while (cc->suiv){
    sum += longueurChaine(cc);
    cc = cc->suiv;
  }
  return sum;
}

//Q1.5
int comptePointsTotal(Chaines *C){
  /*Fonction qui compte le nombre de points à partir de Chaines*/
  int i = 0;
	CellPoint *ptr = C->chaines->points;
	while(ptr){
			i++;
			ptr = ptr->suiv;
	}
	return (i);
}

//
int compte_cellpoints(CellChaine *cellP){
  /*Fonction qui compte le nombre de points à partir de CellChaine*/
	int i = 0;
	CellPoint *ptr = cellP->points;
	while(ptr){
			i++;
			ptr = ptr->suiv;
	}
	return (i);
}

//Q6.2
Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax,int ymax){
  /*Fonction qui permet de génerer des chaines aléatoires*/
  Chaines *cha = creer_chaines(nbChaines, nbPointsChaine);

  for (int i = 1; i <= nbChaines; i++){
		CellChaine *cc= inserer_cellchaine(cha, i);
		for (int j = 0; j < nbPointsChaine; j++){
			inserer_cellpoint(cc, rand() % (xmax + 1), rand() % (ymax + 1));
		}
  }
  afficheChainesSVG(cha, "Instance de test Generation Aleatoire\n");
	return cha;
}
//gcc -o test test.c
