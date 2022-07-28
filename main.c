#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid_fonctions.h"

int main()
{
    srand(time(NULL));

    Matrice grille = init_matrice(25,100);

    const char elements[] = {'x', 'o', 'f'};   int nbr_elements = 3;

    //176, 178
    Curseur carre = { '_', '#', INVISIBLE, 0, 0};
    char sens[20], sens_char, tmp_char;
    int i = 0, exit = 0, last_stat  = VIDE ;

    fill_grid( &grille, elements, 3);
    del_lined(&grille);
    while(space_is_in(grille))
    {
        while(space_is_in(grille))
        {
            score = 0;
            show_grid(grille, carre);
            refresh_matrice(&grille, elements, 3);
            system("sleep .05");
            system("clear");
        }
        del_lined(&grille);
    }
    carre.etat = VIDE;

    while(!exit)
    {
        show_grid(grille, carre);

        if( space_is_in(grille) == 0 )
        {
            carre.etat = last_stat; //dernier etat, celui avant INVISIBLE
            if(carre.etat == VIDE)
            {
                printf("\n                         Direction : ");
                fgets(sens, 19, stdin);

                for(i=0; sens[i] != '\0'; i++)
                {
                    switch(sens[i])
                    {
                        case 'z' :
                            curseur_move(&carre, grille, HAUT);
                            break;
                        case 's' :
                            curseur_move(&carre, grille, BAS);
                            break;
                        case 'q' :
                            curseur_move(&carre, grille, GAUCHE);
                            break;
                        case 'd' :
                            curseur_move(&carre, grille, DROITE);
                            break;
                        case 'a' :
                             carre.etat = last_stat = PLEIN;
                            break;
                        case '!' :
                            exit = 1;
                            break;
                    }
                    system("clear");
                    show_grid(grille, carre);
                }
            }
            else if(carre.etat == PLEIN)
            {
                printf("\n                         Direction : ");
                sens_char = getchar();

                switch(sens_char)
                {
                    case 'z' : case '8':
                        permutation(carre, &grille, HAUT);
                        del_lined(&grille);

                        if(space_is_in(grille))
                            carre.etat = INVISIBLE;
                        else
                            permutation(carre, &grille, HAUT);

                        curseur_move(&carre, grille, HAUT);
                        last_stat = VIDE;
                        break;
                    case 's' : case '2':
                        permutation(carre, &grille, BAS);
                        del_lined(&grille);

                        if(space_is_in(grille))
                            carre.etat = INVISIBLE;
                        else
                            permutation(carre, &grille, BAS);

                        curseur_move(&carre, grille, BAS);
                        last_stat = VIDE;
                        break;
                    case 'q' : case '4':
                        permutation(carre, &grille, GAUCHE);
                        del_lined(&grille);

                        if(space_is_in(grille))
                            carre.etat = INVISIBLE;
                        else
                            permutation(carre, &grille, GAUCHE);

                        curseur_move(&carre, grille, GAUCHE);
                        last_stat = VIDE;
                        break;
                    case 'd' : case '6':
                        permutation(carre, &grille, DROITE);
                        del_lined(&grille);

                        if(space_is_in(grille))
                            carre.etat = INVISIBLE;
                        else
                            permutation(carre, &grille, DROITE);

                        curseur_move(&carre, grille, DROITE);
                        last_stat = VIDE;
                        break;
                    case 'a' :
                        carre.etat = last_stat = VIDE;
                        break;
                    case '!' :
                        exit = 1;
                        break;
                }
                vider_buffer();
            }

        }
        else  //Espace dans la grille
        {
            if(carre.etat != INVISIBLE)
                last_stat = carre.etat;
            carre.etat = INVISIBLE;
            while(space_is_in(grille))
            {
                system("clear");
                refresh_matrice(&grille, elements, 3);
                show_grid(grille, carre);
                del_lined(&grille);
                system("sleep 0.1");
            }
        }

        //del_lined(&grille);
        system("sleep 0.1");
        system("clear");
    }

    free_matrice(&grille);

    return 0;
}
