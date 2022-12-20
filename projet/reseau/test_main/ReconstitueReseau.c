#include "../liste/Reseau.h"
#define N 10
#include "../../SVGwriter.h"
#include "../../chaine/Chaine.h"
#include "../hachage/Hachage.h"
#include "../arbre/ArbreQuat.h"
//valgrind --leak-check=yes ./ReconstitueReseau

//Q2.3
int main(int argc, char**argv){
  /*Main permettant de tester les fonctions de Reseau.c*/
  if (argc != 3 || atoi(argv[2]) <= 0 || atoi(argv[2]) >=4){
    printf("Mauvais format, vous devez executer le fichier comme: ./ReconstitueReseau <nomFichier.cha> <Numero>\n");
    printf("Le numero doit etre la methode utilisee:\n 1-Liste\n2-Table de Hachage\n3-Arbre\n");
    return 1;
  }
  FILE *fr = fopen(argv[1], "r");
  Chaines *cha = lectureChaines(fr);
  FILE *f = fopen("write.txt","w");
	ecrireChaines(cha, f);
  Reseau* R;
  int choix = atoi(argv[2]);
  printf("On retrouve les résultats dans les différents fichiers HTML: Instance 1, Instance 2 et Instance 3\n");
  switch (choix){
    case 1:
      printf("Utilisation des listes pour manipuler un reseau:\n");
      R = reconstitueReseauListe(cha);
      afficheReseauSVG(R, "Instance 2");
      break;
    case 2:
      printf("Utilisation de la table de hachage pour manipuler un reseau:\n");
      R = reconstitueReseauHachage(cha, N);
      afficheReseauSVG(R, "Instance 3");
      break;
    case 3:
      printf("Utilisation d'un arbre pour manipuler un reseau:\n");
      R = reconstitueReseauArbre(cha);
      afficheReseauSVG(R, "Instance 4");
      break;
    default:
      printf("Erreur\n");
      break;
  }
	FILE *fn = fopen("test_reseau_burma.txt", "w");
  ecrireReseau(R, fn);
  fclose(fr);
	fclose(f);
  fclose(fn);
  free_chaines(cha);
  liberer_reseau(R);
	//Q4.2
  printf("Test de la fonction clé:\n");
  for (int i = 0; i <= 10; i++){
    for (int j = 0; j <=10; j++){
      printf("i : %d j : %d clef = %d\n",i, j,fonction_cle(i, j));
    }
		printf("\n");
  }
  return 0;
}

void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}