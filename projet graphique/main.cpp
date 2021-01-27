#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h> /* Inclusion du header de SDL_image (adapter le dossier au besoin)*/
#include <string.h>
#include <SDL/SDL_mixer.h>
#include <windows.h>


typedef struct
{
    int b_n;
    int moulin;
} pion;
pion Grid[3][8]; // la matrice principale qui represente la table de jeu
int poser=18; // nombre de pions initial cas juoeur vs joueur noir et blanc
int Rnoir=0,Rblanc=0; // le nombre de pions recupéré pour chaque joueur
int i_c,j_c; // les coordonnees courant utilisé dans le choix
int i_m,j_m; // les coordonnees de la pions de l'advérsaire à reccuperé
int i_d,j_d; // les coordonnees de la pion pour le deplacement (choisi par le joueur)
int i_c_m,j_c_m;
int i_d_m,j_d_m;
int p; // variable qui va eviter des problèmes dans la determination des moulins
int color=1; // nombre qui va representé soit noir ou blanc
int R1; //pour le joueur max
int R2; //pour la machine min

// pour la SDL
SDL_Event event;
SDL_Surface *ecran = NULL,*imageDeFond = NULL;
SDL_Rect positionSapin, positionBall,positionFond,positionOk,positionQ;
SDL_Surface *noir = IMG_Load("images/noir.png");
SDL_Surface *blanc = IMG_Load("images/blanc.png");
SDL_Surface *ok = IMG_Load("images/ok.png");
SDL_Surface *ball,*gagnant;

int choix(SDL_Event event) // fonction de choix de la position
{
    if(315<event.button.x&&event.button.x<345&&64<event.button.y&&event.button.y<90)
    {
        if(Grid[0][0].b_n == 0)
        {
            Grid[0][0].b_n = color;
            i_c=0;
            j_c=0;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&64<event.button.y&&event.button.y<90)
    {
        if(Grid[0][1].b_n == 0)
        {
            Grid[0][1].b_n=color;
            i_c=0;
            j_c=1;
            return 0;
        }
    }
    if(875<event.button.x&&event.button.x<905&&64<event.button.y&&event.button.y<90)
    {

        if(Grid[0][2].b_n == 0)
        {
            Grid[0][2].b_n=color;
            i_c=0;
            j_c=2;
            return 0;
        }
    }

    if(408<event.button.x&&event.button.x<438&&150<event.button.y&&event.button.y<180)
    {

        if(Grid[1][0].b_n == 0)
        {
            Grid[1][0].b_n=color;
            i_c=1;
            j_c=0;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&150<event.button.y&&event.button.y<180)
    {

        if(Grid[1][1].b_n == 0)
        {
            Grid[1][1].b_n=color;
            i_c=1;
            j_c=1;
            return 0;
        }
    }
    if(780<event.button.x&&event.button.x<810&&150<event.button.y&&event.button.y<180)
    {
        if(Grid[1][2].b_n == 0)
        {
            Grid[1][2].b_n=color;
            i_c=1;
            j_c=2;
            return 0;
        }
    }

    if(500<event.button.x&&event.button.x<530&&240<event.button.y&&event.button.y<270)
    {

        if(Grid[2][0].b_n == 0)
        {
            Grid[2][0].b_n=color;
            i_c=2;
            j_c=0;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&240<event.button.y&&event.button.y<270)
    {

        if(Grid[2][1].b_n == 0)
        {
            Grid[2][1].b_n=color;
            i_c=2;
            j_c=1;
            return 0;
        }
    }
    if(690<event.button.x&&event.button.x<720&&240<event.button.y&&event.button.y<270)
    {

        if(Grid[2][2].b_n == 0)
        {
            Grid[2][2].b_n=color;
            i_c=2;
            j_c=2;
            return 0;
        }
    }

    if(315<event.button.x&&event.button.x<345&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[0][7].b_n == 0)
        {
            Grid[0][7].b_n=color;
            i_c=0;
            j_c=7;
            return 0;
        }
    }
    if(405<event.button.x&&event.button.x<435&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[1][7].b_n == 0)
        {
            Grid[1][7].b_n=color;
            i_c=1;
            j_c=7;
            return 0;
        }
    }
    if(495<event.button.x&&event.button.x<525&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[2][7].b_n == 0)
        {
            Grid[2][7].b_n=color;
            i_c=2;
            j_c=7;
            return 0;
        }
    }
    if(685<event.button.x&&event.button.x<715&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[2][3].b_n == 0)
        {
            Grid[2][3].b_n=color;
            i_c=2;
            j_c=3;
            return 0;
        }
    }
    if(775<event.button.x&&event.button.x<805&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[1][3].b_n == 0)
        {
            Grid[1][3].b_n=color;
            i_c=1;
            j_c=3;
            return 0;
        }
    }
    if(865<event.button.x&&event.button.x<895&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[0][3].b_n == 0)
        {
            Grid[0][3].b_n=color;
            i_c=0;
            j_c=3;
            return 0;
        }
    }

    if(500<event.button.x&&event.button.x<530&&415<event.button.y&&event.button.y<445)
    {

        if(Grid[2][6].b_n == 0)
        {
            Grid[2][6].b_n=color;
            i_c=2;
            j_c=6;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&415<event.button.y&&event.button.y<445)
    {

        if(Grid[2][5].b_n == 0)
        {
            Grid[2][5].b_n=color;
            i_c=2;
            j_c=5;
            return 0;
        }
    }
    if(690<event.button.x&&event.button.x<720&&415<event.button.y&&event.button.y<445)
    {

        if(Grid[2][4].b_n == 0)
        {
            Grid[2][4].b_n=color;
            i_c=2;
            j_c=4;
            return 0;
        }
    }

    if(408<event.button.x&&event.button.x<438&&505<event.button.y&&event.button.y<535)
    {

        if(Grid[1][6].b_n == 0)
        {
            Grid[1][6].b_n=color;
            i_c=1;
            j_c=6;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&505<event.button.y&&event.button.y<535)
    {

        if(Grid[1][5].b_n == 0)
        {
            Grid[1][5].b_n=color;
            i_c=1;
            j_c=5;
            return 0;
        }
    }
    if(780<event.button.x&&event.button.x<810&&505<event.button.y&&event.button.y<535)
    {

        if(Grid[1][4].b_n == 0)
        {
            Grid[1][4].b_n=color;
            i_c=1;
            j_c=4;
            return 0;
        }
    }

    if(315<event.button.x&&event.button.x<345&&590<event.button.y&&event.button.y<620)
    {

        if(Grid[0][6].b_n == 0)
        {
            Grid[0][6].b_n=color;
            i_c=0;
            j_c=6;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&590<event.button.y&&event.button.y<620)
    {

        if(Grid[0][5].b_n == 0)
        {
            Grid[0][5].b_n=color;
            i_c=0;
            j_c=5;
            return 0;
        }
    }
    if(875<event.button.x&&event.button.x<905&&590<event.button.y&&event.button.y<620)
    {

        if(Grid[0][4].b_n == 0)
        {
            Grid[0][4].b_n=color;
            i_c=0;
            j_c=4;
            return 0;
        }
    }
    return 1;


}
int choix1(SDL_Event event) // fonction pour choisir le pion a reccupéré
{
    if(315<event.button.x&&event.button.x<345&&64<event.button.y&&event.button.y<90)
    {
        if(Grid[0][0].b_n == -1 * Grid[i_c][j_c].b_n )
        {
            i_m=0;
            j_m=0;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&64<event.button.y&&event.button.y<90)
    {
        if(Grid[0][1].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=0;
            j_m=1;
            return 0;
        }
    }
    if(875<event.button.x&&event.button.x<905&&64<event.button.y&&event.button.y<90)
    {

        if(Grid[0][2].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=0;
            j_m=2;
            return 0;
        }
    }

    if(408<event.button.x&&event.button.x<438&&150<event.button.y&&event.button.y<180)
    {

        if(Grid[1][0].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=1;
            j_m=0;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&150<event.button.y&&event.button.y<180)
    {

        if(Grid[1][1].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=1;
            j_m=1;
            return 0;
        }
    }
    if(780<event.button.x&&event.button.x<810&&150<event.button.y&&event.button.y<180)
    {
        if(Grid[1][2].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=1;
            j_m=2;
            return 0;
        }
    }

    if(500<event.button.x&&event.button.x<530&&240<event.button.y&&event.button.y<270)
    {

        if(Grid[2][0].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=2;
            j_m=0;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&240<event.button.y&&event.button.y<270)
    {

        if(Grid[2][1].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=2;
            j_m=1;
            return 0;
        }
    }
    if(690<event.button.x&&event.button.x<720&&240<event.button.y&&event.button.y<270)
    {

        if(Grid[2][2].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=2;
            j_m=2;
            return 0;
        }
    }

    if(315<event.button.x&&event.button.x<345&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[0][7].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=0;
            j_m=7;
            return 0;
        }
    }
    if(405<event.button.x&&event.button.x<435&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[1][7].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=1;
            j_m=7;
            return 0;
        }
    }
    if(495<event.button.x&&event.button.x<525&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[2][7].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=2;
            j_m=7;
            return 0;
        }
    }
    if(685<event.button.x&&event.button.x<715&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[2][3].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=2;
            j_m=3;
            return 0;
        }
    }
    if(775<event.button.x&&event.button.x<805&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[1][3].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=1;
            j_m=3;
            return 0;
        }
    }
    if(865<event.button.x&&event.button.x<895&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[0][3].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=0;
            j_m=3;
            return 0;
        }
    }

    if(500<event.button.x&&event.button.x<530&&415<event.button.y&&event.button.y<445)
    {

        if(Grid[2][6].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=2;
            j_m=6;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&415<event.button.y&&event.button.y<445)
    {

        if(Grid[2][5].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=2;
            j_m=5;
            return 0;
        }
    }
    if(690<event.button.x&&event.button.x<720&&415<event.button.y&&event.button.y<445)
    {

        if(Grid[2][4].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=2;
            j_m=4;
            return 0;
        }
    }

    if(408<event.button.x&&event.button.x<438&&505<event.button.y&&event.button.y<535)
    {

        if(Grid[1][6].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=1;
            j_m=6;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&505<event.button.y&&event.button.y<535)
    {

        if(Grid[1][5].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=1;
            j_m=5;
            return 0;
        }
    }
    if(780<event.button.x&&event.button.x<810&&505<event.button.y&&event.button.y<535)
    {

        if(Grid[1][4].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=1;
            j_m=4;
            return 0;
        }
    }

    if(315<event.button.x&&event.button.x<345&&590<event.button.y&&event.button.y<620)
    {

        if(Grid[0][6].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=0;
            j_m=6;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&590<event.button.y&&event.button.y<620)
    {

        if(Grid[0][5].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=0;
            j_m=5;
            return 0;
        }
    }
    if(875<event.button.x&&event.button.x<905&&590<event.button.y&&event.button.y<620)
    {

        if(Grid[0][4].b_n == -1 * Grid[i_c][j_c].b_n)
        {
            i_m=0;
            j_m=4;
            return 0;
        }
    }
    return 1;


}
int choix2(SDL_Event event) // fonction pour choisir la destination d'un pion
{
    if(315<event.button.x&&event.button.x<345&&64<event.button.y&&event.button.y<90)
    {
        if(Grid[0][0].b_n == color )
        {
            i_d=0;
            j_d=0;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&64<event.button.y&&event.button.y<90)
    {
        if(Grid[0][1].b_n == color)
        {
            i_d=0;
            j_d=1;
            return 0;
        }
    }
    if(875<event.button.x&&event.button.x<905&&64<event.button.y&&event.button.y<90)
    {

        if(Grid[0][2].b_n == color)
        {
            i_d=0;
            j_d=2;
            return 0;
        }
    }

    if(408<event.button.x&&event.button.x<438&&150<event.button.y&&event.button.y<180)
    {

        if(Grid[1][0].b_n == color)
        {
            i_d=1;
            j_d=0;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&150<event.button.y&&event.button.y<180)
    {

        if(Grid[1][1].b_n == color)
        {
            i_d=1;
            j_d=1;
            return 0;
        }
    }
    if(780<event.button.x&&event.button.x<810&&150<event.button.y&&event.button.y<180)
    {
        if(Grid[1][2].b_n == color)
        {
            i_d=1;
            j_d=2;
            return 0;
        }
    }

    if(500<event.button.x&&event.button.x<530&&240<event.button.y&&event.button.y<270)
    {

        if(Grid[2][0].b_n == color)
        {
            i_d=2;
            j_d=0;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&240<event.button.y&&event.button.y<270)
    {

        if(Grid[2][1].b_n == color)
        {
            i_d=2;
            j_d=1;
            return 0;
        }
    }
    if(690<event.button.x&&event.button.x<720&&240<event.button.y&&event.button.y<270)
    {

        if(Grid[2][2].b_n == color)
        {
            i_d=2;
            j_d=2;
            return 0;
        }
    }

    if(315<event.button.x&&event.button.x<345&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[0][7].b_n == color)
        {
            i_d=0;
            j_d=7;
            return 0;
        }
    }
    if(405<event.button.x&&event.button.x<435&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[1][7].b_n == color)
        {
            i_d=1;
            j_d=7;
            return 0;
        }
    }
    if(495<event.button.x&&event.button.x<525&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[2][7].b_n == color)
        {
            i_d=2;
            j_d=7;
            return 0;
        }
    }
    if(685<event.button.x&&event.button.x<715&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[2][3].b_n == color)
        {
            i_d=2;
            j_d=3;
            return 0;
        }
    }
    if(775<event.button.x&&event.button.x<805&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[1][3].b_n == color)
        {
            i_d=1;
            j_d=3;
            return 0;
        }
    }
    if(865<event.button.x&&event.button.x<895&&330<event.button.y&&event.button.y<360)
    {

        if(Grid[0][3].b_n == color)
        {
            i_d=0;
            j_d=3;
            return 0;
        }
    }

    if(500<event.button.x&&event.button.x<530&&415<event.button.y&&event.button.y<445)
    {

        if(Grid[2][6].b_n == color)
        {
            i_d=2;
            j_d=6;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&415<event.button.y&&event.button.y<445)
    {

        if(Grid[2][5].b_n == color)
        {
            i_d=2;
            j_d=5;
            return 0;
        }
    }
    if(690<event.button.x&&event.button.x<720&&415<event.button.y&&event.button.y<445)
    {

        if(Grid[2][4].b_n == color)
        {
            i_d=2;
            j_d=4;
            return 0;
        }
    }

    if(408<event.button.x&&event.button.x<438&&505<event.button.y&&event.button.y<535)
    {

        if(Grid[1][6].b_n == color)
        {
            i_d=1;
            j_d=6;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&505<event.button.y&&event.button.y<535)
    {

        if(Grid[1][5].b_n == color)
        {
            i_d=1;
            j_d=5;
            return 0;
        }
    }
    if(780<event.button.x&&event.button.x<810&&505<event.button.y&&event.button.y<535)
    {

        if(Grid[1][4].b_n == color)
        {
            i_d=1;
            j_d=4;
            return 0;
        }
    }

    if(315<event.button.x&&event.button.x<345&&590<event.button.y&&event.button.y<620)
    {

        if(Grid[0][6].b_n == color)
        {
            i_d=0;
            j_d=6;
            return 0;
        }
    }
    if(595<event.button.x&&event.button.x<625&&590<event.button.y&&event.button.y<620)
    {

        if(Grid[0][5].b_n == color)
        {
            i_d=0;
            j_d=5;
            return 0;
        }
    }
    if(875<event.button.x&&event.button.x<905&&590<event.button.y&&event.button.y<620)
    {

        if(Grid[0][4].b_n == color)
        {
            i_d=0;
            j_d=4;
            return 0;
        }
    }
    return 1;


}
void coordonnee(int i,int j) // donne la position d'un pion en px
{
    if(i==0 && j==0)
    {
        positionSapin.x = 305;//310
        positionSapin.y = 50;//55
    }
    if(i==0 && j==1)
    {
        positionSapin.x = 585;
        positionSapin.y = 50;
    }
    if(i==0 && j==2)
    {
        positionSapin.x = 865;
        positionSapin.y = 50;
    }

    if(i==1 && j==0)
    {
        positionSapin.x = 398;
        positionSapin.y = 140;
    }
    if(i==1 && j==1)
    {
        positionSapin.x = 585;
        positionSapin.y = 140;
    }
    if(i==1 && j==2)
    {
        positionSapin.x = 770;
        positionSapin.y = 140;
    }

    if(i==2 && j==0)
    {
        positionSapin.x = 490;
        positionSapin.y = 230;
    }
    if(i==2 && j==1)
    {
        positionSapin.x = 585;
        positionSapin.y = 230;
    }
    if(i==2 && j==2)
    {
        positionSapin.x = 680;
        positionSapin.y = 230;
    }

    if(i==0 && j==7)
    {
        positionSapin.x = 305;
        positionSapin.y = 320;
    }
    if(i==1 && j==7)
    {
        positionSapin.x = 395;
        positionSapin.y = 320;
    }
    if(i==2 && j==7)
    {
        positionSapin.x = 485;
        positionSapin.y = 320;
    }
    if(i==2 && j==3)
    {
        positionSapin.x = 675;
        positionSapin.y = 320;
    }
    if(i==1 && j==3)
    {
        positionSapin.x = 765;
        positionSapin.y = 320;
    }
    if(i==0 && j==3)
    {
        positionSapin.x = 855;
        positionSapin.y = 320;
    }

    if(i==2 && j==6)
    {
        positionSapin.x = 490;
        positionSapin.y = 405;
    }
    if(i==2 && j==5)
    {
        positionSapin.x = 585;
        positionSapin.y = 405;
    }
    if(i==2 && j==4)
    {
        positionSapin.x = 680;
        positionSapin.y = 405;
    }

    if(i==1 && j==6)
    {
        positionSapin.x = 398;
        positionSapin.y = 495;
    }
    if(i==1 && j==5)
    {
        positionSapin.x = 585;
        positionSapin.y = 495;
    }
    if(i==1 && j==4)
    {
        positionSapin.x = 770;
        positionSapin.y = 495;
    }

    if(i==0 && j==6)
    {
        positionSapin.x = 305;
        positionSapin.y = 580;
    }
    if(i==0 && j==5)
    {
        positionSapin.x = 585;
        positionSapin.y = 580;
    }
    if(i==0 && j==4)
    {
        positionSapin.x = 865;
        positionSapin.y = 580;
    }

}
void joueur() // qui a le droit de jouer
{
    positionQ.x=60;
    positionQ.y=40;
    for(int i=0; i<(poser/2); i++)
    {
        SDL_BlitSurface(blanc, NULL, ecran, &positionQ);
        positionQ.x+=70;
        SDL_BlitSurface(noir, NULL, ecran, &positionQ);
        positionQ.x-=70;
        positionQ.y+=55;
        if(poser % 2 !=0)
            SDL_BlitSurface(blanc, NULL, ecran, &positionQ);
    }
    if(poser == 1)
        SDL_BlitSurface(blanc, NULL, ecran, &positionQ);
    if(color==1)
    {
        ball=IMG_Load("images/n.png");
        SDL_BlitSurface(ball, NULL, ecran, &positionBall);
    }
    if(color==-1)
    {
        ball=IMG_Load("images/b.png");
        SDL_BlitSurface(ball, NULL, ecran, &positionBall);
    }
    SDL_Flip(ecran);
}
void PoserPion() // poser les pions sur la table
{
    //imageDeFond = IMG_Load("images/05.jpg");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    joueur();
    for(int i=0; i<3; i++)
        for(int j=0; j<8; j++)
        {
            if(Grid[i][j].b_n== 1)
            {
                coordonnee(i,j);
                SDL_BlitSurface(noir, NULL, ecran, &positionSapin);
                //SDL_Flip(ecran);
            }
            if(Grid[i][j].b_n== -1)
            {
                coordonnee(i,j);
                SDL_BlitSurface(blanc, NULL, ecran, &positionSapin);
                //SDL_Flip(ecran);
            }

        }
    SDL_Flip(ecran);
}
int moulin(int x, int y) // detecte un moulin
{

    if(y%2 != 0)
    {
        if(Grid[0][y].b_n == Grid[1][y].b_n && Grid[0][y].b_n == Grid[2][y].b_n)
            return 0;
        if(Grid[x][y].b_n == Grid[x][(y+1)%8].b_n && Grid[x][y].b_n == Grid[x][y-1].b_n )
            return 0;
    }
    else
    {

        if(Grid[x][y].b_n == Grid[x][(8+((y+1)%8))%8].b_n && Grid[x][y].b_n == Grid[x][(8+((y+2)%8))%8].b_n)
            return 0;
        if(Grid[x][y].b_n == Grid[x][(8+((y-1)%8))%8].b_n && Grid[x][y].b_n == Grid[x][(8+((y-2)%8))%8].b_n)
            return 0;
    }
    return 1;
}
int possibleDeCapture(int c) // possibilite de capture une pion
{
    for(int i=0; i<3; i++)
        for(int j=0; j<8; j++)
        {
            if(Grid[i][j].b_n==c && moulin(i,j))
                return 1;
        }
    return 0;
}
int estBloque(int x, int y) // est ce que un pion est bloque c-a-d degree de liberte est null
{
    if(y %2 ==0)
    {
        if(Grid[x][(8+((y+1)%8))%8].b_n==0|| Grid[x][(8+((y-1)%8))%8].b_n==0)
        {
            return 0;
        }
    }
    else
    {
        if(x==1)
        {
            if(Grid[x][(8+((y+1)%8))%8].b_n==0 || Grid[x][(8+((y-1)%8))%8].b_n==0 || Grid[0][y].b_n==0 || Grid[2][y].b_n==0)
                return 0;
        }
        else if(x == 0)
        {
            if(Grid[x][(8+((y+1)%8))%8].b_n==0 || Grid[x][(8+((y-1)%8))%8].b_n==0 || Grid[1][y].b_n==0 )
                return 0;
        }
        else
        {
            if(Grid[x][(8+((y+1)%8))%8].b_n==0 || Grid[x][(8+((y-1)%8))%8].b_n==0 || Grid[1][y].b_n==0)
                return 0;
        }
    }
    return 1;


}
int joueurBloque(int c) // est ce que un joueur est bloqué
{
    for(int i=0; i<3; i++)
        for(int j=0; j<7; j++)
        {
            if(Grid[i][j].b_n==c && !estBloque(i,j))
                return 0;

        }
    return 1;
}
void retry() // reintialiser
{
    color=1;
    poser=18;
    Rnoir=0;
    Rblanc=0;
    i_c=0;
    j_c=0;
    i_m=0;
    j_m=0;
    i_d=0;
    j_d=0;
    i_c_m=0;
    j_c_m=0;
    i_d_m=0;
    j_d_m=0;
    p=0;
    R1=0;
    R2=0;
    for(int i=0; i<3; i++)
        for(int j=0; j<8; j++)
        {
            Grid[i][j].b_n=0;
        }
    PoserPion();
    joueur();
}
int random(int min,int max) // un entier entre min et max
{
    return (rand()%(max-min+1))+min;
}
void machine_facile_poser()
{
    do
    {
        i_c_m=random(0,2);
        j_c_m=random(0,7);
    }
    while(Grid[i_c_m][j_c_m].b_n != 0);
    Grid[i_c_m][j_c_m].b_n=color;
}

////////////////////////////////////////////////////////// AI /////////////////////////////////////////////////////////////////


int conteur;
struct NOEUD
{
    pion etat[3][8];
    int minimax;
    int derniereCouleur;//va initialer par -1
    int pionPose;
    int RBlanc;
    int RNoir;
    struct NOEUD * tab[24];
};
int moulinAI(pion etat[3][8], int x, int y) // detecte un moulin
{

    if(y%2 != 0)
    {
        if(etat[0][y].b_n == etat[1][y].b_n && etat[0][y].b_n == etat[2][y].b_n)
            return 0;
        if(etat[x][y].b_n == etat[x][(y+1)%8].b_n && etat[x][y].b_n == etat[x][y-1].b_n )
            return 0;
    }
    else
    {

        if(etat[x][y].b_n == etat[x][(8+((y+1)%8))%8].b_n && etat[x][y].b_n == etat[x][(8+((y+2)%8))%8].b_n)
            return 0;
        if(etat[x][y].b_n == etat[x][(8+((y-1)%8))%8].b_n && etat[x][y].b_n == etat[x][(8+((y-2)%8))%8].b_n)
            return 0;
    }
    return 1;
}
int possibleDeCaptureAI(pion etat[3][8], int c) // possibilite de capture une pion
{
    for(int i=0; i<3; i++)
        for(int j=0; j<8; j++)
        {
            if(etat[i][j].b_n==c && moulinAI(etat,i,j))
                return 1;
        }
    return 0;
}
int presCreerMoulin(pion etat[3][8], int x, int y)
{
    if(y % 2 == 0)
    {
        if(etat[x][(8+((y+1)%8))%8].b_n == etat[x][y].b_n && etat[x][(8+((y+2)%8))%8].b_n == 0)
            return 1;
        else if(etat[x][(8+((y+1)%8))%8].b_n == 0 && etat[x][(8+((y+2)%8))%8].b_n == etat[x][y].b_n)
            return 1;
        else if(etat[x][(8+((y-1)%8))%8].b_n == etat[x][y].b_n  && etat[x][(8+((y-2)%8))%8].b_n == 0)
            return 1;
        else if(etat[x][(8+((y-1)%8))%8].b_n == 0  && etat[x][(8+((y-2)%8))%8].b_n == etat[x][y].b_n)
            return 1;
        else
            return 0;
    }
    else
    {
        if(x == 0)
        {
            if(etat[1][y].b_n == etat[x][y].b_n && etat[2][y].b_n == 0)
                return 1;
            else if(etat[1][y].b_n == 0 && etat[2][y].b_n == etat[x][y].b_n)
                return 1;
            else
                return 0;
        }
        else if(x == 1)
        {
            if(etat[0][y].b_n == etat[x][y].b_n && etat[2][y].b_n == 0)
                return 1;
            else if(etat[0][y].b_n == 0 && etat[2][y].b_n == etat[x][y].b_n)
                return 1;
            else
                return 0;
        }
        else
        {
            if(etat[0][y].b_n == etat[x][y].b_n && etat[1][y].b_n == 0)
                return 1;
            else if(etat[0][y].b_n == 0 && etat[1][y].b_n == etat[x][y].b_n)
                return 1;
            else
                return 0;
        }
    }
}
int h(struct NOEUD* Noeud)
{
    int NombreNoirMoulin = 0;
    int NombreNoirPresMoulin = 0;
    int NombreBlancMoulin = 0;
    int NombreBlancPresMoulin = 0;
    ///Cas favorable
    //checher les moulins crees
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(Noeud->etat[i][j].b_n == 1 && !moulinAI(Noeud->etat, i, j))
            {
                NombreNoirMoulin++;
            }
        }
    }
    //Fin checher les moulins crees

    //checher les pres moulins crees
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(Noeud->etat[i][j].b_n == 1 && presCreerMoulin(Noeud->etat, i, j))
            {
                NombreNoirPresMoulin++;
            }
        }
    }
    //fin checher les pres moulins crees
    ///FIN Cas favorable

    ///Cas defavorable
    //checher les moulins crees
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(Noeud->etat[i][j].b_n == -1 && !moulinAI(Noeud->etat, i, j))
            {
                NombreBlancMoulin++;
            }
        }
    }
    //Fin checher les moulins crees

    //checher les pres moulins crees
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(Noeud->etat[i][j].b_n == -1 && presCreerMoulin(Noeud->etat, i, j))
            {
                NombreBlancPresMoulin++;
            }
        }
    }
    //fin checher les pres moulins crees
    ///FIN Cas defavorable

    return 1000*(NombreNoirMoulin - NombreBlancMoulin) + 100*(NombreNoirPresMoulin - NombreBlancPresMoulin) + 10*(Noeud->RBlanc - Noeud->RNoir);
}
void genereSeccesseurs(struct NOEUD* NoeudActuelle)
{
    ///Initialiser le tableaux des fils par NULL
    for(int i=0; i<24; i++)
    {
        NoeudActuelle->tab[i] = NULL;
    }
    ///Fin initialiser le tableaux des fils par NULL

    if(NoeudActuelle->pionPose != 0 )///phase 1
    {
        ///inseret
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 8; j++)
            {

                if(NoeudActuelle->etat[i][j].b_n == 0)
                {
                    ///crier fils
                    struct NOEUD* fils;
                    fils = (struct NOEUD*)malloc(sizeof(struct NOEUD));
                    ///crier fils

                    ///copie
                    for(int x=0; x<3; x++)
                    {
                        for(int y=0; y<8; y++)
                        {
                            fils->etat[x][y].b_n = NoeudActuelle->etat[x][y].b_n;
                        }
                    }
                    ///fin copie
                    ///Initialisation
                    fils->minimax = 0;
                    fils->derniereCouleur = NoeudActuelle->derniereCouleur * -1;
                    fils->pionPose = NoeudActuelle->pionPose;
                    fils->RBlanc = NoeudActuelle->RBlanc;
                    fils->RNoir = NoeudActuelle->RNoir;
                    ///Fin initialisation
                    ///------>>>> L'affectation de mouvement
                    fils->etat[i][j].b_n = NoeudActuelle->derniereCouleur*-1;
                    fils->pionPose--;

                    if(!moulinAI(fils->etat, i, j) && possibleDeCaptureAI(fils->etat, NoeudActuelle->derniereCouleur))
                    {
                        for(int k=0; k<3; k++)
                        {
                            for(int l=0; l<8; l++)
                            {
                                if(moulinAI(fils->etat, k, l) && fils->etat[k][l].b_n==NoeudActuelle->derniereCouleur)
                                {
                                    ///creer le vrai fils cas de moulin
                                    struct NOEUD* filsMoulin;
                                    filsMoulin = (struct NOEUD*)malloc(sizeof(struct NOEUD));
                                    ///fin creer le vrai fils cas de moulin

                                    ///copie
                                    for(int x=0; x<3; x++)
                                    {
                                        for(int y=0; y<8; y++)
                                        {
                                            filsMoulin->etat[x][y].b_n = fils->etat[x][y].b_n;
                                        }
                                    }
                                    ///fin coppie
                                    ///Initialisation
                                    filsMoulin->minimax = 0;
                                    filsMoulin->derniereCouleur = fils->derniereCouleur;
                                    filsMoulin->pionPose = fils->pionPose;
                                    filsMoulin->RBlanc = fils->RBlanc;
                                    filsMoulin->RNoir = fils->RNoir;
                                    ///Fin initialisation

                                    filsMoulin->etat[k][l].b_n = 0;

                                    if(NoeudActuelle->derniereCouleur == 1)
                                    {
                                        filsMoulin->RNoir++;
                                    }
                                    else
                                    {
                                        filsMoulin->RBlanc++;
                                    }
                                    ///Entrer les filsMoulin dans l'arbre

                                    for(int address=0; address<24; address++)
                                    {
                                        if(NoeudActuelle->tab[address] == NULL)
                                        {
                                            NoeudActuelle->tab[address] = filsMoulin;
                                            break;
                                        }
                                    }

                                    ///Fin Entrer les filsMoulin dans l'arbre
                                }
                            }
                        }
                    }
                    else
                    {

                        ///Entrer les fils dans l'arbre
                        for(int address=0; address<24; address++)
                        {
                            if(NoeudActuelle->tab[address] == NULL)
                            {
                                NoeudActuelle->tab[address] = fils;
                                break;
                            }
                        }

                        ///Fin Entrer les filsMoulin dans l'arbre
                    }
                }
            }
        }
        ///fin inseret

    }
    else ///phase 2 et phase 3
    {
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(NoeudActuelle->etat[i][j].b_n == NoeudActuelle->derniereCouleur*-1)
                {
                    for(int k=0; k<3; k++)
                    {
                        for(int l=0; l<8; l++)
                        {
                            if(NoeudActuelle->etat[k][l].b_n == 0)
                            {
                                int resultat = 0;

                                if(NoeudActuelle->derniereCouleur == 1 && NoeudActuelle->RBlanc ==6)
                                {
                                    resultat = 1;
                                }
                                else if(NoeudActuelle->derniereCouleur == -1 && NoeudActuelle->RNoir ==6)
                                {
                                    resultat = 1;
                                }
                                else
                                {
                                    if(j %2 ==0)
                                    {
                                        if((i == k) && ((l==(8+((j+1)%8))%8)|| (l==(8+((j-1)%8))%8)) )
                                        {
                                            resultat = 1;
                                        }
                                        else
                                        {
                                            resultat = 0;
                                        }
                                    }
                                    else
                                    {
                                        if(i==1)
                                        {
                                            if((k == 1) && ((l==(8+((j+1)%8))%8)|| (l==(8+((j-1)%8))%8)) )
                                            {
                                                resultat = 1;
                                            }
                                            else if((k == 0)&&(l==j))
                                            {
                                                resultat = 1;
                                            }
                                            else if((k == 2)&&(l==j))
                                            {
                                                resultat = 1;
                                            }
                                            else
                                            {
                                                resultat = 0;
                                            }
                                        }
                                        else if(i == 0)
                                        {
                                            if((k == 0) && ((l==(8+((j+1)%8))%8)|| (l==(8+((j-1)%8))%8)) )
                                            {
                                                resultat = 1;
                                            }
                                            else if((k == 1)&&(l==j))
                                            {
                                                resultat = 1;
                                            }
                                            else
                                            {
                                                resultat = 0;
                                            }

                                        }
                                        else
                                        {
                                            if((k == 2) && ((l==(8+((j+1)%8))%8)|| (l==(8+((j-1)%8))%8)) )
                                            {
                                                resultat = 1;
                                            }
                                            else if((k == 1)&&(l==j))
                                            {
                                                resultat = 1;
                                            }
                                            else
                                            {
                                                resultat = 0;
                                            }

                                        }
                                    }
                                }
                                if(resultat)
                                {
                                    ///crier fils
                                    struct NOEUD* fils;
                                    fils = (struct NOEUD*)malloc(sizeof(struct NOEUD));
                                    ///crier fils

                                    ///copie
                                    for(int x=0; x<3; x++)
                                    {
                                        for(int y=0; y<8; y++)
                                        {
                                            fils->etat[x][y].b_n = NoeudActuelle->etat[x][y].b_n;
                                        }
                                    }
                                    ///fin copie
                                    ///Initialisation
                                    fils->minimax = 0;
                                    fils->derniereCouleur = NoeudActuelle->derniereCouleur * -1;
                                    fils->pionPose = 0;
                                    fils->RBlanc = NoeudActuelle->RBlanc;
                                    fils->RNoir = NoeudActuelle->RNoir;
                                    ///Fin initialisation
                                    ///------>>>> L'affectation de mouvement
                                    fils->etat[i][j].b_n=0;
                                    fils->etat[k][l].b_n=NoeudActuelle->derniereCouleur * -1;
                                    ///------>>>> FIN L'affectation de mouvement
                                    if(!moulinAI(fils->etat, k, l) && possibleDeCaptureAI(fils->etat, NoeudActuelle->derniereCouleur))
                                    {
                                        for(int m=0; m<3; m++)
                                        {
                                            for(int n=0; n<8; n++)
                                            {
                                                if(moulinAI(fils->etat, m, n) && fils->etat[m][n].b_n==NoeudActuelle->derniereCouleur)
                                                {
                                                    ///creer le vrai fils cas de moulin
                                                    struct NOEUD* filsMoulin;
                                                    filsMoulin = (struct NOEUD*)malloc(sizeof(struct NOEUD));
                                                    ///fin creer le vrai fils cas de moulin

                                                    ///copie
                                                    for(int x=0; x<3; x++)
                                                    {
                                                        for(int y=0; y<8; y++)
                                                        {
                                                            filsMoulin->etat[x][y].b_n = fils->etat[x][y].b_n;
                                                        }
                                                    }
                                                    ///fin coppie
                                                    ///Initialisation
                                                    filsMoulin->minimax = 0;
                                                    filsMoulin->derniereCouleur = fils->derniereCouleur;
                                                    filsMoulin->pionPose = 0;
                                                    filsMoulin->RBlanc = fils->RBlanc;
                                                    filsMoulin->RNoir = fils->RNoir;
                                                    ///Fin initialisation
                                                    filsMoulin->etat[m][n].b_n = 0;
                                                    ///Capturer
                                                    if(NoeudActuelle->derniereCouleur == 1)
                                                    {
                                                        filsMoulin->RNoir++;
                                                    }
                                                    else
                                                    {
                                                        filsMoulin->RBlanc++;
                                                    }
                                                    ///Fin capturer
                                                    ///Entrer les filsMoulin dans l'arbre

                                                    for(int address=0; address<24; address++)
                                                    {
                                                        if(NoeudActuelle->tab[address] == NULL)
                                                        {
                                                            NoeudActuelle->tab[address] = filsMoulin;
                                                            break;
                                                        }
                                                    }

                                                    ///Fin Entrer les filsMoulin dans l'arbre
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {

                                        ///Entrer les fils dans l'arbre

                                        for(int address=0; address<24; address++)
                                        {
                                            if(NoeudActuelle->tab[address] == NULL)
                                            {
                                                NoeudActuelle->tab[address] = fils;
                                                break;
                                            }
                                        }

                                        ///Fin Entrer les filsMoulin dans l'arbre
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
int genereArbre(struct NOEUD* NoeudActuelle, int p)
{
    if(p == 1)
    {
        genereSeccesseurs(NoeudActuelle);
        return 0;
    }
    genereSeccesseurs(NoeudActuelle);
    for(int i=0; i<24; i++)
    {
        if(NoeudActuelle->tab[i] != NULL)
        {
            genereArbre(NoeudActuelle->tab[i], p-1);
        }
    }
}
int alphaBita(struct NOEUD* Noeud, int p, int a, int b)
{
    conteur++;
    int static v = 0;
    if(Noeud->RBlanc == 7 || Noeud->RNoir == 7 || p == 0)
    {
        Noeud->minimax = h(Noeud);
        goto outFct;
    }
    else
    {
        if(Noeud->derniereCouleur == -1)
        {
            v = -999999; /// - Infinity
            for(int i=0; i<24; i++)
            {
                if(Noeud->tab[i] != NULL)
                {
                    alphaBita(Noeud->tab[i], p-1, a, b);
                }
                v = Noeud->tab[0]->minimax;
                for(int i=0; i<24; i++)
                {
                    if(Noeud->tab[i] != NULL && v < Noeud->tab[i]->minimax)
                    {
                        v = Noeud->tab[i]->minimax;
                    }
                }
                if(v > b)
                {
                    Noeud->minimax = v;
                    goto outFct;
                }
                a = max(a, v);

            }
        }
        else
        {
            v = 999999; /// + Infinity
            for(int i=0; i<24; i++)
            {
                if(Noeud->tab[i] != NULL)
                {
                    alphaBita(Noeud->tab[i], p-1, a, b);
                }
                v = Noeud->tab[0]->minimax;
                for(int i=0; i<24; i++)
                {
                    if(Noeud->tab[i] != NULL && Noeud->tab[i]->minimax < v)
                    {
                        v = Noeud->tab[i]->minimax;
                    }
                }
                if(v < a)
                {
                    Noeud->minimax = v;
                    goto outFct;
                }
                b = min(b, v);
            }
        }

    }
    Noeud->minimax = v;
outFct:
    {

    }
}
int minimaxFonction(struct NOEUD* Noeud, int p)
{
    conteur++;
    if(Noeud->RBlanc == 7 || Noeud->RNoir == 7 || p == 0)
    {
        Noeud->minimax = h(Noeud);
    }
    else
    {
        if(Noeud->derniereCouleur == -1)
        {
            for(int i=0; i < 24; i++)
                if(Noeud->tab[i] != NULL)
                {
                    minimaxFonction(Noeud->tab[i], p-1);
                }

            Noeud->minimax = Noeud->tab[0]->minimax;
            for(int i=1; i<24; i++)
                if(Noeud->tab[i] != NULL && Noeud->minimax < Noeud->tab[i]->minimax)
                    Noeud->minimax = Noeud->tab[i]->minimax;
            //return Noeud->minimax;
        }
        else
        {
            for(int i=0; i < 24; i++)
                if(Noeud->tab[i] != NULL)
                {
                    minimaxFonction(Noeud->tab[i], p-1);
                }

            Noeud->minimax = Noeud->tab[0]->minimax;
            for(int i=1; i<24; i++)
                if(Noeud->tab[i] != NULL && Noeud->tab[i]->minimax < Noeud->minimax)
                    Noeud->minimax = Noeud->tab[i]->minimax;
            //return Noeud->minimax;
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





int main(int argc, char *argv[])

{
    srand ( time(NULL) );
    SDL_Rect positionFond;
    positionFond.x = 0; // ecran
    positionFond.y = 0;
    positionSapin.x = 0; // position pion
    positionSapin.y = 0;
    positionOk.x =0 ;
    positionOk.y =0 ;
    positionBall.x=1083;
    positionBall.y=293;
    SDL_Init(SDL_INIT_VIDEO );
    //ecran = SDL_SetVideoMode(640, 480, 32, SDL_FULLSCREEN);

    //Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1; //Initialisation de l'API Mixer
    SDL_WM_SetIcon(IMG_Load("images/100.jpg"), NULL);
    ecran = SDL_SetVideoMode(1300, 699, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("JEU DE MOULIN", NULL);
    imageDeFond = IMG_Load("images/01.jpg");

    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

    SDL_Flip(ecran);
    int continuer = 1;
    //SDL_Event event;

    // music
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }

    Mix_AllocateChannels(32); //Allouer 32 canaux
    Mix_Volume(1, MIX_MAX_VOLUME/2); //Mettre à mi-volume le post 1
    Mix_Chunk *son;//Créer un pointeur pour stocker un .WAV
    Mix_Chunk *son2;
    son = Mix_LoadWAV("son/clic0.wav"); //Charger un wav dans un pointeur
    son2 = Mix_LoadWAV("son/clic1.wav");
    Mix_VolumeChunk(son, MIX_MAX_VOLUME/4); //Mettre un volume pour ce wav
    Mix_VolumeChunk(son2, MIX_MAX_VOLUME/4);

    Mix_VolumeMusic(MIX_MAX_VOLUME /4);
    Mix_Music *musique;
    musique = Mix_LoadMUS("son/1.mp3"); //Chargement de la musique
    Mix_PlayMusic(musique, -1);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            Mix_PlayChannel(1, son, 0);//Joue le son 1 sur le canal 1 ;
H:
            imageDeFond = IMG_Load("images/02.jpg");
            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
            SDL_Flip(ecran);
            SDL_Event event;
            while (continuer)
            {
                SDL_WaitEvent(&event);
                switch(event.type)
                {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    if(344<event.button.x&&event.button.x<926&&168<event.button.y&&event.button.y<300) // jouer
                    {
                        Mix_PlayChannel(1, son, 0);
A:
                        imageDeFond = IMG_Load("images/03.jpg");
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        SDL_Flip(ecran);
                        SDL_Event event;
                        while (continuer)
                        {
                            SDL_WaitEvent(&event);
                            switch(event.type)
                            {
                            case SDL_QUIT:
                                continuer = 0;
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                            {
                                if(45<event.button.x&&event.button.x<191&&70<event.button.y&&event.button.y<204) // retour
                                {
                                    Mix_PlayChannel(1, son2, 0);
                                    goto H;
                                }
                                if(345<event.button.x&&event.button.x<930&&230<event.button.y&&event.button.y<360) // joueur vs joueur
                                {
                                    Mix_PlayChannel(1, son, 0);
                                    imageDeFond = IMG_Load("images/05.jpg");
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    joueur();
                                    SDL_Flip(ecran);
X_:
                                    if((Rnoir==7 || Rblanc==7 || joueurBloque(1) || joueurBloque(-1) )&& poser==0)
                                    {
                                        //fin
                                        if(Rnoir==7 || joueurBloque(1))
                                            gagnant = IMG_Load("images/09.jpg");
                                        else if(Rblanc==7 || joueurBloque(-1))
                                            gagnant = IMG_Load("images/08.jpg");
                                        SDL_BlitSurface(gagnant, NULL, ecran, &positionFond);
                                        SDL_Flip(ecran);
                                        SDL_Event event;
                                        while (continuer)
                                        {
                                            SDL_WaitEvent(&event);
                                            switch(event.type)
                                            {
                                            case SDL_QUIT:
                                                continuer = 0;
                                                break;
                                            case SDL_MOUSEBUTTONDOWN:
                                            {
                                                if(558<event.button.x&&event.button.x<742&&490<event.button.y&&event.button.y<670) // retry
                                                {
                                                    Mix_PlayChannel(1, son2, 0);
                                                    retry();
                                                    goto A;

                                                }

                                            }

                                            }

                                        }

                                    }
                                    SDL_Event event;
                                    while (continuer)
                                    {
                                        SDL_WaitEvent(&event);
                                        switch(event.type)
                                        {
                                        case SDL_QUIT:
                                        {
                                            continuer = 0;
                                            break;
                                        }
                                        case SDL_MOUSEBUTTONDOWN:
                                        {
                                            if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                            {
                                                Mix_PlayChannel(1, son2, 0);
                                                retry();
                                                goto A;
                                            }
                                            if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                            {
                                                Mix_PlayChannel(1, son2, 0);
                                                retry();
                                                goto X_;

                                            }
                                            if(!moulin(i_c,j_c) && p && possibleDeCapture(color)) // les moulins
                                            {
                                                p=0;
S:
                                                SDL_Event event;
                                                while (continuer)
                                                {
                                                    SDL_WaitEvent(&event);
                                                    switch(event.type)
                                                    {
                                                    case SDL_QUIT:
                                                        continuer = 0;
                                                        break;
                                                    case SDL_MOUSEBUTTONDOWN:
                                                    {
                                                        if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                        {
                                                            Mix_PlayChannel(1, son2, 0);
                                                            retry();
                                                            goto A;
                                                        }
                                                        if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                        {
                                                            Mix_PlayChannel(1, son2, 0);
                                                            retry();
                                                            goto X_;

                                                        }
                                                        if(!choix1(event))
                                                        {
                                                            /*if(!possibleDeCapture(-1*color))
                                                            {
                                                              goto X_;
                                                            }*/
                                                            if(moulin(i_m,j_m))
                                                            {
                                                                if(Grid[i_m][j_m].b_n==1)
                                                                    Rnoir+=1;  // nbr de noir recuperé
                                                                else
                                                                    Rblanc+=1; // nbr de blanc recupéré
                                                                Grid[i_m][j_m].b_n=0;
                                                                PoserPion();
                                                                goto X_;
                                                            }
                                                            else
                                                                goto S;
                                                        }
                                                        else
                                                            goto S;
                                                    }

                                                    }

                                                }

                                            }

                                            if(poser==0) // phase 2 : deplacement
                                            {

                                                if(!choix2(event)) // i_d && j_d
                                                {
                                                    if(estBloque(i_d,j_d) && Rnoir!=6 && Rblanc!=6)
                                                        goto X_;
                                                    coordonnee(i_d,j_d);
                                                    SDL_BlitSurface(ok, NULL, ecran, &positionSapin);
                                                    SDL_Flip(ecran);
S_:
                                                    SDL_Event event;
                                                    while (continuer)
                                                    {
                                                        SDL_WaitEvent(&event);
                                                        switch(event.type)
                                                        {
                                                        case SDL_QUIT:
                                                            continuer = 0;
                                                            break;
                                                        case SDL_MOUSEBUTTONDOWN:
                                                        {
                                                            if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                            {
                                                                Mix_PlayChannel(1, son2, 0);
                                                                retry();
                                                                goto A;
                                                            }
                                                            if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                            {
                                                                Mix_PlayChannel(1, son2, 0);
                                                                retry();
                                                                goto X_;

                                                            }
                                                            if(!choix(event)) // i_c && j_c
                                                            {
                                                                p=1;
                                                                /*Grid[i_d][j_d].b_n=0;
                                                                color =color * -1;
                                                                PoserPion();
                                                                goto X_;*/

                                                                //
                                                                if(Rblanc ==6 && color==-1)
                                                                {
                                                                    Grid[i_d][j_d].b_n=0;
                                                                    color =1;
                                                                    PoserPion();
                                                                    goto X_;
                                                                }
                                                                else if(Rnoir ==6 && color==1)
                                                                {
                                                                    Grid[i_d][j_d].b_n=0;
                                                                    color =-1;
                                                                    PoserPion();
                                                                    goto X_;
                                                                }
                                                                else
                                                                {
                                                                    if(j_d %2 ==0)
                                                                    {
                                                                        if((i_d == i_c) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                        {
                                                                            Grid[i_d][j_d].b_n=0;
                                                                            color =color * -1;
                                                                            PoserPion();
                                                                            goto X_;
                                                                        }
                                                                        else
                                                                        {
                                                                            Grid[i_c][j_c].b_n=0;
                                                                            goto S_;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        if(i_d==1)
                                                                        {
                                                                            if((i_c == 1) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto X_;
                                                                            }
                                                                            if((i_c == 0)&&(j_c==j_d))
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto X_;
                                                                            }
                                                                            if((i_c == 2)&&(j_c==j_d))
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto X_;
                                                                            }
                                                                            else
                                                                            {
                                                                                Grid[i_c][j_c].b_n=0;
                                                                                goto S_;
                                                                            }
                                                                        }
                                                                        else if(i_d == 0)
                                                                        {
                                                                            if((i_c == 0) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto X_;
                                                                            }
                                                                            if((i_c == 1)&&(j_c==j_d))
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto X_;
                                                                            }
                                                                            else
                                                                            {
                                                                                Grid[i_c][j_c].b_n=0;
                                                                                goto S_;
                                                                            }

                                                                        }
                                                                        else
                                                                        {
                                                                            if((i_c == 2) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto X_;
                                                                            }
                                                                            if((i_c == 1)&&(j_c==j_d))
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto X_;
                                                                            }
                                                                            else
                                                                            {
                                                                                Grid[i_c][j_c].b_n=0;
                                                                                goto S_;
                                                                            }

                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            else
                                                                goto S_;
                                                        }

                                                        }

                                                    }
                                                }
                                                else
                                                    goto X_;


                                            }
                                            if(poser!=0) //phase 1 : poser les pions
                                            {
                                                //joueur(); // tour
                                                if(!choix(event))
                                                {
                                                    p=1;
                                                    color =color * -1;
                                                    poser=poser-1;
                                                }
                                                else
                                                    goto X_ ;
                                                PoserPion();
                                            }



                                        }

                                        }

                                    }



                                }
                                if(345<event.button.x&&event.button.x<930&&406<event.button.y&&event.button.y<540) // joueur vs machine
                                {
                                    Mix_PlayChannel(1, son, 0);
B:
                                    imageDeFond = IMG_Load("images/04.jpg");
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_Flip(ecran);
                                    SDL_Event event;
                                    while (continuer)
                                    {
                                        SDL_WaitEvent(&event);
                                        switch(event.type)
                                        {
                                        case SDL_QUIT:
                                            continuer = 0;
                                            break;
                                        case SDL_MOUSEBUTTONDOWN:
                                        {
                                            if(45<event.button.x&&event.button.x<191&&70<event.button.y&&event.button.y<204) // retour
                                            {
                                                Mix_PlayChannel(1, son2, 0);
                                                goto A;
                                            }
                                            if(345<event.button.x&&event.button.x<930&&230<event.button.y&&event.button.y<360) // difficile
                                            {
                                                Mix_PlayChannel(1, son, 0);
                                                imageDeFond = IMG_Load("images/05.jpg");
                                                SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                                joueur();
                                                SDL_Flip(ecran);
BB:
                                                SDL_Event event;
                                                while (continuer)
                                                {
                                                    SDL_WaitEvent(&event);
                                                    switch(event.type)
                                                    {
                                                    case SDL_QUIT:
                                                        continuer = 0;
                                                        break;
                                                    case SDL_MOUSEBUTTONDOWN:
                                                    {
                                                        if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                        {
                                                            Mix_PlayChannel(1, son2, 0);
                                                            retry();
                                                            goto B;
                                                        }
                                                        if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                        {
                                                            Mix_PlayChannel(1, son2, 0);
                                                            retry();
                                                            goto BB;

                                                        }
                                                        if(poser==0)// phase de deplacement
                                                        {
                                                            color=-1;
                                                            if(Rnoir==7 || Rblanc==7 || joueurBloque(1) || joueurBloque(-1))
                                                            {
                                                                //fin
                                                                if(Rnoir==7 || joueurBloque(1))
                                                                    gagnant = IMG_Load("images/09.jpg");// blanc
                                                                else
                                                                    gagnant = IMG_Load("images/08.jpg"); // noir
                                                                SDL_BlitSurface(gagnant, NULL, ecran, &positionFond);
                                                                SDL_Flip(ecran);
                                                                SDL_Event event;
                                                                while (continuer)
                                                                {
                                                                    SDL_WaitEvent(&event);
                                                                    switch(event.type)
                                                                    {
                                                                    case SDL_QUIT:
                                                                        continuer = 0;
                                                                        break;
                                                                    case SDL_MOUSEBUTTONDOWN:
                                                                    {
                                                                        if(558<event.button.x&&event.button.x<742&&490<event.button.y&&event.button.y<670) // retry
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            retry();
                                                                            goto A;

                                                                        }

                                                                    }

                                                                    }

                                                                }
                                                            }
                                                            if(!choix2(event)) // i_d && j_d
                                                            {
                                                                if(estBloque(i_d,j_d) && Rnoir!=6 && Rblanc!=6)
                                                                    goto BB;
                                                                coordonnee(i_d,j_d);
                                                                SDL_BlitSurface(ok, NULL, ecran, &positionSapin);
                                                                SDL_Flip(ecran);
MM:
                                                                SDL_Event event;
                                                                while (continuer)
                                                                {
                                                                    SDL_WaitEvent(&event);
                                                                    switch(event.type)
                                                                    {
                                                                    case SDL_QUIT:
                                                                        continuer = 0;
                                                                        break;
                                                                    case SDL_MOUSEBUTTONDOWN:
                                                                    {
                                                                        if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            goto B;
                                                                        }
                                                                        if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            goto BB;

                                                                        }
                                                                        if(!choix(event)) // i_c && j_c
                                                                        {
                                                                            p=1;
                                                                            if(Rblanc ==6 /*&& color==-1*/)
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =1;
                                                                                PoserPion();
                                                                                goto outt;
                                                                            }
                                                                            else if(Rnoir ==6 /*&& color==1*/)
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =-1;
                                                                                PoserPion();
                                                                                goto outt;
                                                                            }
                                                                            else
                                                                            {
                                                                                if(j_d %2 ==0)
                                                                                {
                                                                                    if((i_d == i_c) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                                    {
                                                                                        Grid[i_d][j_d].b_n=0;
                                                                                        color =color * -1;
                                                                                        PoserPion();
                                                                                        goto outt;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        Grid[i_c][j_c].b_n=0;
                                                                                        goto MM;
                                                                                    }
                                                                                }
                                                                                else
                                                                                {
                                                                                    if(i_d==1)
                                                                                    {
                                                                                        if((i_c == 1) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto outt;
                                                                                        }
                                                                                        if((i_c == 0)&&(j_c==j_d))
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto outt;
                                                                                        }
                                                                                        if((i_c == 2)&&(j_c==j_d))
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto outt;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            Grid[i_c][j_c].b_n=0;
                                                                                            goto MM;
                                                                                        }
                                                                                    }
                                                                                    else if(i_d == 0)
                                                                                    {
                                                                                        if((i_c == 0) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto outt;
                                                                                        }
                                                                                        if((i_c == 1)&&(j_c==j_d))
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto outt;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            Grid[i_c][j_c].b_n=0;
                                                                                            goto MM;
                                                                                        }

                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        if((i_c == 2) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto outt;
                                                                                        }
                                                                                        if((i_c == 1)&&(j_c==j_d))
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto outt;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            Grid[i_c][j_c].b_n=0;
                                                                                            goto MM;
                                                                                        }

                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                        else
                                                                            goto MM;
                                                                    }

                                                                    }

                                                                }
                                                            }
                                                            else
                                                                goto BB;

outt:
                                                            if(!moulin(i_c,j_c) && p && possibleDeCapture(color)) // les moulins
                                                            {
                                                                p=0;
NN:
                                                                SDL_Event event;
                                                                while (continuer)
                                                                {
                                                                    SDL_WaitEvent(&event);
                                                                    switch(event.type)
                                                                    {
                                                                    case SDL_QUIT:
                                                                        continuer = 0;
                                                                        break;
                                                                    case SDL_MOUSEBUTTONDOWN:
                                                                    {
                                                                        if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            goto B;
                                                                        }
                                                                        if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            //goto B_;

                                                                        }
                                                                        if(!choix1(event))
                                                                        {
                                                                            if(moulin(i_m,j_m))
                                                                            {
                                                                                Rblanc++;
                                                                                Grid[i_m][j_m].b_n=0;
                                                                                PoserPion();
                                                                                goto outt1;

                                                                            }
                                                                            else
                                                                                goto NN;
                                                                        }
                                                                        else
                                                                            goto NN;
                                                                    }

                                                                    }

                                                                }

                                                            }
outt1:
                                                            {
                                                                color=-1;
                                                                struct NOEUD* Pointeur;
                                                                Pointeur = (struct NOEUD*)malloc(sizeof(struct NOEUD));
                                                                for(int x=0; x<3; x++)
                                                                {
                                                                    for(int y=0; y<8; y++)
                                                                    {
                                                                        Pointeur->etat[x][y].b_n = Grid[x][y].b_n;
                                                                    }
                                                                }
                                                                ///fin copie
                                                                ///Initialisation
                                                                Pointeur->minimax = 0;
                                                                Pointeur->derniereCouleur = -1;
                                                                Pointeur->pionPose = poser;
                                                                Pointeur->RBlanc = Rblanc;
                                                                Pointeur->RNoir = Rnoir;
                                                                ///Fin initialisation
                                                                conteur=0;
                                                                genereArbre(Pointeur, 3);
                                                                //alphaBita(Pointeur, 3, -999999, 999999);
                                                                minimaxFonction(Pointeur, 3);
                                                                for(int i=0; i<24; i++)
                                                                {
                                                                    if(Pointeur->tab[i] != NULL && Pointeur->tab[i]->minimax == Pointeur->minimax)
                                                                    {
                                                                        Rnoir=Pointeur->tab[i]->RNoir;
                                                                        Rblanc=Pointeur->tab[i]->RBlanc;
                                                                        for(int x=0; x<3; x++)
                                                                            for(int y=0; y<8; y++)
                                                                                Grid[x][y].b_n = Pointeur->tab[i]->etat[x][y].b_n;
                                                                        break;
                                                                    }
                                                                }
                                                                PoserPion();


                                                            }

                                                        }
                                                        if(poser!=0) //phase 1 : poser les pions
                                                        {
                                                            color=-1;
                                                            if(!choix(event))
                                                            {
                                                                p=1;
                                                                color =color * -1;
                                                                poser=poser-1;
                                                            }
                                                            else
                                                            {
                                                                goto BB;
                                                            }
                                                            PoserPion();

                                                            // moulin pour le joueur
                                                            if(!moulin(i_c,j_c) && p && possibleDeCapture(color)) // les moulins
                                                            {
                                                                p=0;
N_:
                                                                SDL_Event event;
                                                                while (continuer)
                                                                {
                                                                    SDL_WaitEvent(&event);
                                                                    switch(event.type)
                                                                    {
                                                                    case SDL_QUIT:
                                                                        continuer = 0;
                                                                        break;
                                                                    case SDL_MOUSEBUTTONDOWN:
                                                                    {
                                                                        if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            goto B;
                                                                        }
                                                                        if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            //goto B_;

                                                                        }
                                                                        if(!choix1(event))
                                                                        {
                                                                            if(moulin(i_m,j_m))
                                                                            {
                                                                                Rblanc++;
                                                                                Grid[i_m][j_m].b_n=0;
                                                                                PoserPion();
                                                                                goto sortirr;

                                                                            }
                                                                            else
                                                                                goto N_;
                                                                        }
                                                                        else
                                                                            goto N_;
                                                                    }

                                                                    }

                                                                }

                                                            }
sortirr:
                                                            {

                                                                color=-1;
                                                                struct NOEUD* Pointeur;
                                                                Pointeur = (struct NOEUD*)malloc(sizeof(struct NOEUD));
                                                                for(int x=0; x<3; x++)
                                                                {
                                                                    for(int y=0; y<8; y++)
                                                                    {
                                                                        Pointeur->etat[x][y].b_n = Grid[x][y].b_n;
                                                                    }
                                                                }
                                                                ///fin copie
                                                                ///Initialisation
                                                                Pointeur->minimax = 0;
                                                                Pointeur->derniereCouleur = -1;
                                                                Pointeur->pionPose = poser;
                                                                Pointeur->RBlanc = Rblanc;
                                                                Pointeur->RNoir = Rnoir;
                                                                ///Fin initialisation
                                                                conteur=0;
                                                                genereArbre(Pointeur, 3);
                                                                //alphaBita(Pointeur, 3, -999999, 999999);
                                                                minimaxFonction(Pointeur, 3);
                                                                for(int i=0; i<24; i++)
                                                                {
                                                                    if(Pointeur->tab[i] != NULL && Pointeur->tab[i]->minimax == Pointeur->minimax)
                                                                    {
                                                                        Rnoir=Pointeur->tab[i]->RNoir;
                                                                        Rblanc=Pointeur->tab[i]->RBlanc;
                                                                        for(int x=0; x<3; x++)
                                                                            for(int y=0; y<8; y++)
                                                                                Grid[x][y].b_n = Pointeur->tab[i]->etat[x][y].b_n;
                                                                        poser--;
                                                                        break;
                                                                    }
                                                                }

                                                                PoserPion();
                                                            }

                                                        }





                                                    }

                                                    }

                                                }

                                            }
                                            if(345<event.button.x&&event.button.x<930&&406<event.button.y&&event.button.y<540) // facile
                                            {
                                                Mix_PlayChannel(1, son, 0);
                                                imageDeFond = IMG_Load("images/05.jpg");
                                                SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                                joueur();
                                                SDL_Flip(ecran);
B_:

                                                SDL_Event event;
                                                while (continuer)
                                                {
                                                    SDL_WaitEvent(&event);
                                                    switch(event.type)
                                                    {
                                                    case SDL_QUIT:
                                                        continuer = 0;
                                                        break;
                                                    case SDL_MOUSEBUTTONDOWN:
                                                    {
                                                        if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                        {
                                                            Mix_PlayChannel(1, son2, 0);
                                                            retry();
                                                            goto B;
                                                        }
                                                        if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                        {
                                                            Mix_PlayChannel(1, son2, 0);
                                                            retry();
                                                            goto B_;

                                                        }

                                                        if(poser==0)// phase de deplacement
                                                        {
                                                            if((Rnoir==7 || Rblanc==7 || joueurBloque(1) || joueurBloque(-1))&& poser==0)
                                                            {
                                                                //fin
                                                                if(Rnoir==7 || joueurBloque(1))
                                                                    gagnant = IMG_Load("images/09.jpg");
                                                                else
                                                                    gagnant = IMG_Load("images/08.jpg");
                                                                SDL_BlitSurface(gagnant, NULL, ecran, &positionFond);
                                                                SDL_Flip(ecran);
                                                                SDL_Event event;
                                                                while (continuer)
                                                                {
                                                                    SDL_WaitEvent(&event);
                                                                    switch(event.type)
                                                                    {
                                                                    case SDL_QUIT:
                                                                        continuer = 0;
                                                                        break;
                                                                    case SDL_MOUSEBUTTONDOWN:
                                                                    {
                                                                        if(558<event.button.x&&event.button.x<742&&490<event.button.y&&event.button.y<670) // retry
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            retry();
                                                                            goto A;

                                                                        }

                                                                    }

                                                                    }

                                                                }
                                                            }
                                                            if(!choix2(event)) // i_d && j_d
                                                            {
                                                                if(estBloque(i_d,j_d) && Rnoir!=6 && Rblanc!=6)
                                                                    goto B_;
                                                                coordonnee(i_d,j_d);
                                                                SDL_BlitSurface(ok, NULL, ecran, &positionSapin);
                                                                SDL_Flip(ecran);
M:
                                                                SDL_Event event;
                                                                while (continuer)
                                                                {
                                                                    SDL_WaitEvent(&event);
                                                                    switch(event.type)
                                                                    {
                                                                    case SDL_QUIT:
                                                                        continuer = 0;
                                                                        break;
                                                                    case SDL_MOUSEBUTTONDOWN:
                                                                    {
                                                                        if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            goto B;
                                                                        }
                                                                        if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            goto B_;

                                                                        }
                                                                        if(!choix(event)) // i_c && j_c
                                                                        {
                                                                            p=1;
                                                                            if(Rblanc ==6 && color==-1)
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =1;
                                                                                PoserPion();
                                                                                goto out;
                                                                            }
                                                                            else if(Rnoir ==6 && color==1)
                                                                            {
                                                                                Grid[i_d][j_d].b_n=0;
                                                                                color =-1;
                                                                                PoserPion();
                                                                                goto out;
                                                                            }
                                                                            else
                                                                            {
                                                                                if(j_d %2 ==0)
                                                                                {
                                                                                    if((i_d == i_c) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                                    {
                                                                                        Grid[i_d][j_d].b_n=0;
                                                                                        color =color * -1;
                                                                                        PoserPion();
                                                                                        goto out;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        Grid[i_c][j_c].b_n=0;
                                                                                        goto M;
                                                                                    }
                                                                                }
                                                                                else
                                                                                {
                                                                                    if(i_d==1)
                                                                                    {
                                                                                        if((i_c == 1) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto out;
                                                                                        }
                                                                                        if((i_c == 0)&&(j_c==j_d))
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto out;
                                                                                        }
                                                                                        if((i_c == 2)&&(j_c==j_d))
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto out;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            Grid[i_c][j_c].b_n=0;
                                                                                            goto M;
                                                                                        }
                                                                                    }
                                                                                    else if(i_d == 0)
                                                                                    {
                                                                                        if((i_c == 0) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto out;
                                                                                        }
                                                                                        if((i_c == 1)&&(j_c==j_d))
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto out;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            Grid[i_c][j_c].b_n=0;
                                                                                            goto M;
                                                                                        }

                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        if((i_c == 2) && ((j_c==(8+((j_d+1)%8))%8)|| (j_c==(8+((j_d-1)%8))%8)) )
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto out;
                                                                                        }
                                                                                        if((i_c == 1)&&(j_c==j_d))
                                                                                        {
                                                                                            Grid[i_d][j_d].b_n=0;
                                                                                            color =color * -1;
                                                                                            PoserPion();
                                                                                            goto out;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            Grid[i_c][j_c].b_n=0;
                                                                                            goto M;
                                                                                        }

                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                        else
                                                                            goto M;
                                                                    }

                                                                    }

                                                                }
                                                            }
                                                            else
                                                                goto B_;

out:
                                                            if(!moulin(i_c,j_c) && p && possibleDeCapture(color)) // les moulins
                                                            {
                                                                p=0;
N_N:
                                                                SDL_Event event;
                                                                while (continuer)
                                                                {
                                                                    SDL_WaitEvent(&event);
                                                                    switch(event.type)
                                                                    {
                                                                    case SDL_QUIT:
                                                                        continuer = 0;
                                                                        break;
                                                                    case SDL_MOUSEBUTTONDOWN:
                                                                    {
                                                                        if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            goto B;
                                                                        }
                                                                        if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            //goto B_;

                                                                        }
                                                                        if(!choix1(event))
                                                                        {
                                                                            if(moulin(i_m,j_m))
                                                                            {
                                                                                Rblanc++;
                                                                                Grid[i_m][j_m].b_n=0;
                                                                                PoserPion();
                                                                                goto out1;

                                                                            }
                                                                            else
                                                                                goto N_N;
                                                                        }
                                                                        else
                                                                            goto N_N;
                                                                    }

                                                                    }

                                                                }

                                                            }

                                                            // deplacer de la machine
out1:
                                                            {
again:
                                                                do
                                                                {
                                                                    i_d_m=random(0,2);
                                                                    j_d_m=random(0,7);
                                                                }
                                                                while(Grid[i_d_m][j_d_m].b_n!= color);
                                                                if(estBloque(i_d_m,j_d_m) && Rnoir!=6 && Rblanc!=6)
                                                                    goto again;
                                                                coordonnee(i_d_m,j_d_m);
                                                                SDL_BlitSurface(ok, NULL, ecran, &positionSapin);
                                                                SDL_Flip(ecran);
M_:
                                                                do
                                                                {
                                                                    i_c_m=random(0,2);
                                                                    j_c_m=random(0,7);
                                                                }
                                                                while(Grid[i_c_m][j_c_m].b_n !=0);
                                                                if(Rblanc ==6 && color==-1)
                                                                {
                                                                    Grid[i_d_m][j_d_m].b_n=0;
                                                                    Grid[i_c_m][j_c_m].b_n=color;
                                                                    color =1;
                                                                    PoserPion();
                                                                }
                                                                else if(Rnoir ==6 && color==1)
                                                                {
                                                                    Grid[i_d_m][j_d_m].b_n=0;
                                                                    Grid[i_c_m][j_c_m].b_n=color;
                                                                    color =-1;
                                                                    PoserPion();
                                                                }
                                                                else
                                                                {
                                                                    if(j_d_m %2 ==0)
                                                                    {
                                                                        if((i_d_m == i_c_m) && ((j_c_m==(8+((j_d_m+1)%8))%8)|| (j_c_m==(8+((j_d_m-1)%8))%8)) )
                                                                        {
                                                                            Grid[i_d_m][j_d_m].b_n=0;
                                                                            Grid[i_c_m][j_c_m].b_n=color;
                                                                            color =color * -1;
                                                                            PoserPion();
                                                                            goto out_;

                                                                        }
                                                                        else
                                                                        {
                                                                            goto M_;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        if(i_d_m==1)
                                                                        {
                                                                            if((i_c_m == 1) && ((j_c_m==(8+((j_d_m+1)%8))%8)|| (j_c_m==(8+((j_d_m-1)%8))%8)) )
                                                                            {
                                                                                Grid[i_d_m][j_d_m].b_n=0;
                                                                                Grid[i_c_m][j_c_m].b_n=color;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto out_;
                                                                            }
                                                                            if((i_c_m == 0)&&(j_c_m==j_d_m))
                                                                            {
                                                                                Grid[i_d_m][j_d_m].b_n=0;
                                                                                Grid[i_c_m][j_c_m].b_n=color;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto out_;
                                                                            }
                                                                            if((i_c_m == 2)&&(j_c_m==j_d_m))
                                                                            {
                                                                                Grid[i_d_m][j_d_m].b_n=0;
                                                                                Grid[i_c_m][j_c_m].b_n=color;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto out_;
                                                                            }
                                                                            else
                                                                            {
                                                                                goto M_;
                                                                            }
                                                                        }
                                                                        else if(i_d_m == 0)
                                                                        {
                                                                            if((i_c_m == 0) && ((j_c_m==(8+((j_d_m+1)%8))%8)|| (j_c_m==(8+((j_d_m-1)%8))%8)) )
                                                                            {
                                                                                Grid[i_d_m][j_d_m].b_n=0;
                                                                                Grid[i_c_m][j_c_m].b_n=color;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto out_;
                                                                            }
                                                                            if((i_c_m == 1)&&(j_c_m==j_d_m))
                                                                            {
                                                                                Grid[i_d_m][j_d_m].b_n=0;
                                                                                Grid[i_c_m][j_c_m].b_n=color;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto out_;
                                                                            }
                                                                            else
                                                                            {
                                                                                goto M_;
                                                                            }

                                                                        }
                                                                        else
                                                                        {
                                                                            if((i_c_m == 2) && ((j_c_m==(8+((j_d_m+1)%8))%8)|| (j_c_m==(8+((j_d_m-1)%8))%8)) )
                                                                            {
                                                                                Grid[i_d_m][j_d_m].b_n=0;
                                                                                Grid[i_c_m][j_c_m].b_n=color;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto out_;
                                                                            }
                                                                            if((i_c_m == 1)&&(j_c_m==j_d_m))
                                                                            {
                                                                                Grid[i_d_m][j_d_m].b_n=0;
                                                                                Grid[i_c_m][j_c_m].b_n=color;
                                                                                color =color * -1;
                                                                                PoserPion();
                                                                                goto out_;
                                                                            }
                                                                            else
                                                                            {
                                                                                goto M_;
                                                                            }

                                                                        }
                                                                    }
                                                                }

                                                            }
out_:
                                                            if(!moulin(i_c_m,j_c_m) && possibleDeCapture(color))
                                                            {

                                                                int i,j;
tryAgain:
                                                                i = random(0,2);
                                                                j = random(0,7);
                                                                if(Grid[i][j].b_n != color || !moulin(i,j))
                                                                {
                                                                    goto tryAgain;
                                                                }
                                                                Grid[i][j].b_n=0;
                                                                Rnoir++;
                                                                PoserPion();

                                                            }


                                                        }
                                                        if(poser!=0) //phase 1 : poser les pions
                                                        {
                                                            if(!choix(event))
                                                            {
                                                                p=1;
                                                                color =color * -1;
                                                                poser=poser-1;
                                                            }
                                                            else
                                                            {
                                                                goto B_;
                                                            }
                                                            PoserPion();

                                                            // moulin pour le joueur
                                                            if(!moulin(i_c,j_c) && p && possibleDeCapture(color)) // les moulins
                                                            {
                                                                p=0;
N:
                                                                SDL_Event event;
                                                                while (continuer)
                                                                {
                                                                    SDL_WaitEvent(&event);
                                                                    switch(event.type)
                                                                    {
                                                                    case SDL_QUIT:
                                                                        continuer = 0;
                                                                        break;
                                                                    case SDL_MOUSEBUTTONDOWN:
                                                                    {
                                                                        if(58<event.button.x&&event.button.x<180&&555<event.button.y&&event.button.y<665) // retour
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            goto B;
                                                                        }
                                                                        if(1170<event.button.x&&event.button.x<1285&&555<event.button.y&&event.button.y<665) // retry
                                                                        {
                                                                            Mix_PlayChannel(1, son2, 0);
                                                                            //retry();
                                                                            //goto B_;

                                                                        }
                                                                        if(!choix1(event))
                                                                        {
                                                                            if(moulin(i_m,j_m))
                                                                            {
                                                                                Rblanc++;
                                                                                Grid[i_m][j_m].b_n=0;
                                                                                PoserPion();
                                                                                goto sortir;

                                                                            }
                                                                            else
                                                                                goto N;
                                                                        }
                                                                        else
                                                                            goto N;
                                                                    }

                                                                    }

                                                                }

                                                            }
sortir:
                                                            //joueur(); // tour de la machine
                                                            machine_facile_poser();
                                                            color=color*-1;
                                                            poser=poser-1;
                                                            PoserPion();
                                                            if(!moulin(i_c_m,j_c_m) && possibleDeCapture(color))
                                                            {

                                                                int i,j;
Again:
                                                                i = random(0,2);
                                                                j = random(0,7);
                                                                if(Grid[i][j].b_n != color || !moulin(i,j))
                                                                {
                                                                    goto Again;
                                                                }
                                                                Grid[i][j].b_n=0;
                                                                Rnoir++;
                                                                PoserPion();

                                                            }

                                                        }



                                                    }

                                                    }

                                                }



                                            }

                                        }
                                        }
                                    }
                                }
                            }

                            }
                        }
                    }
                    if(458<event.button.x&&event.button.x<816&&332<event.button.y&&event.button.y<447) // regle
                    {
                        Mix_PlayChannel(1, son, 0);
                        imageDeFond = IMG_Load("images/06.jpg");
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        SDL_Flip(ecran);
                        SDL_Event event;
                        while (continuer)
                        {
                            SDL_WaitEvent(&event);
                            switch(event.type)
                            {
                            case SDL_QUIT:
                                continuer = 0;
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                            {
                                if(45<event.button.x&&event.button.x<191&&70<event.button.y&&event.button.y<204)
                                {
                                    Mix_PlayChannel(1, son2, 0);
                                    goto H;
                                }

                            }

                            }
                        }

                    }
                    if(458<event.button.x&&event.button.x<816&&478<event.button.y&&event.button.y<594) // reglage
                    {
                        Mix_PlayChannel(1, son, 0);
                        imageDeFond = IMG_Load("images/07.jpg");
                        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                        SDL_Flip(ecran);
                        SDL_Event event;
                        while (continuer)
                        {
X:
                            SDL_WaitEvent(&event);
                            switch(event.type)
                            {
                            case SDL_QUIT:
                                continuer = 0;
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                            {
                                if(45<event.button.x&&event.button.x<191&&70<event.button.y&&event.button.y<204)
                                {
                                    Mix_PlayChannel(1, son2, 0);
                                    goto H;
                                }
                                if(290<event.button.x&&event.button.x<590&&280<event.button.y&&event.button.y<589)
                                {
                                    Mix_ResumeMusic();;
                                    goto X;

                                }
                                if(713<event.button.x&&event.button.x<1009&&280<event.button.y&&event.button.y<589)
                                {
                                    Mix_PauseMusic();
                                    goto X;

                                }

                            }

                            }
                        }

                    }
                }

                }
            }
        }




        }
    }

    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(ok);
    SDL_FreeSurface(noir);
    SDL_FreeSurface(blanc);
    SDL_FreeSurface(ball);
    SDL_FreeSurface(gagnant);
    Mix_FreeChunk(son);//Libération du son 1
    Mix_FreeChunk(son2);//Libération du son 1
    Mix_FreeMusic(musique);
    Mix_CloseAudio(); //Fermeture de l'API
    SDL_Quit();
    return EXIT_SUCCESS;

}

