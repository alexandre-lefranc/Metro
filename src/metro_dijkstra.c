/*---------------------------- Fichier metro_dijkstra.c */

/* Bibliotheque standard. */
#include <stdlib.h>

/* Inclusion pour assurer la coherence. */
#include "../inc/metro_dijkstra.h"

#include "../inc/metro_interface.h"	/* is_station(), ... */
#include "../inc/metro_data.h" /* free_line() ... */
#include "../inc/pile.h" /* pop() ... */

/*--------------------------------------------------*
 * 		Fonction qui retourne le minimum.	 		*
 *--------------------------------------------------*/

unsigned minimum(float distance[], bool visite[], env environment)
{
  	unsigned i, j;
 	
	for (i = 0U; i < environment.n_station && visite[i]; i++);

	j = i; 
 
	for (i++; i < environment.n_station; i++)
		if ((!visite[i]) && (distance[i] < distance[j]))
			j = i;

	return j;
}

/*--------------------------------------------------*
 * 		Fonction qui implemente l'algorithme de		*
 *  Dijkstra.									    *
 *--------------------------------------------------*/

void dijkstra(unsigned depart, env environment, unsigned predecesseur[], 
			  bool visite[])
{
	unsigned ligne, colonne, i;
	float ** matrice = environment.matrice;
	float * distance = NULL;

	distance = (float * ) malloc(sizeof(float ) * environment.n_station);

	/* Initialisation de l'algorithme. */
	distance[depart] = 0.0f;

	for (colonne = 0U; colonne < environment.n_station; colonne++)
  	{
    	if (colonne != depart)
      		distance[colonne] = INFINI;

		visite[colonne] = FALSE;
		predecesseur[colonne] = environment.n_station;
	}
	
	/* Parcours de la matrice */
	for (i = 0U; i < environment.n_station; i++) 
	{
		/* On cherche le minimum. */
    	ligne = minimum(distance, visite, environment);
    	visite[ligne] = TRUE;

		for (colonne = 0U; colonne < environment.n_station; colonne++)
			if ((matrice[ligne][colonne] != INFINI) &&
		  		(ligne != colonne) && 
	  	  		(!visite[colonne]) && 
		  		(distance[ligne] + matrice[ligne][colonne] < distance[colonne])) 
			{
				/* Mise a jour du tableau des distances. */
        		distance[colonne] = distance[ligne] + matrice[ligne][colonne]; 
				/* On fait passser le chemin par colonne. */
        		predecesseur[colonne] = ligne; 
      		}
	}

	free(distance);
}

/*--------------------------------------------------*
 *	Fonction qui affiche le plus court chemin.		*
 *--------------------------------------------------*/

void afficher_court_chemin(unsigned depart, unsigned arrivee,
						 env environment) 
{
  	unsigned i;
	unsigned * predecesseur = NULL; 

	coord c;
	ligne voie = NULL;
	pile stack = NULL;
	bool * visite = NULL;
	station * reseau = environment.reseau;

	/* Creer le tableau des predecesseurs. */
	predecesseur = (unsigned *) malloc(sizeof(unsigned)* 
										environment.n_station);

	visite = (bool *) malloc(sizeof(bool)*environment.n_station);
	
	/* Appel a la fonction de l'algorithme de Dijkstra. */
  	dijkstra(depart, environment, predecesseur, visite);

	/* Initialise la listbox. */
	listbox_init(environment.lb);

  	for (i = arrivee; i != depart; i = predecesseur[i])
		/* Chemin impossible */
    	if (i == environment.n_station)
		{
			/* On affiche dans la listbox. */
			add_item_listbox("Itineraire impossible.", environment.lb);
			draw_items(X_LB, Y_LB, L_LB, H_LB, environment.lb);
			return;
		}
		/* Ajoute les elements dans la pile. */
		else
      		push(&stack, i);

  	push(&stack, depart); 
	
	/* Creer une ligne. */
	/* Retire les elements de la pile. */
  	while (!empty(stack))
		voie = add_queue(voie, "", reseau[pop(&stack)].nom, environment);

	c.x = voie->station->x;
	c.y = voie->station->y;

	/* Dessine le chemin. */
	draw_lines(voie, c, COLOR_ITINERAIRE);
	
	/* Affiche l'itineraire. */
	affiche_itineraire(voie, environment);

	/* Libere les espaces alloues. */
	free_line(voie);
	free(predecesseur);
	free(visite);
	clean(&stack);
}

/*--------------------------------------------------*
 * Fonction qui initialise une matrice d'adjacence	*
 * a l'infini.										*
 *--------------------------------------------------*/

void matrice_init(env * environment)
{
	unsigned ligne, colonne;
	float ** matrice = NULL;
	coord a;
	
	/* Alloue un tableau de pointeur. */
	environment->matrice = (float **) malloc(environment->n_station 
											* sizeof(float *));
		
	/* Alloue un tableau de float. */
	for (ligne = 0U; ligne < environment->n_station; ++ligne)
		environment->matrice[ligne]= (float *) malloc(environment->n_station 
														* sizeof(float));

	/* Affecte l'adresse de la matrice. */
	matrice = environment->matrice;
		
	/* Initialisation de la matrice. */
	for (ligne = 0U; ligne < environment->n_station; ++ligne)
		for (colonne = 0U; colonne < environment->n_station; ++colonne)
			if (ligne == colonne)
				matrice[ligne][colonne] = 0.0f;
			else
				matrice[ligne][colonne] = INFINI;

	/* Avec metro. */
	if (environment->avec_metro)
		load_matrice(environment->metro, a, environment, -1);
		
	/* Avec RER. */
	if (environment->avec_rer)
		load_matrice(environment->rer, a, environment, -1);
	
	/* Avec marche a pied. */
	if (environment->avec_pieton)
		load_matrice(environment->pieton, a, environment, -1);
}

/*--------------------------------------------------*
 *		Fonction qui charge la matrice.				*
 *--------------------------------------------------*/

void load_matrice(ligne voie, coord a, env * environment, int indiceligne)
{
	int colonne;
	float d;
	float ** matrice = environment->matrice;
	coord b;
	
	if (voie->nom_ligne[INDICE_LIGNE] == SEPARATEUR_DATA)
	{
		voie = voie->next;
		b.x = voie->station->x;
		b.y = voie->station->y;
 
 		colonne = is_station(b, *environment);
	}

	else
	{
		/* Affecte la coordonnee de la 2eme station. */
		b.x = voie->station->x;
		b.y = voie->station->y;

		/* Recherche l'indice de la station qui correspond
	 	   au coordonne b. */
		colonne = is_station(b, *environment);
	
		/* Calcul de la distance des 2 points A et B. */
		d = distance(a, b);

		/* Affecte la distance a notre matrice. */
		matrice[indiceligne][colonne] = d;
	}

	/* On recommence pour l'arret suivant. */
	if (voie->next != NULL)
		load_matrice(voie->next, b, environment, colonne);
}

/*----------------------------- Fin du fichier metro_dijkstra.c */
/* EOF */
