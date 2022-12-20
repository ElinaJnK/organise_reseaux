#include "Chaine.h"
#define  N 100
//#define LENBUF 100
int main(int ac, char **av){
	if (ac != 3){
    printf("Mauvais format, vous devez executer le fichier comme: ./ChaineMain <nomFichierSource.txt> <nomFichierDest.txt>\n");
		return 1;
	}

  FILE *fr = fopen(av[1], "r");
  Chaines *cha = lectureChaines(fr);
  FILE *fw = fopen(av[2], "w");
  ecrireChaines(cha, fw);
  //Q1.3
  afficheChainesSVG(cha, "Instance 1");
	free_chaines(cha);
	fclose(fr);
  fclose(fw);
	return 0;
}
