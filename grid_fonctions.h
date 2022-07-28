#ifndef GRID_FUNCTIONS_INCLUDED
#define GRID_FUNCTIONS_INCLUDED

#include <time.h>

//-----------------CURSEUR---------------------------//
//---------------------------------------------------//
enum Direction {GAUCHE, DROITE, HAUT, BAS};
enum Etat { INVISIBLE, VIDE , PLEIN };

typedef struct
{
    char empty_char, full_char;
    int etat;
    int x, y;
} Curseur;
//--------------------------------------------------------------//
//--------------------------------------------------------------//

typedef struct
{
    int n, p;
    char **tableau;
} Matrice, *pt_Matrice;

/*-------------VARIABLES----------------*/
static int score = 0;
/*--------------------------------------*/

void fill_grid(pt_Matrice matrice , char* contenants, int contenant_taille);
void show_grid(Matrice matrice, Curseur fleche);
short refresh_matrice(pt_Matrice matrice, char* contenants, int taille);

Matrice init_matrice(int pn, int pp);
void free_matrice(pt_Matrice matrice);
short del_lined(pt_Matrice matrice);
short space_is_in(Matrice matrice);

void permutation(Curseur fleche ,pt_Matrice matrice, enum Direction dir );

short is_in_matrice(int i, int j, Matrice mat);


//-----------------CURSEUR---------------------------//
//---------------------------------------------------//
void curseur_move(Curseur *fleche, Matrice limite, enum Direction dir);
//--------------------------------------------------------------//
//--------------------------------------------------------------//

void vider_buffer();

#endif // GRID_FUNCTIONS_INCLUDED
