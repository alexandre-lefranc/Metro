/*----------------------- Fichier metro_main.c */

/* Bibliotheque standard. */
#include <stdlib.h> /* EXIT_SUCCESS */

#include "../inc/metro_data.h" /* load_data()..*/
#include "../inc/metro_interface.h" /* interface_init() .. */
#include "../inc/metro_dijkstra.h" /* matrice_init() */

/*	Fonction principale. */
int main(void) 
{
	env environment;
	listbox lb;

	/* Initialisation de la structure "environment". */
	init_env(&environment, &lb);
	
	/* Chargement des differentes donnees. */
	if (!load_data(&environment))
		return EXIT_FAILURE;
	
	/* Initialisation de la matrice. */
	matrice_init(&environment);

	/* Initialisation de l'interface graphique. */
  	interface_init();

	/* Dessine l'ensemble des stations et des lignes 
	   de transports. */
	draw_reseau(environment);

	/* Dessine l'interface. */ 
	draw_interface();

	/* Gestion de l'interface graphique. */
	traite_interface(environment);

	/* Fermeture de l'interface graphique. */
	interface_shutdown();
	
	/* Libere les espaces alloues. */
	data_shutdown(&environment);

	/* Fin de programme. */
	return EXIT_SUCCESS; 
}

/*------------------ Fin du fichier metro_main.c */
/* EOF */
