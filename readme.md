Implémentation de la méthode des potentiels
-------------------------------------------

Structure de donnée utilisé: tache_t

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

Nous utilisons en pratique un tableau de "tache_t" ( tache_t tab[nb_tache] ).
Nous avons ainsi une représentation sous forme de tableau comme si l'on écrivait le problème à la main, sur papier.

Les seuls points difficiles à comprendre au premier abord dans le programme, sont la recherche des successeurs d'une tache. Nous allons expliquer brièvements.
Nous recherchons dans toutes les taches pouvant avoir la tache t comme antécédent, si t est bien un antécédent. Pour cela le fichier d'entrée doit être écrit correctement, c'est à dire que les antécédents de la tache stocké avec l'indice "i", sont forcéments dans une case d'indice inférieur à "i".

Antécédents(tache[i]) sont inclus dans { tache[0], tache[1], ..., tache[i-1] }.

Autrement, la résolution d'un problème d'ordonnancement se fait comme suit:

	   -> init_tache
	   
	   -> find_tps_au_plus_tot  
	   -> find_tps_au_plus_tard
	   -> find_marge_totale
	   -> find_marge_libre

	   -> writes_resultats


Le programme se compile avec make.

Le programme s'utilise comme suit:
   ./meth_pot [fichier_entree] [fichier_sortie]   