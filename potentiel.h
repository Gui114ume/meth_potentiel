#ifndef POTENTIEL_H
#define POTENTIEL_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef unsigned int u32;

typedef struct tache_s
{
    u32 duree;
    u32 nb_antecedents;
    u32* antecedent;

    u32 tps_tot;
    u32 tps_tard;
    u32 marge_tot;
    u32 marge_libre;
} tache_t;

u32 init_taches(tache_t* tab_tache,
                u32* nb_tache,
                FILE* input_file);

u32 find_tps_tot( tache_t* tab_tache,
                  u32 nb_taches);

u32 find_tps_tard(tache_t* tab_tache,
                  u32 nb_taches);

u32 find_marge_totale(tache_t* tab_tache,
                      u32 nb_taches);

u32 find_marge_libre(tache_t* tab_tache,
                     u32 nb_taches);

u32 write_taches(tache_t* tab_tache,
                 u32 nb_tache,
                 FILE* output_file);

#endif