#include "BmpLib.h"

#define XImage 3280 //largeur fixe de l'image prise par la caméra (a def)
#define ZImage 2464  //hauteur fixe de l'image prise par la caméra (a def)


void prendCouleurImage (char path[100], unsigned int **rouge, unsigned int **bleu, unsigned int **vert);
void cree3matrice(DonneesImageRGB *source, unsigned int **bleu, unsigned int **vert, unsigned int **rouge);
void NDG  (unsigned int ** tabGris, unsigned int ** tabRouge,  unsigned int ** tabVert, unsigned int ** tabBleu );
void conversionLBP (unsigned int ** tabGris, unsigned int ** tabRecupValeur);
unsigned int comparaison (unsigned int **tabLBPa , unsigned int **tabLBPb);
void GrisEnImage (unsigned int **tabGris, char path[100]);
unsigned int analyse(short int mode, char path1[100], char path2[100]);
void lisLBPsurImage (unsigned int **tabLBP, char path[100]);
