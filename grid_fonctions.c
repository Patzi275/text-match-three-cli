#include "grid_fonctions.h"
#include <stdio.h>

//-------CURSEUR--------//
// x index la ligne et y la colonne
void curseur_move(Curseur *fleche, Matrice limite, enum Direction dir)
{
    switch(dir)
    {
        case GAUCHE :
            fleche->y = (fleche->y > 0) ? fleche->y-1 : fleche->y;
            break;
        case DROITE :
            fleche->y = (fleche->y < limite.p - 1) ? fleche->y+1 : fleche->y;
            break;
        case HAUT :
            fleche->x = (fleche->x > 0) ? fleche->x-1 : fleche->x;
            break;
        case BAS :
            fleche->x = (fleche->x < limite.n - 1) ? fleche->x+1 : fleche->x;
            break;
    }
}
//----------------------//


Matrice init_matrice(int pn, int pp)
{
    int j;
    Matrice matrice ;
    matrice.n = pn;
    matrice.p = pp;
    matrice.tableau = (char**)malloc(sizeof(char*)*pn);
    for(j = 0; j < pn; j++)
    {
        matrice.tableau[j] = (char*)malloc(sizeof(char)*pp);
    }
    return matrice;
}

void free_matrice(pt_Matrice matrice)
{
    int j;

    for(j = 0; j < matrice->n; j++)
    {
        free(matrice->tableau[j]);
    }
    free(matrice->tableau);
}

void fill_grid(pt_Matrice matrice ,char* contenants, int contenant_taille)
{
    int i, j;

    for(i=0; i<matrice->n; i++)
    {
        for(j=0; j<matrice->p; j++)
        {
            matrice->tableau[i][j] = contenants[rand()%contenant_taille];
        }
    }
}

short refresh_matrice(pt_Matrice matrice, char* contenants, int taille)
{
    int i, j;
    short modifier = 0;
    char tmp_char;

    for(i = matrice->n - 1; i>=0; i--)
    {
        for(j=0; j<matrice->p; j++)
        {
            if(matrice->tableau[i][j] == ' ')
            {
                if(i == 0)
                    matrice->tableau[i][j] = contenants[rand()%taille];
                else
                {
                    matrice->tableau[i][j] = matrice->tableau[i-1][j];
                    matrice->tableau[i-1][j] = ' ';
                }
                modifier = 1;
            }
        }
    }
    return modifier;
}

short space_is_in(Matrice matrice)
{
    short retour = 0;
    int i, j;

    for(i=0; i<matrice.n; i++)
    {
        for(j=0; j<matrice.p; j++)
        {
            if(matrice.tableau[i][j] == ' ')
            {
                retour = 1;
            }
        }
    }
    return retour ;
}

void show_grid(Matrice matrice, Curseur fleche)
{
    int i, j;

    printf("+-------------------------+---------------------------+\n");
    printf("|-------DEPLACEMENT-------|-----------AUTRES----------|\n");
    printf("|         CHAR  NUM-PAD(x)|           CHAR  NUM-PAD(x)|\n");
    printf("| haut  :   z     8       | selection :  a     5      |\n");
    printf("| bas   :   s     2       | quitter   :  !     0      |\n");
    printf("| gauche:   q     4       |                           |\n");
    printf("| droite:   d     6       |                           |\n");
    printf("+-------------------------+---------------------------+\n");



    printf("\n");
    for(i=0; i<matrice.n; i++)
    {
        printf("  | ");
        for(j=0; j<matrice.p; j++)
        {
            if(fleche.x == i && fleche.y == j && fleche.etat != INVISIBLE)
            {
                if(fleche.etat == PLEIN)
                    printf("%c",fleche.full_char);
                else
                    printf("%c",fleche.empty_char);
            }
            else
                printf("%c",matrice.tableau[i][j]);
        }
        if(i != 3)
            printf(" |\n");
        else
            printf(" |         SCORE : %d points\n", score);
    }

    printf("  |-");
    for(j=0; j<matrice.p; j++)
    {
        printf("-");
    }
    printf("-|\n");
}

short is_in_matrice(int i, int j, Matrice mat)
{
    if(i<0 || j<0)
        return 0;
    else if( i >= mat.n || j >= mat.p)
        return 0;
    else
        return 1;
}

short del_lined(pt_Matrice matrice)
{
    int i, j, k, condition, nbr;
    char tmp_char;
    short reponse = 0;

    if(space_is_in(*matrice))
        return 0;

    for(i=0; i<matrice->n; i++)
    {
        for(j=0; j<matrice->p; j++)
        {
            if(matrice->tableau[i][j] != ' ')
            {
                tmp_char = matrice->tableau[i][j];

                nbr = 1;
                do
                {
                    if(is_in_matrice(i, j+nbr, *matrice) && matrice->tableau[i][j+nbr] == tmp_char)
                        condition = 1;
                    else
                        condition = 0;

                    if(condition)
                        nbr++;
                    else if(nbr >= 3)
                    {
                        for(k=0; k<nbr; k++)
                            matrice->tableau[i][j+k] = ' ';
                        reponse = 1;
                        score += nbr;
                    }
                }while(condition);

                nbr = 1;
                do
                {
                    if(is_in_matrice(i+nbr, j, *matrice) && matrice->tableau[i+nbr][j] == tmp_char)
                        condition = 1;
                    else
                        condition = 0;

                    if(condition)
                        nbr++;
                    else if(nbr >= 3)
                    {
                        for(k=0; k<nbr; k++)
                            matrice->tableau[i+k][j] = ' ';
                        reponse = 1;
                        score += nbr;
                    }
                }while(condition);
            }
        }
    }
    return reponse;
}

void permutation(Curseur fleche ,pt_Matrice matrice, enum Direction dir )
{
    char temp;
    switch(dir)
    {
        case HAUT :
            if(is_in_matrice(fleche.x-1, fleche.y, *matrice))
            {
                temp = matrice->tableau[fleche.x-1][fleche.y];
                matrice->tableau[fleche.x-1][fleche.y] = matrice->tableau[fleche.x][fleche.y];
                matrice->tableau[fleche.x][fleche.y] = temp;
            }
            break;
        case BAS :
            if(is_in_matrice(fleche.x+1, fleche.y, *matrice))
            {
                temp = matrice->tableau[fleche.x+1][fleche.y];
                matrice->tableau[fleche.x+1][fleche.y] = matrice->tableau[fleche.x][fleche.y];
                matrice->tableau[fleche.x][fleche.y] = temp;
            }
            break;
        case GAUCHE :
            if(is_in_matrice(fleche.x, fleche.y-1, *matrice))
            {
                temp = matrice->tableau[fleche.x][fleche.y-1];
                matrice->tableau[fleche.x][fleche.y-1] = matrice->tableau[fleche.x][fleche.y];
                matrice->tableau[fleche.x][fleche.y] = temp;
            }
            break;
        case DROITE :
            if(is_in_matrice(fleche.x, fleche.y+1, *matrice))
            {
                temp = matrice->tableau[fleche.x][fleche.y+1];
                matrice->tableau[fleche.x][fleche.y+1] = matrice->tableau[fleche.x][fleche.y];
                matrice->tableau[fleche.x][fleche.y] = temp;
            }
            break;
    }
}

void vider_buffer()
{
	char c = 0;
 	while (c != '\n' && c != EOF)
 	{
 		c = getchar();
 	}
}


