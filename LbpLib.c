#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "LbpLib.h"




//fonction de decoupage en trois tableau Rouge, vert et bleu d'une image se trouvant a l'adresse indiquee
void prendCouleurImage (char path[100], unsigned int **rouge, unsigned int **bleu, unsigned int **vert)
{
    DonneesImageRGB* image;
    image = lisBMPRGB(path);
    cree3matrice(image, bleu, vert, rouge);
}


void cree3matrice(DonneesImageRGB *source, unsigned int **bleu, unsigned int **vert, unsigned int **rouge)
{
    int i,j,k=0;
    for(j=0;j<ZImage;j++)
    {
        for(i=0;i<XImage;i++)//boucle de decoupage, partant du pixel 0 au dernier pixe
        {
            bleu[j][i] = source -> donneesRGB[k];//Bleu du pixel de position i
            vert[j][i] = source -> donneesRGB[k+1];//Rouge du pixel de position i
            rouge[j][i] = source -> donneesRGB[k+2];//vert du pixel de position i
            k=k+3;
        } 
    }
    
}

void NDG  (unsigned int ** tabGris, unsigned int ** tabRouge,  unsigned int ** tabVert, unsigned int ** tabBleu )// a completer
{
    // On devrait avoir un tableau en entré
    int i,j;
    // On change chaque couleur en une niveau de gris
    for(i=0; i<ZImage;i++)
    {
        for(j=0; j<=XImage; j++)
        {
            tabGris[i][j]= tabRouge[i][j]*0.2125 + tabVert[i][j]*0.7154 + tabBleu[i][j]*0.0721;
        }
    }
}

void conversionLBP (unsigned int ** tabGris, unsigned int ** tabRecupValeur) // type et parametre à completer
{
    // ----- Variables ----------// 
    int i,j,k,l;
    
    // ---------------------- //
    
     for(i=1; i<ZImage-2;i++)
    {
        for(j=1; j<=XImage-2; j++)
        {
          for(k = i-1; k<= i+1;k++)
            {
                for(l = j-1; l<= j+1;l++)
                {
                    if(k != i || j != l)
                    {
                        tabRecupValeur[i][j] = (tabRecupValeur[i][j] << 1);
                        if(tabGris[i][j]>=tabGris[k][l])
                        {
                            tabRecupValeur[i][j] = tabRecupValeur[i][j] +1;
                            
                        }
                        
                    }     
                }
            }
            if (i==1501 && j==1504) printf("lbp = %d\n",tabRecupValeur[i][j]);
        }
    }
}

unsigned int comparaison (unsigned int **tabLBPa , unsigned int **tabLBPb)
{
    unsigned int *tabCompA = calloc(256,sizeof(int)*256), *tabCompB = calloc(256,sizeof(unsigned int)*256), *tabResult = calloc(256,sizeof(unsigned int)*256);
    unsigned int var = 0;
    int i,j,k,cpt1=0,cpt2=0,zmin=1000,zmax=1800,xmin=1250,xmax=2250;
    for(k=0;k<256;k++)
    {
        for(i=zmin; i<zmax ; i++)
        {
            for(j=xmin ; j<xmax ; j++)
            {
                if(tabLBPa[i][j] == k)
                {
                    tabCompA[k] = tabCompA[k] + 1;
                    if(k==56)
                    {
                        cpt1 = cpt1 + 1;
                    }
                }
                if(tabLBPb[i][j] == k)
                {
                    tabCompB[k] = tabCompB[k] + 1;
                    if(k==56)
                    {
                        cpt2 = cpt2 + 1;
                    }
                }

            }
        }
        
    }
    for(i=0 ; i<256 ; i++)
    {
        if(tabCompA[i]<tabCompB[i])
        {
            tabResult[i] = tabCompB[i] - tabCompA[i];
        }
        else
        {
            tabResult[i] = tabCompA[i] - tabCompB[i];
        }
    }
    for(i=0;i<256;i++)
    {
        var = var + tabResult[i];
    }
    printf("\n");
    var = var/(256);
    free(tabCompA);
    free(tabCompB);
    free(tabResult);
    return var;
}

void GrisEnImage (unsigned int **tabGris, char path[100])
{
    DonneesImageRGB* saveGris = malloc(sizeof(DonneesImageRGB));
    saveGris -> donneesRGB = malloc(sizeof(unsigned int)*ZImage*sizeof(unsigned int)*XImage*3);
    int i,j,k=0;
    bool b;
    for(j=0;j<ZImage;j++)
    {
        for(i=0;i<XImage;i++)
        {
            saveGris ->donneesRGB[k] = tabGris[j][i];
            saveGris -> donneesRGB[k+1] = tabGris[j][i];
            saveGris -> donneesRGB[k+2] = tabGris[j][i];
            k +=3;
        } 
    }
    printf("%d \n",saveGris->donneesRGB[67000]);
    saveGris -> largeurImage = XImage;
    saveGris -> hauteurImage = ZImage;
    b = ecrisBMPRGB_Dans(saveGris , path);
    if(b == false)
    {
        printf("Erreur de la sauvegarde\n");
    }
    free(saveGris -> donneesRGB);
    free(saveGris);
}

void lisLBPsurImage (unsigned int **tabLBP, char path[100])
{
    DonneesImageRGB* image;
    image = lisBMPRGB(path);
    int i,j,k=0;
    for(j=0;j<ZImage;j++)
    {
        for(i=0;i<XImage;i++)
        {
            tabLBP[j][i] = image -> donneesRGB[k];
            k += 3;
        } 
    }
}
    
/*int main (void)//main de test, ignorer
{
    int i;
    int resultat;
    unsigned int **bleu = malloc(sizeof(unsigned int *)*ZImage), **vert =malloc(sizeof(unsigned int *)*ZImage), **rouge = malloc(sizeof(unsigned int *)*ZImage);
    unsigned int **tabNDG = malloc(sizeof(unsigned int *)*ZImage), **tabLBPBinaireA = calloc(ZImage,sizeof(unsigned int *)*ZImage), **tabLBPBinaireB = calloc(ZImage, sizeof(unsigned int *)*ZImage);
    for(i=0; i<ZImage ; i++)
    {
        bleu[i] = malloc(sizeof(unsigned int)*XImage);
        rouge[i] = malloc(sizeof(unsigned int)*XImage);
        vert[i] = malloc(sizeof(unsigned int)*XImage);
        tabNDG[i] = malloc(sizeof(unsigned int)*XImage);
        tabLBPBinaireA[i] = calloc(XImage,sizeof(unsigned int *)*XImage);
        tabLBPBinaireB[i] = calloc(XImage,sizeof(unsigned int*)*XImage);
    }
    prendCouleurImage("testju2.bmp", bleu, rouge, vert );
    NDG(tabNDG, rouge, vert , bleu);
    conversionLBP(tabNDG,tabLBPBinaireA);
    prendCouleurImage("testju3.bmp", bleu, rouge, vert);
    NDG(tabNDG, rouge, vert, bleu);
    conversionLBP(tabNDG,tabLBPBinaireB );
    GrisEnImage(tabLBPBinaireA,"testimage1.bmp");
    GrisEnImage(tabLBPBinaireB,"testimage2.bmp");
    resultat = analyse(2,"testimage1.bmp","testimage2.bmp");
    printf("Comparaison1: %d \n",resultat);
    prendCouleurImage("aurelien2.bmp", bleu, rouge, vert);
    NDG(tabNDG, rouge, vert, bleu);
    conversionLBP(tabNDG,tabLBPBinaireB );
    GrisEnImage(tabLBPBinaireB,"testimage3.bmp");
    resultat = analyse(2,"testimage1.bmp","testimage3.bmp");
    printf("Comparaison2: %d \n",resultat);
    for(i=0 ; i<ZImage ; i++)
    {
        free(rouge[i]);
        free(vert[i]);
        free(bleu[i]);
        free(tabNDG[i]);
        free(tabLBPBinaireA[i]);
        free(tabLBPBinaireB[i]);
    }
    free(rouge);
    free(vert);
    free(bleu);
    free(tabNDG);
    free(tabLBPBinaireA);
    free(tabLBPBinaireB);
    return 0;   
}*/

unsigned int analyse(short int mode, char path1[100], char path2[100])
{
    int i;
    unsigned int **bleu = malloc(sizeof(unsigned int *)*ZImage), **vert =malloc(sizeof(unsigned int *)*ZImage), **rouge = malloc(sizeof(unsigned int *)*ZImage);
    unsigned int **tabNDG = malloc(sizeof(unsigned int *)*ZImage), **tabLBPBinaireA = calloc(ZImage,sizeof(unsigned int *)*ZImage);
    unsigned int **tabLBPBinaireB = calloc(ZImage, sizeof(unsigned int *)*ZImage), resultat = 1000;

    switch(mode)
    {
        case 1://extraction d'une photo et calcul de toute ses composantes et la sauvegarde sosu la forme d'une image de LBP
        for(i=0; i<ZImage ; i++)
        {
            bleu[i] = malloc(sizeof(unsigned int)*XImage);
            rouge[i] = malloc(sizeof(unsigned int)*XImage);
            vert[i] = malloc(sizeof(unsigned int)*XImage);
            tabNDG[i] = malloc(sizeof(unsigned int)*XImage);
            tabLBPBinaireA[i] = calloc(XImage,sizeof(unsigned int *)*XImage);
        }
        
        prendCouleurImage(path1, bleu, rouge, vert );
        NDG(tabNDG, rouge, vert , bleu);
        conversionLBP(tabNDG,tabLBPBinaireA);
        GrisEnImage(tabLBPBinaireA,path2);
        for(i=0 ; i<ZImage ; i++)
        {
            free(rouge[i]);
            free(vert[i]);
            free(bleu[i]);
            free(tabNDG[i]);
            free(tabLBPBinaireA[i]);
        }
        free(rouge);
        free(vert);
        free(bleu);
        free(tabNDG);
        free(tabLBPBinaireA);
        break;

        case 2: //cas d'une comparaison sur deux images il faut qu'elle soient en stock avec le mode 1
        for(i=0;i<ZImage;i++)
        {
            tabLBPBinaireA[i] = calloc(XImage,sizeof(unsigned int *)*XImage);
            tabLBPBinaireB[i] = calloc(XImage,sizeof(unsigned int*)*XImage);
        }

        lisLBPsurImage(tabLBPBinaireA,path1);
        lisLBPsurImage(tabLBPBinaireB,path2);
        resultat = comparaison(tabLBPBinaireA,tabLBPBinaireB);
        for(i=0;i<ZImage;i++)
        {
            free(tabLBPBinaireA[i]);
            free(tabLBPBinaireB[i]);
        }
        free(tabLBPBinaireA);
        free(tabLBPBinaireB);       
        break;
        
    }
    return resultat;
}
