/*------------------------- Fichier metro_dijkstra.h */

/* Encapsulation contre les inclusions multiples. */
#ifndef METRO_DIJKSTRA_H                   
#define METRO_DIJKSTRA_H

#include "../inc/metro_main.h" /* coord */

/* ====================================== Constantes */

/* Choix arbitraire de l'infini. */
#define INFINI 999999.0f

/* ============================ Fonctions publiques */

/*--------------------------------------------------*
 *	Fonction qui affiche le plus court chemin.		*
 *--------------------------------------------------*/

void afficher_court_chemin(unsigned depart, 
						   unsigned arrivee,
						   env environment);

/*--------------------------------------------------*
 * Fonction qui initialise une matrice d'adjacence	*
 * a l'infini.										*
 *--------------------------------------------------*/

void matrice_init(env * environment);

/*--------------------------------------------------*
 *		Fonction qui charge la matrice.				*
 *--------------------------------------------------*/

void load_matrice(ligne voie, coord a, env * environment, 
                  int indiceligne);

#endif  /* #ifndef METRO_DIJKSTRA_H */
/*----------------- Fin du fichier metro_dijkstra.h */
/* EOF */
