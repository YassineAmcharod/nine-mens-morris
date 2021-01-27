#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct
{
    int b_n;
    int moulin;
} pion;
int poser=18;
int couleur=-1;
int niveau,colonne;
int niveau_d,colonne_d;
int R1; //pour le joueur max
int R2; //pour la machine min
pion Grid[3][8];
int profondeur=5;
int conteur;
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

int deplacement()
{
    if(R2 ==6 && couleur==-1)
    {
        Grid[niveau_d][colonne_d].b_n=0;
        Grid[niveau][colonne].b_n=couleur;
        couleur =1;
        return 1;
    }
    else if(R1 ==6 && couleur==1)
    {
        Grid[niveau_d][colonne_d].b_n=0;
        Grid[niveau][colonne].b_n=couleur;
        couleur =-1;
        return 1;
    }
    else
    {
        if(colonne_d %2 ==0)
        {
            if((niveau_d == niveau) && ((colonne==(8+((colonne_d+1)%8))%8)|| (colonne==(8+((colonne_d-1)%8))%8)) )
            {
                Grid[niveau_d][colonne_d].b_n=0;
                Grid[niveau][colonne].b_n=couleur;
                couleur =couleur * -1;
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(niveau_d==1)
            {
                if((niveau == 1) && ((colonne==(8+((colonne_d+1)%8))%8)|| (colonne==(8+((colonne_d-1)%8))%8)) )
                {
                    Grid[niveau_d][colonne_d].b_n=0;
                    Grid[niveau][colonne].b_n=couleur;
                    couleur =couleur * -1;
                    return 1;
                }
                if((niveau == 0)&&(colonne==colonne_d))
                {
                    Grid[niveau_d][colonne_d].b_n=0;
                    Grid[niveau][colonne].b_n=couleur;
                    couleur =couleur * -1;
                    return 1;
                }
                if((niveau == 2)&&(colonne==colonne_d))
                {
                    Grid[niveau_d][colonne_d].b_n=0;
                    Grid[niveau][colonne].b_n=couleur;
                    couleur =couleur * -1;
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if(niveau_d == 0)
            {
                if((niveau == 0) && ((colonne==(8+((colonne_d+1)%8))%8)|| (colonne==(8+((colonne_d-1)%8))%8)) )
                {
                    Grid[niveau_d][colonne_d].b_n=0;
                    Grid[niveau][colonne].b_n=couleur;
                    couleur =couleur * -1;
                    return 1;
                }
                if((niveau == 1)&&(colonne==colonne_d))
                {
                    Grid[niveau_d][colonne_d].b_n=0;
                    Grid[niveau][colonne].b_n=couleur;
                    couleur =couleur * -1;
                    return 1;
                }
                else
                {
                    return 0;
                }

            }
            else
            {
                if((niveau == 2) && ((colonne==(8+((colonne_d+1)%8))%8)|| (colonne==(8+((colonne_d-1)%8))%8)) )
                {
                    Grid[niveau_d][colonne_d].b_n=0;
                    Grid[niveau][colonne].b_n=couleur;
                    couleur =couleur * -1;
                    return 1;
                }
                if((niveau == 1)&&(colonne==colonne_d))
                {
                    Grid[niveau_d][colonne_d].b_n=0;
                    Grid[niveau][colonne].b_n=couleur;
                    couleur =couleur * -1;
                    return 1;
                }
                else
                {
                    return 0;
                }

            }
        }
    }

}

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
void destribuerColor(int i,int j)
{
    if(Grid[i][j].b_n==0)
        {Color(15,0);printf("#");}
    else if(Grid[i][j].b_n==1)
        {Color(9,9);printf(" ");}
    else if(Grid[i][j].b_n==-1)
        {Color(10,10);printf(" ");}
    Color(15,0);
}

void board()
{
system("cls");
printf("\n\n\n");
printf("\t     ");destribuerColor(0,0);printf("#######################");destribuerColor(0,1);printf("########################");destribuerColor(0,2);printf("\n");
printf("\t     ");printf("#                       #                        #\n");
printf("\t     ");printf("#                       #                        #\n");
printf("\t     ");printf("#                       #                        #\n");
printf("\t     ");printf("#       ");destribuerColor(1,0);printf("###############");destribuerColor(1,1);printf("################");destribuerColor(1,2);printf("       #\n");
printf("\t     ");printf("#       #               #                #       #\n");
printf("\t     ");printf("#       #               #                #       #\n");
printf("\t     ");printf("#       #               #                #       #\n");
printf("\t     ");printf("#       #       ");destribuerColor(2,0);printf("#######");destribuerColor(2,1);printf("########");destribuerColor(2,2);printf("       #       #\n");
printf("\t     ");printf("#       #       #                #       #       #\n");
printf("\t     ");printf("#       #       #                #       #       #\n");
printf("\t     ");printf("#       #       #                #       #       #\n");
printf("\t     ");printf("#       #       #                #       #       #\n");
printf("\t     ");destribuerColor(0,7);printf("#######");destribuerColor(1,7);printf("#######");destribuerColor(2,7);printf("                ");destribuerColor(2,3);printf("#######");destribuerColor(1,3);printf("#######");destribuerColor(0,3);printf("\n");
printf("\t     ");printf("#       #       #                #       #       #\n");
printf("\t     ");printf("#       #       #                #       #       #\n");
printf("\t     ");printf("#       #       #                #       #       #\n");
printf("\t     ");printf("#       #       #                #       #       #\n");
printf("\t     ");printf("#       #       ");destribuerColor(2,6);printf("#######");destribuerColor(2,5);printf("########");destribuerColor(2,4);printf("       #       #\n");
printf("\t     ");printf("#       #               #                #       #\n");
printf("\t     ");printf("#       #               #                #       #\n");
printf("\t     ");printf("#       #               #                #       #\n");
printf("\t     ");printf("#       ");destribuerColor(1,6);printf("###############");destribuerColor(1,5);printf("################");destribuerColor(1,4);printf("       #\n");
printf("\t     ");printf("#                       #                        #\n");
printf("\t     ");printf("#                       #                        #\n");
printf("\t     ");printf("#                       #                        #\n");
printf("\t     ");destribuerColor(0,6);printf("#######################");destribuerColor(0,5);printf("########################");destribuerColor(0,4);printf("\n\n\n");
printf("\n  - Nombre de Noeuds            ===>  %d\n",conteur);
}


//////////////////////////// AI ////////////////////////////////////////////////////

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
//typedef struct NOEUD* AddressTable;
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

    return 1000*(NombreNoirMoulin - NombreBlancMoulin) + 100*(NombreNoirPresMoulin - NombreBlancPresMoulin)+ 10*(Noeud->RBlanc - Noeud->RNoir);
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
        goto out;
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
                    goto out;
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
                    goto out;
                }
                b = min(b, v);
            }
        }

    }
    Noeud->minimax = v;
    out:
    {

    }
}


///////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    int AI;
    A:
    printf("1 . MinMax\n2 . Alphabeta\n\n\n");
    printf("votre choix >>>>  ");
    scanf("%d",&AI);
    if(AI!=1 && AI!=2)
    {
        system("cls");
        goto A;
    }
    while(poser!=0) // phase 1
    {
        board();
        printf("\n  - Nombre de Pions qui restent ===> %d",poser);
        printf("\n\n");
        Again:
        printf("\n>>>>>> Entrer le niveau (0 - 2) : ");
        scanf("%d",&niveau);
        if(niveau<0 || niveau>2)
            goto Again;
        Again1:
        printf("\n>>>>>> Entrer la colonne (0 - 7) : ");
        scanf("%d",&colonne);
        if(colonne<0 || colonne>7)
            goto Again1;
        if(Grid[niveau][colonne].b_n!=0)
            goto Again;
        Grid[niveau][colonne].b_n=couleur;
        //couleur*=-1;
        if(!moulin(niveau,colonne)&& possibleDeCapture(-1*couleur))
        {
            tryAgain:
            board();
            printf("\n\n");
            printf("choisir un pion de l\'autre joueur \n");
            A_:
            printf("\n>>>>>> Entrer le niveau (0 - 2) : ");
            scanf("%d",&niveau);
            if(niveau<0 || niveau>2)
                goto A_;
            B_:
            printf("\n>>>>>> Entrer la colonne (0 - 7) : ");
            scanf("%d",&colonne);
            if(colonne<0 || colonne>7)
                goto B_;
            if(Grid[niveau][colonne].b_n!=-1*couleur || !moulin(niveau,colonne))
                goto tryAgain;
            Grid[niveau][colonne].b_n=0;
            R1++; // le joueur a capturé

        }
        poser--;
        /// choix de la machine en utilisant l AI
        // niveau pour machine
        // colonne pour la machine

        struct NOEUD* Pointeur;
        Pointeur = (struct NOEUD*)malloc(sizeof(struct NOEUD));
        ///crier Pointeur
        ///copie
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
    Pointeur->RBlanc = R2;
    Pointeur->RNoir = R1;
    ///Fin initialisation
    conteur=0;
    genereArbre(Pointeur, profondeur);
    if(AI==1)
        minimaxFonction(Pointeur, profondeur);
    else
        alphaBita(Pointeur, profondeur, -999999, 999999);
    for(int i=0; i<24; i++)
    {
        if(Pointeur->tab[i] != NULL && Pointeur->tab[i]->minimax == Pointeur->minimax)
        {
            R1=Pointeur->tab[i]->RNoir;
            R2=Pointeur->tab[i]->RBlanc;
            for(int x=0; x<3; x++)
                for(int y=0; y<8; y++)
                     Grid[x][y].b_n = Pointeur->tab[i]->etat[x][y].b_n;
            poser--;
            break;
        }
    }
    }
    tryAgain1:
    board();
    printf("\n\n");
    if(R1==7 || R2==7 || joueurBloque(1)|| joueurBloque(-1))
    {
        //fin
        if(R1==7 || joueurBloque(1)) // le joueur a gagne
        {
            system("cls");
            printf("\n\n    ===>    le joueur a gagne ");
        }
        if(R2==7 || joueurBloque(-1)) // la machine a gagner
        {
            system("cls");
            printf("\n\n    ===>    la machine a gagne ");
        }
        printf("\n\n\n *********  appuyer sur un button pour quitter  *********\n\n\n\n ");
        getchar();
        exit(1);

    }
    printf("choisir un pion pour le deplacer \n");
    Again2:
    printf("\n>>>>>> Entrer le niveau (0 - 2) : ");
    scanf("%d",&niveau_d);
    if(niveau_d<0 || niveau_d>2)
        goto Again2;
    Again3:
    printf("\n>>>>>> Entrer la colonne (0 - 7) : ");
    scanf("%d",&colonne_d);
    if(colonne_d<0 || colonne_d>7)
        goto Again3;
    if(Grid[niveau_d][colonne_d].b_n!=couleur)
        goto tryAgain1;
    if(estBloque(niveau_d,colonne_d) && R1!=6 && R2!=6)
        goto tryAgain1;
    tryAgain2:
    board();
    printf("choisir ou voulez vous le deplacer \n");
    Again4:
    printf("\n>>>>>> Entrer le niveau (0 - 2) : ");
    scanf("%d",&niveau);
    if(niveau<0 || niveau>2)
        goto Again4;
    Again5:
    printf("\n>>>>>> Entrer la colonne (0 - 7) : ");
    scanf("%d",&colonne);
    if(colonne<0 || colonne>7)
        goto Again5;
    if(Grid[niveau][colonne].b_n!=0)
        goto tryAgain2;
    if(!deplacement())
        goto tryAgain2;
    couleur=-1;
    if(!moulin(niveau,colonne)&& possibleDeCapture(couleur*-1))
    {
        tryAgain5:
        board();
        printf("\n\n");
        printf("choisir un pion de l\'autre joueur \n");
        A1_:
        printf("\n>>>>>> Entrer le niveau (0 - 2) : ");
        scanf("%d",&niveau);
        if(niveau<0 || niveau>2)
            goto A1_;
        B1_:
        printf("\n>>>>>> Entrer la colonne (0 - 7) : ");
        scanf("%d",&colonne);
        if(colonne<0 || colonne>7)
            goto B1_;
        if(Grid[niveau][colonne].b_n!=-1*couleur || !moulin(niveau,colonne))
            goto tryAgain5;
        Grid[niveau][colonne].b_n=0;
        R1++; // a revoir

    }
    couleur=-1;
    struct NOEUD* Pointeur;
    Pointeur = (struct NOEUD*)malloc(sizeof(struct NOEUD));
    ///crier Pointeur
    ///copie
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
    Pointeur->RBlanc = R2;
    Pointeur->RNoir = R1;
    ///Fin initialisation
    conteur=0;
    genereArbre(Pointeur, profondeur);
    //minimaxFonction(Pointeur, 3);
    if(AI==1)
        minimaxFonction(Pointeur, profondeur);
    else
        alphaBita(Pointeur, profondeur, -999999, 999999);
    for(int i=0; i<24; i++)
    {
        if(Pointeur->tab[i] != NULL && Pointeur->tab[i]->minimax == Pointeur->minimax)
        {
            R1=Pointeur->tab[i]->RNoir;
            R2=Pointeur->tab[i]->RBlanc;
            for(int x=0; x<3; x++)
                 for(int y=0; y<8; y++)
                     Grid[x][y].b_n = Pointeur->tab[i]->etat[x][y].b_n;
           break;
        }
    }
    goto tryAgain1;
    printf("yassine");
    return 0;
}
