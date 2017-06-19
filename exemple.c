#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()
#include "projet.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

// Fonction de trace de cercle
void cercle(float centreX, float centreY, float rayon);
/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);



int main(int argc, char **argv)
{
    initialiseGfx(argc, argv);
    
    prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);
    
    /* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
        qui elle-meme utilise fonctionAffichage ci-dessous */
    lanceBoucleEvenements();
    
    return 0;
}



/* Fonction de trace de cercle */
void cercle(float centreX, float centreY, float rayon)
{
    const int Pas = 20; // Nombre de secteurs pour tracer le cercle
    const double PasAngulaire = 2.*M_PI/Pas;
    int index;
    
    for (index = 0; index < Pas; ++index) // Pour chaque secteur
    {
        const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
        triangle(centreX, centreY,
                 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
                 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
            // On trace le secteur a l'aide d'un triangle => approximation d'un cercle
    }
    
}


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
    static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
    static DonneesImageRGB *image = NULL; // L'image a afficher au centre de l'ecran
    //static DonneesImageRGB *image1 = NULL;
    static int mode = 0; 
    static char afficheTimer [50];
    static int timer = 0;
    static int comparaison = 0;
    static char txt[50];
    static unsigned int resultat,resultat2;
    switch (evenement)
    {
        case Initialisation:
            /* Le message "Initialisation" est envoye une seule fois, au debut du
            programme : il permet de fixer "image" a la valeur qu'il devra conserver
            jusqu'a la fin du programme : soit "image" reste a NULL si l'image n'a
            pas pu etre lue, soit "image" pointera sur une structure contenant
            les caracteristiques de l'image "imageNB.bmp" */
            // 0 menu d'acceuil // 1 menu de selection 
            // Configure le systeme pour generer un message Temporisation
            // toutes les 20 millisecondes
            image = lisBMPRGB("juliencouleur1.bmp");
            demandeTemporisation(20);
            break;
        
        case Temporisation:
            
            if(timer>0)
            {
                timer --;
                sprintf(afficheTimer,"%d",timer);
                printf("%s\n", afficheTimer );
               if (timer==0)
               {
                    if(comparaison == 1 )
                {
                    mode = 61;
                    //unsigned int analyse(short int mode, char path1[100], char path2[100])
                    printf("passe comparaison fonction");
                    
                    printf("resultat = %d\n",resultat);
                }
                
                else 
                {
                    mode = 1;
                }

               }
            }
            
            
            rafraichisFenetre();
            break;
            
        case Affichage:
            
            // On part d'un fond d'ecran blanc
            effaceFenetre (0, 100, 150);
            
            if (mode==0)
            {
                 couleurCourante(150,150,150);

                rectangle(4.5*largeurFenetre()/20, 8.5*hauteurFenetre()/20 ,14.5*largeurFenetre()/20,11*hauteurFenetre()/20);
                rectangle(4.5*largeurFenetre()/20, 3.5*hauteurFenetre()/20 ,14.5*largeurFenetre()/20,6*hauteurFenetre()/20);
                
                couleurCourante(0,0,0);
                
                rectangle(4*largeurFenetre()/20, 9*hauteurFenetre()/20 ,14*largeurFenetre()/20,11*hauteurFenetre()/20);
                rectangle(4*largeurFenetre()/20, 4*hauteurFenetre()/20 ,14*largeurFenetre()/20,6*hauteurFenetre()/20);

                
                couleurCourante(255,255,255);
                
                afficheChaine("Launch the software ",30,5*largeurFenetre()/20,10*hauteurFenetre()/20);
                afficheChaine("Leave the software ",30,5* largeurFenetre()/20,5*hauteurFenetre()/20);
            }
            if (mode==1)
            {   
                couleurCourante(175,175,175);

                rectangle(4.5*largeurFenetre()/40, 38.5*hauteurFenetre()/50 ,28.5*largeurFenetre()/40,43*hauteurFenetre()/50);
                rectangle(4.5*largeurFenetre()/40, 28.5*hauteurFenetre()/50 ,31.5*largeurFenetre()/40,33*hauteurFenetre()/50);
                rectangle(4.5*largeurFenetre()/40, 18.5*hauteurFenetre()/50 ,28.5*largeurFenetre()/40,23*hauteurFenetre()/50);
                rectangle(4.5*largeurFenetre()/40, 8.5*hauteurFenetre()/50 ,28.5*largeurFenetre()/40,13*hauteurFenetre()/50);

                couleurCourante(0,0,0);

                rectangle(4*largeurFenetre()/40, 39*hauteurFenetre()/50 ,28*largeurFenetre()/40,43*hauteurFenetre()/50);
                rectangle(4*largeurFenetre()/40, 29*hauteurFenetre()/50 ,31*largeurFenetre()/40,33*hauteurFenetre()/50);
                rectangle(4*largeurFenetre()/40, 19*hauteurFenetre()/50 ,28*largeurFenetre()/40,23*hauteurFenetre()/50);
                rectangle(4*largeurFenetre()/40, 9*hauteurFenetre()/50 ,28*largeurFenetre()/40,13*hauteurFenetre()/50);

                couleurCourante(255,255,255); 

                afficheChaine("Take a photo (WIP)",30, 5* largeurFenetre()/40,40*hauteurFenetre()/50); // démarage au mode 50
                afficheChaine("Launch a comparison(demo)",30,5* largeurFenetre()/40,30*hauteurFenetre()/50); // démarage au mode 60
                afficheChaine("Add a user (WIP)",30,5* largeurFenetre()/40,20*hauteurFenetre()/50);
                afficheChaine("Leave the software ",30,5* largeurFenetre()/40,10*hauteurFenetre()/50);
                
            }
            
            if(mode == 2 ) // mode d'affichage des résultats
            {
                
            }
            
            if(mode == 50)
            {
                couleurCourante(0,0,0);
                afficheChaine("press to start countdown",20,hauteurFenetre()/2,largeurFenetre()/2);
            }
            if (mode == 51)
            {
                if (image != NULL) // Si l'image a pu etre lue
            {
                couleurCourante(0,0,0);
                afficheChaine(afficheTimer,30,largeurFenetre()/2,hauteurFenetre()/2);
                // Commande pour prendre l'image sans besoin de la montrer
                //      raspistill -o image.bmp -t 5000
                // On affiche l'image
                // si le timer est fini alors : on affiche l'image
                
            }
            
            }
            
            if(mode == 60)
            {
                // on prend la photo puis on recupère le nom de la personne / de la photo à recupéré
                
            }
            
            if(mode == 61)
            {
                
                // idéalement on récupere le nom de la photo à comparais. 
                //ecrisImage(0,0, image->largeurImage, image->hauteurImage, image->donneesRGB);  
                //printf("%lf %lf\n",(image->largeurImage)/2.,(image->hauteurImage)/2.);
                couleurCourante(175,175,175);
                rectangle(4.5*largeurFenetre()/40, 38.5*hauteurFenetre()/50 ,29.5*largeurFenetre()/40,43*hauteurFenetre()/50);
                couleurCourante(0,0,0); 
                rectangle(4*largeurFenetre()/40, 39*hauteurFenetre()/50 ,29*largeurFenetre()/40,43*hauteurFenetre()/50);
                couleurCourante(175,175,175);
                afficheChaine("successfully saved",30, 5* largeurFenetre()/40,40*hauteurFenetre()/50);

                couleurCourante(175,175,175);
                rectangle(4.5*largeurFenetre()/40, 18.5*hauteurFenetre()/50 ,29.5*largeurFenetre()/40,22.5*hauteurFenetre()/50);
                couleurCourante(0,0,0); 
                rectangle(4*largeurFenetre()/40, 19*hauteurFenetre()/50 ,29*largeurFenetre()/40,22.5*hauteurFenetre()/50);
                couleurCourante(175,175,175);
                afficheChaine("next step?",30, 5* largeurFenetre()/40,20*hauteurFenetre()/50);
                
            }
            if (mode == 62)
            {
                couleurCourante(175,175,175);
                rectangle(4.5*largeurFenetre()/40, 38.5*hauteurFenetre()/50 ,29.5*largeurFenetre()/40,43*hauteurFenetre()/50);
                couleurCourante(0,0,0); 
                rectangle(4*largeurFenetre()/40, 39*hauteurFenetre()/50 ,29*largeurFenetre()/40,43*hauteurFenetre()/50);
                couleurCourante(175,175,175);
                afficheChaine("analysis successful!",30, 5* largeurFenetre()/40,40*hauteurFenetre()/50);

                couleurCourante(175,175,175);
                rectangle(4.5*largeurFenetre()/40, 18.5*hauteurFenetre()/50 ,29.5*largeurFenetre()/40,23*hauteurFenetre()/50);
                couleurCourante(0,0,0); 
                rectangle(4*largeurFenetre()/40, 19*hauteurFenetre()/50 ,29*largeurFenetre()/40,23*hauteurFenetre()/50);
                couleurCourante(175,175,175);
                afficheChaine("analysis 1:",30, 5* largeurFenetre()/40,20*hauteurFenetre()/50);
                sprintf(txt,"%d",resultat);
                afficheChaine(txt,30,20*largeurFenetre()/40,20*hauteurFenetre()/50);

                couleurCourante(175,175,175);
                rectangle(4.5*largeurFenetre()/40, 8.5*hauteurFenetre()/50 ,29.5*largeurFenetre()/40,13*hauteurFenetre()/50);
                couleurCourante(0,0,0); 
                rectangle(4*largeurFenetre()/40, 9*hauteurFenetre()/50 ,29*largeurFenetre()/40,13*hauteurFenetre()/50);
                couleurCourante(175,175,175);
                afficheChaine("analysis 2:",30, 5* largeurFenetre()/40,10*hauteurFenetre()/50);
                sprintf(txt,"%d",resultat2);
                afficheChaine(txt,30,20*largeurFenetre()/40,10*hauteurFenetre()/50);
            }
            break;
            
        case Clavier:
            printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

            switch (caractereClavier())
            {
                case 'Q': /* Pour sortir quelque peu proprement du programme */
                case 'q':
                    libereDonneesImageRGB(&image); /* On libere la structure image,
                    c'est plus propre, meme si on va sortir du programme juste apres */
                    termineBoucleEvenements();
                    break;

                case 'F':
                case 'f':
                    pleinEcran = !pleinEcran; // Changement de mode plein ecran
                    if (pleinEcran)
                        modePleinEcran();
                    else
                        redimensionneFenetre(LargeurFenetre, HauteurFenetre);
                    break;

                case 'R':
                case 'r':
                    // Configure le systeme pour generer un message Temporisation
                    // toutes les 20 millisecondes (rapide)
                    demandeTemporisation(20);
                    break;

                case 'L':
                case 'l':
                    // Configure le systeme pour generer un message Temporisation
                    // toutes les 100 millisecondes (lent)
                    demandeTemporisation(100);
                    break;

                case 'S':
                case 's':
                    // Configure le systeme pour ne plus generer de message Temporisation
                    demandeTemporisation(-1);
                    break;
            }
            break;
            
        case ClavierSpecial:
            printf("ASCII %d\n", toucheClavier());
            break;

        case BoutonSouris:
            if (etatBoutonSouris() == GaucheAppuye)
            {
                
            }
            else if (etatBoutonSouris() == GaucheRelache)
            {
                if(mode==0)
                {
                    // Lancement du programme
                    if(abscisseSouris()>=4*largeurFenetre()/20 && abscisseSouris()<=14*largeurFenetre()/20)
                    {
                        if (ordonneeSouris()>=9*hauteurFenetre()/20 && ordonneeSouris() <=11*hauteurFenetre()/20)
                        {   
                            mode=1;
                        }                   
                    }
                // Quitté le programme
                if(abscisseSouris()>=4*largeurFenetre()/20 && abscisseSouris()<=14*largeurFenetre()/20)
                {
                    if (ordonneeSouris()>=4*hauteurFenetre()/20 && ordonneeSouris() <= 5*hauteurFenetre()/20)
                    {
                            libereDonneesImageRGB(&image); /* On libere la structure image,
                    c'est plus propre, meme si on va sortir du programme juste apres */     
                    termineBoucleEvenements();
                    }
                }
                }
                if(mode == 1)
                {
                    // si on veut prendre une photo
                    if(abscisseSouris()>=2*largeurFenetre()/20 && abscisseSouris()<=14*largeurFenetre()/20)
                    {
                        if (ordonneeSouris()>=39*hauteurFenetre()/50 && ordonneeSouris() <=41*hauteurFenetre()/50)
                        {   
                            mode=50;
                             printf("On appuie sur photo \n");
                        }                   
                    }
                    // si on veut faire une comparaison
                    if(abscisseSouris()>=2*largeurFenetre()/20 && abscisseSouris()<=14*largeurFenetre()/20)
                    {
                        if (ordonneeSouris()>=29*hauteurFenetre()/50 && ordonneeSouris() <=31*hauteurFenetre()/50)
                        {   
                            mode=50;
                            comparaison = 1;
                            resultat = analyse (1, "juliencouleur1.bmp","julienpascouleur.bmp");
                            resultat = analyse (1, "juliencouleur2.bmp","julienpascouleur2.bmp");
                            resultat = analyse (1, "aureliencouleur1.bmp","aurelienpascouleur.bmp");
                        }                   
                    }



                    // si on ajoute une personne
                    if(abscisseSouris()>=2*largeurFenetre()/20 && abscisseSouris()<=14*largeurFenetre()/20)
                    {
                        if (ordonneeSouris()>=19*hauteurFenetre()/50 && ordonneeSouris() <=21*hauteurFenetre()/50)
                        {   
                            // On enregiste le nom, prénom puis on prends un photo et on enregiste le tout

                        }                   
                    }


                    // si on quitte
                    if(abscisseSouris()>=2*largeurFenetre()/20 && abscisseSouris()<=14*largeurFenetre()/20)
                    {
                        if (ordonneeSouris()>=9*hauteurFenetre()/50 && ordonneeSouris() <=11*hauteurFenetre()/50)
                        {   
                            libereDonneesImageRGB(&image); /* On libere la structure image,
                            c'est plus propre, meme si on va sortir du programme juste apres */     
                            termineBoucleEvenements();
                        }                   
                    }
                }
            
                if (mode == 50)
                {
                    if(abscisseSouris()>=0*hauteurFenetre()/3 && abscisseSouris()<=3*largeurFenetre()/3)
                    {
                        if (ordonneeSouris()>= 0*hauteurFenetre()/3 && ordonneeSouris() <=3*hauteurFenetre()/3)
                        {   
                            mode=51;
                            timer = 5; // temps a regler
                            printf("On valide la photo\n");
                        }                   
                    }
                }
                if (mode == 61)
                {
                    if((abscisseSouris()>=4.5*largeurFenetre()/40) && (ordonneeSouris()>=18.5*hauteurFenetre()/50) && (abscisseSouris()<= 29.5*largeurFenetre()/40) && (ordonneeSouris()<=23*hauteurFenetre()/50))
                    {
                        mode = 62;
                        resultat = analyse(2,"julienpascouleur.bmp","julienpascouleur2.bmp");
                        printf("res 1 : %d\n",resultat);
                        resultat2 = analyse(2,"julienpascouleur.bmp","aurelienpascouleur.bmp");
                        printf("res 2 : %d\n",resultat2);
                    }
                }
                
            }
            break;
        
        case Souris: // Si la souris est deplacee
            break;
        
        case Inactivite: // Quand aucun message n'est disponible
            break;
        
        case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
            break;
    }
}
