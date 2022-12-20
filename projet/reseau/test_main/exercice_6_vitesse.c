//6.1
/*Permet de tester la vitesse des différents algorithmes*/
#include <time.h>
#include <stdio.h>
#include "../liste/Reseau.h"
#include "../hachage/Hachage.h"
#include "../arbre/ArbreQuat.h"
#include "../../chaine/Chaine.h"
#include "../../SVGwriter.h"

//Pour les tables de hachage, à faire varier
#define N 500
int main(){
  clock_t temps_initial;
  clock_t temps_final;
  double temps_cpu, temps_cpu1, temps_cpu2, temps_cpu3;
  Reseau *R,*Rt, *Ra;
  Chaines *nv_cha;
  FILE *fa = fopen("00014_burma.cha", "r");
  Chaines *cha = lectureChaines(fa);
  //Q6.3
  FILE *fichier_ecriture1 = fopen("ecriture_vitesse_gnuplot_liste.txt", "w");
  FILE *fichier_ecriture2 = fopen("ecriture_vitesse_gnuplot.txt","w");
  int nbPointsChaines = 10, xmax = 500, ymax = 500;
  for (int i = 1; i <= 1000; i +=2){
    printf("Generation aleatoire de chaines:\n");
    printf("i: %d",i);
    nv_cha = generationAleatoire(i, nbPointsChaines, xmax, ymax);

    printf("Fin de generation aleatoire de chaines:\n");
    //Reconstitution d'un réseau par liste
    temps_initial = clock () ;
    R = reconstitueReseauListe(nv_cha);
    temps_final = clock () ;
    temps_cpu1 = ((double)(temps_final - temps_initial)) /CLOCKS_PER_SEC;

    //Reconstitution d'un reseau par table de hachage
    temps_initial = clock () ;
    Rt = reconstitueReseauHachage(nv_cha, N);
    temps_final = clock () ;
    temps_cpu2 = ((double)(temps_final - temps_initial)) /CLOCKS_PER_SEC;

    //Reconstitution d'un reseau par arbre quaternaire
    temps_initial = clock();
    Ra = reconstitueReseauArbre(nv_cha);
    temps_final = clock();
    temps_cpu3 = ((double)(temps_final - temps_initial)) /CLOCKS_PER_SEC;
    //On écrit tout dans un fichier pour pouvoir tracer les courbes
    fprintf(fichier_ecriture1, "%d %lf\n",i, temps_cpu1);
    fprintf(fichier_ecriture2, "%d %lf %lf\n",i, temps_cpu2, temps_cpu3);
  }

  //Liberations 
  fclose(fa);
  fclose(fichier_ecriture1);
  fclose(fichier_ecriture2);
  liberer_reseau(R);
  liberer_reseau(Rt);
  liberer_reseau(Ra);
}
