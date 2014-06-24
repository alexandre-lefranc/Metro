/*---------------------------- Fichier metro_data.c */

/* Bibliotheque standard. */
#include <stdlib.h> /* malloc(), free() ... */
#include <string.h> /* strcpy() ... */
#include <math.h> /* sqrt() */

/* Inclusion pour assurer la coherence. */
#include "../inc/metro_data.h" 

#include "../inc/metro_interface.h" /* get_station(), .. */

/*--------------------------------------------------*
 * 		Fonction qui initialise la structure 		*
 * 	"environment". 									*
 *--------------------------------------------------*/

void init_env(env * environment, listbox * lb)
{
	environment->reseau = NULL;

	environment->rer = NULL;
	environment->metro = NULL;
	environment->pieton = NULL;

	environment->matrice = NULL;

	environment->station_depart = ERR_STATION;
	environment->station_arrivee = ERR_STATION;

	environment->avec_rer = TRUE;
	environment->avec_metro = TRUE;
	environment->avec_pieton = TRUE;

	environment->lb = lb;
	
	/* Initialisation de la listbox. */
	listbox_init(environment->lb);
}

/*--------------------------------------------------*
 * Fonction qui retourne le nombre de stations 		*
 * contenu dans un fichier.							*
 *--------------------------------------------------*/

int get_nbr_station(FILE * fd)
{
	int i;
	char buffer[STATION_NAME_MAX];

	i = 0;

	/* Compte le nombre de lignes. */
	while (fgets(buffer, STATION_NAME_MAX, fd))
		i++;

	/* Renvoie le nombre de stations. */
	return i;
}

/*--------------------------------------------------*
 * Fonction qui calcule la distance entre deux 		*
 * points.											*
 *--------------------------------------------------*/

float distance(coord a, coord b)
{
	/* Formule de distance entre 2 points A et B. */
	return sqrt((b.x - a.x)*(b.x - a.x) + 
				(b.y - a.y)*(b.y - a.y));
}

/*--------------------------------------------------*
 * Fonction qui effectue un tri en ordre croissant  *
 * d'un tableau de stations en utilisant leur 		*
 * distance au point d'origine (0,0).				*
 *--------------------------------------------------*/

void tri_station(env * environment)
{
	int i, j;
	float d, d1;

	station * reseau = NULL;
	station tmp;
	coord origin, c, c1;

	/* Initialisation du point d'origne. */
	origin.x = 0;
	origin.y = 0;

	reseau = environment->reseau;
	
	/* Utilisation du tri a bulle. */
	for (i = 0; i < environment->n_station; ++i)
		for (j = 0; j < environment->n_station; ++j)
		{
			
			/* Calcul de la 1ere distance. */
			c.x = reseau[j].x;
			c.y = reseau[j].y;
			d = distance(origin, c);

			/* Calcul de la 2eme distance. */
			c1.x = reseau[j + 1].x;
			c1.y = reseau[j + 1].y;
			d1 = distance(origin, c1);
			
			/* Comparaison des 2 distances. */
			if (d > d1)
			{
				/* Swap des elements. */
				tmp = reseau[j];
				reseau[j] = reseau[j + 1];
				reseau[j + 1] = tmp;
			}
		}
}

/*--------------------------------------------------*
 * 	Fonction qui supprime le '\n' d'une chaine s.	*
 *--------------------------------------------------*/

void remove_endl(string s)
{
	string ps = NULL;

 	/*
     * Renvoie un pointeur sur la 1ere occurence 
     * du caractere '\n' dans la chaine s.
	 */
	ps = strchr(s, ENDL);
	
	/* Ajout du '\0'. */
	if (ps != NULL)
		*ps = '\0';
}

/*--------------------------------------------------*
 * 	Fonction qui ajoute une station en tete d'une	*
 *	ligne.											*
 *--------------------------------------------------*/

ligne add_head(ligne voie, string nom_ligne, 
				string nom_arret, env environment)
{
	ligne new = NULL;

	/* On cree une nouvelle allocation. */
	new = (ligne) malloc(sizeof(struct arret));

	/* Copie du nom de la ligne. */
	strcpy(new->nom_ligne, nom_ligne);

	/* On recherche l'adresse de la station "nom_arret". */
	new->station = get_station(nom_arret, environment);

	/* Assigne au champ "pointeur" du nouveau maillon, 
	 * la valeur du pointeur vers le maillon de tete. 
	 */
	new->next = voie;

	return new;
}

/*--------------------------------------------------*
 * 	Fonction qui ajoute une station a la fin d'une 	*
 *	ligne.											*
 *--------------------------------------------------*/

ligne add_queue(ligne voie, string nom_ligne, 
				string nom_arret, env environment)
{
	if (voie == NULL)
		return add_head(NULL, nom_ligne, nom_arret, environment);

	else
	{
		voie->next = add_queue(voie->next, nom_ligne, 
								nom_arret, environment);
		return voie;
	}
} 

/*--------------------------------------------------*
 * 	Fonction qui charge les differentes lignes de 	*
 *	transports contenues dans un fichier, renvoie 	*
 * 	TRUE si tout c'est bien deroule autrement FALSE.*
 *--------------------------------------------------*/

bool load_lines(env * environment)
{
	char tmp[LINE_NAME_MAX];
	char nom_ligne[LINE_MAX];

	FILE * fd = NULL; 

	ligne rer = NULL;
	ligne metro = NULL;
	ligne pieton = NULL;

	string nom_station = NULL;

	/* Test d'ouverture du fichier. */
	if (!(fd = fopen(FILENAME_LIGNES, "r")))
  	{
    	fprintf(stderr, "Impossible d'ouvrir le fichier %s \n",
				 FILENAME_LIGNES);
      	return FALSE;
  	}
	
	/* Parcours du fichier. */
	while (fgets(tmp, LINE_NAME_MAX, fd))
	{

		/* Nouvelle ligne. */
		/* Test du '\n' en cas d'erreur. */
	 	if ((tmp[INDICE_LIGNE] == SEPARATEUR_DATA) && 
			(tmp[INDICE_ERREUR] != ENDL))
		{
			remove_endl(tmp);
					
			/* RER */
			if ((tmp[INDICE_LIGNE2] >= INDICE_RER_DEBUT) &&
				(tmp[INDICE_LIGNE2] <= INDICE_RER_FIN))
				rer = add_queue(rer, tmp, "",  *environment);

			/* Pieton */
			else if (tmp[INDICE_LIGNE2] == INDICE_PIETON)
				pieton = add_queue(pieton, tmp, "", *environment);

			/* Metro. */
			else 
				metro = add_queue(metro, tmp, "", *environment);

		}

		else
		{

			/* Copie du nom de la ligne. */
			strcpy(nom_ligne, strtok(tmp, STR_SEPARATEUR_LIGNE));
		
			/* Affectation du nom de la station. */
			nom_station = strtok(NULL, STR_ENDL);
			
			/* RER */
			if ((tmp[INDICE_LIGNE] >= INDICE_RER_DEBUT) && 
				(tmp[INDICE_LIGNE] <= INDICE_RER_FIN))
				rer = add_queue(rer, nom_ligne, 
							   nom_station, *environment);

			/* Pieton. */
			else if (tmp[INDICE_LIGNE] == INDICE_PIETON)	
				pieton = add_queue(pieton, nom_ligne, 
								  nom_station, *environment);
			/* Metro. */
			else if (tmp[INDICE_ERREUR] != ENDL)
				metro = add_queue(metro, nom_ligne, nom_station, *environment);

		}
    }
	
	/* Fermeture du fichier. */
	fclose(fd);

	/* Affectation des adresses. */
	environment->rer = rer;
	environment->metro = metro;
	environment->pieton = pieton;

	return TRUE;
}

/*--------------------------------------------------*
 *	Fonction qui charge les stations contenues dans	*
 *	un fichier, renvoie TRUE si tout c'est bien 	*
 *	deroule autrement FALSE.						*
 *--------------------------------------------------*/

bool load_stations(env * environment)
{
	unsigned i;

	FILE * fd = NULL;
	station * reseau = NULL; 

	/* Test d'ouverture du fichier. */
	if (!(fd = fopen(FILENAME_STATIONS, "r")))
	{
		fprintf(stderr, "Impossible d'ouvrir le fichier %s \n",
				 FILENAME_STATIONS);
		return FALSE;
	}

	/* Affecte le nombre de stations. */	
	environment->n_station = get_nbr_station(fd);
	
	/* Alloue l'espace necessaire. */
	environment->reseau = (station *) malloc(environment->n_station * 
												sizeof(station));

	reseau = environment->reseau;

	/* Retour en debut de fichier. */
	rewind(fd);
	
	/* Parcours du fichier. */
	for (i = 0U; !feof(fd); ++i)
	{
		/* Affectation des coordonnees. */
		fscanf(fd, "%d ", &reseau[i].x);
				
		fscanf(fd, "%d ", &reseau[i].y);
		
		/* Copie du nom de la station. */
 		fgets(reseau[i].nom, STATION_NAME_MAX, fd);

		/* On supprime le \n. */
		remove_endl(reseau[i].nom);
	}
	
	/* Fermeture du fichier. */
	fclose(fd);

 	return TRUE;
}

/*--------------------------------------------------*
 * 	Fonction qui charge l'ensemble des donnees.		*
 *	Retourne TRUE si tout c'est bien passe sinon	* 
 *  FALSE.	 										*
 *--------------------------------------------------*/

bool load_data(env * environment)
{
	/* Charge les stations. */
	if (!load_stations(environment))
    	return FALSE;
    
	/* Tri le tableau de station. */
	tri_station(environment);
 	
	/* 
     * Charge les differentes lignes 
	 * de transports.              
	 */	 
	if (!load_lines(environment))
		return FALSE;

	return TRUE;
}

/*--------------------------------------------------*
 *	Fonction qui libere la memoire allouee d'une 	*
 *	ligne l.										*
 *--------------------------------------------------*/

void free_line(ligne l)
{
	if (l != NULL)
	{
		free_line(l->next);
		free(l);
	}
}

/*--------------------------------------------------*
 *	Fonction qui libere les differentes memoires 	*
 *	allouees.					 					*
 *--------------------------------------------------*/

void data_shutdown(env * environment)
{
	/* Libere l'espace alloue des lignes de transports. */
	free_line(environment->metro);	
	free_line(environment->rer);	
	free_line(environment->pieton);	

	/* Libere l'espace alloue de toutes les stations. */
	free(environment->reseau);

	/* Libere l'espace alloue de la matrice. */
	free(environment->matrice);
}

/*---------------------- Fin du fichier metro_data.c */
/* EOF */
