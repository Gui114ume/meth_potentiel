#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "potentiel.h"


//
u32 init_taches(tache_t* tab_tache,
                u32* nb_tache,
                FILE* input_file)
{

    char* the_string = malloc(100 * sizeof(char) + sizeof(char));
    char* token;
    int i_tache = 0;
    fgets(the_string, 100, input_file);
    int nb = atoi(the_string);
    *nb_tache = nb;
    while(fgets(the_string, 100, input_file))
    {
        token = strtok(the_string, " ");

        // remplir duree
        tab_tache[i_tache].duree = atoi(token);
        token = strtok(NULL, " ");

        //remplir nb antecedents
        tab_tache[i_tache].nb_antecedents = atoi(token);
        if(tab_tache[i_tache].nb_antecedents > 0)
            tab_tache[i_tache].antecedent = malloc(sizeof(int) * tab_tache[i_tache].nb_antecedents);
        token = strtok(NULL, " ");
        //remplir liste d'antecedents
        int i_antecedent = 0;

        while(token != NULL)
        {
            tab_tache[i_tache].antecedent[i_antecedent] = atoi(token);
            token = strtok(NULL, " ");
            i_antecedent++;

        }
    i_tache++;
    }

    return 1;
};

//
u32 find_tps_tot( tache_t* tab_tache,
                  u32 nb_taches)
{

    for(int i = 0 ; i < nb_taches; i++)
    {
        if(tab_tache[i].nb_antecedents == 0)
        {
            tab_tache[i].tps_tot = 0;
        }
    }

    for(int i = 0 ; i < nb_taches; i++)
    {
        u32 tmp = 0; //la valeur minimum du probleme
        for(int k = 0 ; (k < tab_tache[i].nb_antecedents)  ; k++)
        {
            tmp = MAX(tab_tache[tab_tache[i].antecedent[k]].duree + tab_tache[tab_tache[i].antecedent[k]].tps_tot, tmp);
        }
        tab_tache[i].tps_tot = tmp;
    }

};

//
u32 find_tps_tard(tache_t* tab_tache,
                  u32 nb_taches)
{
    // on s'impose ceci, il faut donc prendre en compte le noeud fin !! il doit etre ecrit dans le fichier !
    tab_tache[nb_taches - 1].tps_tard = tab_tache[nb_taches - 1].tps_tot;
    int tmp = tab_tache[nb_taches - 1].tps_tard; // la valeur maximum du probleme
    int j = 0;

    //pour toutes les taches du probleme
    for(int i = nb_taches - 2 ; i != 0 ; i--)
    {
        tmp = tab_tache[nb_taches - 1].tps_tard;

        //pour toutes les taches qui peuvent avoir la tache i comme antecedant
        for( j = nb_taches - 1; j > i ; j--)
        {
            //on cherche dans les antecedents
            for (int k = 0; k < tab_tache[j].nb_antecedents; k++) {
                //si i est antecedent de j, alors j est successeur de i
                if (tab_tache[j].antecedent[k] == i)
                    tmp = MIN(tmp, tab_tache[j].tps_tard);
            }
        }
        tmp -= tab_tache[i].duree;
        tab_tache[i].tps_tard = tmp;
        tmp = 0;
    }
    return 1;
};

//
u32 find_marge_totale(tache_t* tab_tache,
                      u32 nb_taches)
{
    for(int i = 0 ; i < nb_taches ; i++)
        tab_tache[i].marge_tot = tab_tache[i].tps_tard - tab_tache[i].tps_tot;
};

//
u32 find_marge_libre(tache_t* tab_tache,
                     u32 nb_taches)
{
    // a verifier, les cas particuliers
    tab_tache[nb_taches - 1].marge_libre = 0;
    int tmp = 0;
    int j = 0 ;
    //pour toutes les taches du probleme
    for(int i = nb_taches - 2 ; i != 0 ; i--)
    {
        tmp = tab_tache[nb_taches - 1].tps_tot; // la valeur max qui existe dans le probleme
        //pour toutes les taches qui peuvent avoir la tache i comme antecedant
        for( j = nb_taches - 1; j > i ; j--)
        {
            //on cherche dans les antecedents
            for (int k = 0; k < tab_tache[j].nb_antecedents; k++) {
                //si i est antecedent de j, alors j est successeur de i
                if (tab_tache[j].antecedent[k] == i)
                {
                    tmp = MIN(tmp, tab_tache[j].tps_tot);
                }
            }
        }
        tmp = tmp - tab_tache[i].duree - tab_tache[i].tps_tot;
        tab_tache[i].marge_libre = tmp;
    }

};

//
u32 write_taches(tache_t* tab_tache,
                 u32 nb_tache,
                 FILE* output_file)

{
    for(int i = 0 ; i < nb_tache ; i++)
        fprintf(output_file,"%d %d %d %d %d %d\n",i,tab_tache[i].duree,tab_tache[i].tps_tot,tab_tache[i].tps_tard,tab_tache[i].marge_tot,tab_tache[i].marge_libre);
    return 1;
};


int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("usage : %s [fichier_entree] [fichier_sortie]\n", argv[0]);
        fflush(stdout);
        exit(-1);
    }

    FILE *fptr_in = fopen(argv[1], "r");
    FILE *fptr_out = fopen(argv[2], "w");

    u32 nb_tache = 0;
    tache_t *tab_tache = NULL;

    //on recupere le nombre de tache
    //on alloue le tableau de taches
    char *tmp = malloc(100 * sizeof(char) + sizeof(char));
    fgets(tmp, 100, fptr_in);
    tab_tache = (tache_t *) malloc(sizeof(tache_t) * atoi(tmp));
    fseek(fptr_in, SEEK_SET, 0);

    init_taches(tab_tache,
                &nb_tache,
                fptr_in);

    find_tps_tot(tab_tache,
                 nb_tache);

    find_tps_tard(tab_tache,
                  nb_tache);


    find_marge_totale(tab_tache,
                      nb_tache);


    find_marge_libre(tab_tache,
                     nb_tache);

    write_taches(tab_tache,
                 nb_tache,
                 fptr_out);

    free(tab_tache);
    free(tmp);
    fclose(fptr_in);
    fclose(fptr_out);

    return EXIT_SUCCESS;
}