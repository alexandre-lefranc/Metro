/*------------------------- Fichier metro_data.h */

/* Encapsulation contre les inclusions multiples. */
#ifndef METRO_DATA_H                   
#define METRO_DATA_H 

/* Bibliotheque standard. */
#include <stdio.h> /* FILE * */

#include "../inc/metro_main.h" /* bool, ... */

/* ===================================== Constantes */

/* Nom du fichier contenant les stations. */
#define FILENAME_STATIONS "stations.data"

/* Nom du fichier contenant les lignes de
	transports. */
#define FILENAME_LIGNES "lignes.data"

/* Indice ou se trouve le '\n' en
	cas d'erreur. */
#define INDICE_ERREUR 4

/* Chaine de caractere saut de ligne. */
#define STR_ENDL "\n" 

/* Choix arbitraire de la longueur de la chaine 
   du numero de ligne */
#define LINE_MAX 10

/* ============================ Fonctions publiques */

/*--------------------------------------------------*
 * 		Fonction qui initialise la structure 		*
 * 	"environment". 									*
 *--------------------------------------------------*/

void init_env(env * environment, listbox * lb);

/*--------------------------------------------------*
 * Fonction qui calcule la distance entre deux 		*
 * points.											*
 *--------------------------------------------------*/

float distance(coord a, coord b);

/*--------------------------------------------------*
 * Fonction qui effectue un tri en ordre croissant  *
 * d'un tableau de stations en utilisant leur 		*
 * distance au point d'origine (0,0).				*
 *--------------------------------------------------*/

void remove_endl(string s);

/*--------------------------------------------------*
 * 	Fonction qui ajoute une station en tete d'une	*
 *	ligne.											*
 *--------------------------------------------------*/

ligne add_head(ligne voie, string nom_ligne, 
				string nom_arret, env environment);

/*--------------------------------------------------*
 * 	Fonction qui ajoute une station a la fin d'une 	*
 *	ligne.											*
 *--------------------------------------------------*/

ligne add_queue(ligne voie, string nom_ligne, 
				string nom_arret, env environment);

/*--------------------------------------------------*
 * 	Fonction qui charge l'ensemble des donnees.		*
 *	Retourne TRUE si tout c'est bien passe sinon	* 
 *  FALSE.	 										*
 *--------------------------------------------------*/

bool load_data(env * environment);

/*--------------------------------------------------*
 *	Fonction qui libere la memoire allouee d'une 	*
 *	ligne l.										*
 *--------------------------------------------------*/

void free_line(ligne l);

/*--------------------------------------------------*
 *	Fonction qui libere les differentes memoires 	*
 *	allouees.					 					*
 *--------------------------------------------------*/

void data_shutdown(env * environment);

#endif /* #ifndef METRO_DATA_H */

/*--------------------- Fin du fichier metro_data.h */
/* EOF */
