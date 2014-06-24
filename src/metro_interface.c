/*----------------------- Fichier metro_interface.c */

/* Bibliotheque standard */
#include <string.h> /* strcmp(), ... */
#include <stdio.h> /* FILE* */

/* Inclusion pour assurer la coherence */
#include "../inc/metro_interface.h"	

#include "../inc/graph.h" /* InitialiserGraphique() ... */
#include "../inc/metro_dijkstra.h" /* afficher_court_chemin() ... */

/*--------------------------------------------------*
 * Fonction qui dessine un drapeau sur une station.	* 
 * Si etat vaut FALSE alors on affiche le drapeau 	*
 * de depart, sinon on dessine le drapeau d'arrivee.*
 *--------------------------------------------------*/

void draw_flag(int x, int y, bool etat)
{
	if (!etat)
		ChargerImage(DRAP, x, y, OX_DRAP, OY_DRAP, 
                     L_DRAP, H_DRAP);

	else
		ChargerImage(DRAP, x, y, OX_DRAP + L_DRAP, 
                     OY_DRAP, L_DRAP, H_DRAP);		
}

/*--------------------------------------------------*
 * 		Fonction qui dessine la scrollbar.			*
 *--------------------------------------------------*/

void draw_scrollbar(int x, int y, int l, int h)
{
	/* Dessine le bouton "montee" de la scrollbar.  */
	CopierZone(1, 0, OX_SCRLB_UP, OY_SCRLB_UP, 
			   L_SCRLB, H_SCRLB, x, y + 1);	

	/* Dessine le bouton "descente" de la scrollbar.  */
	CopierZone(1, 0, OX_SCRLB_DOWN, OY_SCRLB_DOWN, 
			   L_SCRLB, H_SCRLB, x, y + H_LB - H_SCRLB);	
}

/*--------------------------------------------------*
 * 		Fonction qui dessine une listbox.			*
 *--------------------------------------------------*/

void draw_listbox(int x, int y, int l, int h)
{
	DessinerRectangle(x, y, l, h);
	/* Dessine la scrollbar. */
	draw_scrollbar(x + l - L_SCRLB, y, l, h);
}

/*--------------------------------------------------*
 * 	Fonction qui dessine les items de la listbox.	*
 *--------------------------------------------------*/

void draw_items(int x, int y, int l, int h, listbox * lb)
{
	int textpos = 0;
	int i;
	
	/* Efface l'interieur de la listbox sans les bordures. */
	RemplirRectangleC(x + 1, y + 1, l - L_SCRLB - 1, h - 1, 
					  CouleurParNom(COUL_ARR_PLAN));

	/* Parcours du tableau d'item. */
	for (i = lb->current_indice; ((i >= 0) && (textpos < h - H_SCRLB) 
		 && (i < lb->data_indice)); ++i)
	{
		/* Position de l'item. */
	 	textpos += TailleSupPolice(SIZE_TXT) + TailleInfPolice(SIZE_TXT);

		EcrireTexte(x + ESPACE_TXT, y + textpos, lb->tablistbox[i], SIZE_TXT);
	} 	
	
	/* Nombres d'items dessines. */
	lb->n_item = i - lb->current_indice;
}

/*--------------------------------------------------*
 * 		 	Fonction qui ajoute un item.			*
 *--------------------------------------------------*/

void add_item_listbox(string text, listbox * lb)
{
	/* Ajout de l'item dans le tableau. */
	if (lb->data_indice < ITEM_MAX)
		strcpy(&lb->tablistbox[lb->data_indice++][0], text);
}

/*--------------------------------------------------*
 * 			Fonction qui gere la listbox.			*
 *--------------------------------------------------*/

void traite_listbox(coord c, listbox * lb)
{
	/* Bouton "montee" de la scrollbar. */
	if (( c.x >= X_LB + L_LB - L_SCRLB) && 
		( c.x <= X_LB + L_LB ) &&
		( c.y >= Y_LB) &&
		( c.y <= Y_LB + H_SCRLB) &&
		(lb->current_indice))
	{
		lb->current_indice--;
		draw_items(X_LB, Y_LB, L_LB, H_LB, lb);
	}

	/* Bouton "descente" de la scrollbar. */
	else if (( c.x >= X_LB + L_LB - L_SCRLB) &&
			( c.x <= X_LB + L_LB ) &&
			( c.y >= Y_LB + H_LB - H_SCRLB) &&
			( c.y <= Y_LB + H_LB) &&
			(lb->current_indice + lb->n_item != lb->data_indice))
	{
		lb->current_indice++;
		draw_items(X_LB, Y_LB, L_LB, H_LB, lb);					
	}
}

/*--------------------------------------------------*
 * 	Fonction qui enregistre un itineraire dans un 	*
 *	fichier.										*
 *--------------------------------------------------*/

void enregistrer_itineraire(listbox lb)
{
	int i;
	FILE * fichier = NULL;

	/* Test d'ouverture de fichier. */
	if (!(fichier = fopen(FILENAME_SAVE, "w")))
	{
		printf("Impossible d'ouvrir le fichier %s\n",
				FILENAME_SAVE);
		return;
	}
	/* Parcours du tableau d'item de la listbox. */
	for (i = 0U; i < lb.data_indice && i < ITEM_MAX; ++i)
	{
		/* Ecriture de l'item dans le fichier. */
		fputs(lb.tablistbox[i], fichier);

		/* Ecriture du caractere saut de ligne dans le fichier. */
		fputc(ENDL, fichier);
	}

	/* Fermeture du fichier. */
	fclose(fichier);	
}

/*--------------------------------------------------*
 *		Fonction qui initialise une listbox.		*
 *--------------------------------------------------*/

void listbox_init(listbox * lb)
{
	/* Nombre d'item dans la listbox. */
	lb->data_indice = 0;
	/* Position de la listbox actuelle. */
	lb->current_indice = 0;
	/* Nombre d'item dessiner. */
	lb->n_item = 0;
}

/*--------------------------------------------------*
 *	Fonction qui recherche une station et retourne 	*
 *	son adresse.									*
 *--------------------------------------------------*/

station * get_station(string station_name, 
						env environment)
{
	unsigned i; 	
	station * reseau = environment.reseau;

	/* Parcours du tableau. */
	for (i = 0U; i < environment.n_station; ++i)
		if (!strcmp(reseau[i].nom, station_name))
			/* Retourne l'adresse de la station. */
			return &reseau[i]; 
	
	return NULL;
}
/*--------------------------------------------------*
 *          Cree une interface graphique. 			*
 *--------------------------------------------------*/

void interface_init(void)
{
 	InitialiserGraphique();

	/* Creer une fenetre centree. */
 	CreerFenetre((Maxx() - FEN_L)/2, 
				(Maxy() - FEN_L)/2,
				 FEN_L, FEN_H);

	/* Arriere plan en blanc. */
	EffacerEcran(CouleurParNom(COUL_ARR_PLAN));
}

/*--------------------------------------------------*
 * 			Ferme l'interface graphique.			*
 *--------------------------------------------------*/

void interface_shutdown(void)
{
	FermerGraphique();
}

/*--------------------------------------------------*
 * 			Dessine l'ensemble des stations.		*
 *--------------------------------------------------*/

void draw_stations(env environment)
{
	unsigned i;
	station * reseau = environment.reseau;

	/* Parcours du tableau. */
	for (i = 0U; i < environment.n_station; ++i) 
		DessinerArc(reseau[i].x/2, reseau[i].y/2, 
					TAILLE_STATION, TAILLE_STATION, ANGLE1, ANGLE2);
}

/*--------------------------------------------------*
 * 	Fonction qui cherche si la coordonnee transmit 	*
 *	par argument existe, la fonction retourne son 	*
 *	indice ou ERR_STATION (-1) si elle n'existe pas.*	
 *--------------------------------------------------*/

int is_station(coord c, env environment)
{
	int i;
	station * reseau = environment.reseau;

	/* Parcours du tableau. */
	for (i = 0; i < environment.n_station; ++i)
		if ((c.x >= reseau[i].x) &&
			(c.y >= reseau[i].y) &&
			(c.x < TAILLE_STATION*2 + reseau[i].x) &&
			(c.y < TAILLE_STATION*2 + reseau[i].y))
				return i;
	
	return ERR_STATION;
} 

/*--------------------------------------------------*
 *			Fonction qui gere la checkbox.			*
 *--------------------------------------------------*/

void traite_checkbox(coord c, env * environment)
{
	/* Test de la 1ere checkbox metro. */
	if ((c.x >= X_CB) &&
		(c.y >= Y_CB) &&
		(c.x <= X_CB + SIZE_CB) &&
		(c.y <= Y_CB + SIZE_CB))
	{
		environment->avec_metro = !environment->avec_metro;

		/* Si la checkbox est OK. */
		if (environment->avec_metro)
			ChargerImage(IMG_NAME, X_CB, Y_CB, 
						 OX_CB_OK, OY_CB_OK, SIZE_CB, SIZE_CB);

		else
			ChargerImage(IMG_NAME, X_CB, Y_CB, 
						 OX_CB, OY_CB, SIZE_CB, SIZE_CB);
		
		CopierZone(0, 1, X_CB, Y_CB, SIZE_CB, SIZE_CB, 
				   X_CB, Y_CB);
		CopierZone(0, 2, X_CB, Y_CB, SIZE_CB, SIZE_CB, 
				   X_CB, Y_CB);

		/* On reinitialise la matrice */
		matrice_init(environment);
	}
	/* Test de la 2eme checkbox RER. */
	else if ((c.x >= X_CB) &&
			 (c.y >= ESPACE_CB + Y_CB) &&
			 (c.x <= X_CB + SIZE_CB) &&
			 (c.y <= ESPACE_CB + Y_CB + SIZE_CB))
	{
		environment->avec_rer = !environment->avec_rer;

		/* Si la checkbox est OK. */
		if (environment->avec_rer)
			ChargerImage(IMG_NAME, X_CB, Y_CB + ESPACE_CB, 
						 OX_CB_OK, OY_CB_OK, SIZE_CB, SIZE_CB);

		else
			ChargerImage(IMG_NAME, X_CB, Y_CB + ESPACE_CB, 
						 OX_CB, OY_CB, SIZE_CB, SIZE_CB);

		CopierZone(0, 1, X_CB, Y_CB + ESPACE_CB, SIZE_CB, 
					SIZE_CB, X_CB, Y_CB + ESPACE_CB);

		CopierZone(0, 2, X_CB, Y_CB + ESPACE_CB,SIZE_CB, 
					SIZE_CB, X_CB, Y_CB + ESPACE_CB);
	
		/* On reinitialise la matrice */	
		matrice_init(environment);
	}
	/* Test de la 3eme checkbox marche a pied. */
	else if ((c.x >= X_CB) &&
			 (c.y >= 2*ESPACE_CB + Y_CB) &&
			 (c.x <= X_CB + SIZE_CB) &&
			 (c.y <= 2*ESPACE_CB + Y_CB + SIZE_CB))
	{
		environment->avec_pieton = !environment->avec_pieton;

		/* Si la checkbox est OK. */
		if (environment->avec_pieton)
			ChargerImage(IMG_NAME, X_CB, Y_CB + 2*ESPACE_CB, 
						 OX_CB_OK, OY_CB_OK, SIZE_CB, SIZE_CB);

		else
			ChargerImage(IMG_NAME, X_CB, Y_CB + 2*ESPACE_CB, 
						 OX_CB, OY_CB, SIZE_CB, SIZE_CB);


		CopierZone(0, 1, X_CB, Y_CB, SIZE_CB, SIZE_CB, 
				   X_CB, Y_CB);

		CopierZone(0, 2, X_CB, Y_CB + 2*ESPACE_CB, SIZE_CB, 
				   SIZE_CB, X_CB, Y_CB + 2*ESPACE_CB);

		/* On reinitialise la matrice */
		matrice_init(environment);
	}
}

/*--------------------------------------------------*
 * Fonction qui retourne le numero de ligne desiree.*
 *--------------------------------------------------*/

string get_line_name(string station, env environment, 
						string station_next)
{
	string nom_ligne = NULL;

	/* Recherche dans la ligne metro. */
	if(environment.avec_metro)
		if ((nom_ligne = find_line_name(environment.metro, station, station_next)))
			return nom_ligne;

	/* Recherche dans la ligne rer. */
	if(environment.avec_rer)
		if ((nom_ligne = find_line_name(environment.rer, station, station_next)))
			return nom_ligne;

	/* Recherche dans la ligne pieton. */
	if (environment.avec_pieton)
		if ((nom_ligne = find_line_name(environment.pieton, station, station_next)))
			return nom_ligne;
		
	return NULL;
}

/*--------------------------------------------------*
 * 		Fonction qui cherche une ligne desiree.		*
 *--------------------------------------------------*/

string find_line_name(ligne voie, string station, string station_next)
{	
	string nom_ligne = NULL;	
	
	while (voie)
	{

		if (voie->nom_ligne[INDICE_LIGNE] == SEPARATEUR_DATA)
			nom_ligne = voie->nom_ligne + INDICE_LIGNE2 - 1;

		/* Si la station correspond a "station". */
		if ((voie->station) && (!strcmp(voie->station->nom, station)))
		{
			voie = voie->next;

			if (voie->nom_ligne[INDICE_LIGNE] == SEPARATEUR_DATA)
				nom_ligne = voie->nom_ligne + INDICE_LIGNE2 - 1;
		
			/* Si la station suivante correspond a "station_next"
				alors c'est la bonne ligne. */
			if ((voie->station) && (!strcmp(voie->station->nom, station_next)))
				return nom_ligne;

			/* Test de comparaison special pour les lignes de marche a pied. */
			if ((voie->station) && (!strcmp(voie->station->nom, station)))
				return nom_ligne;
		}

		/* Arret suivant. */
		voie = voie->next;
	}

	return NULL;
}

/*--------------------------------------------------*
 * 		Fonction qui affiche un itineraire.	  		*
 *--------------------------------------------------*/

void affiche_itineraire(ligne itineraire, env environment)
{
	char derniereligne[LINE_NAME_MAX] = "";
	char tmp[LINE_NAME_MAX];
	char numligne[LINE_NAME_MAX];

	string station_name = NULL;
	string nomligne = NULL;
	
	/* Parcours de la liste chainee. */
	while (itineraire) 
	{
		station_name = itineraire->station->nom;
		/* Arret suivant. */
		itineraire = itineraire->next;

		if (itineraire)
		{	
			/* Recherche de la bonne ligne. */
			nomligne = get_line_name(station_name, 
								  environment, 
								  itineraire->station->nom);

			strcpy(numligne, nomligne);

			strtok(numligne, ":");
			strcpy(tmp, "");

		}
		
		/* Si la ligne est differente de l'ancienne. */
		if (strcmp(numligne, derniereligne))
		{
			if (strcmp(derniereligne, ""))
			{	
				add_item_listbox(station_name, environment.lb);
				add_item_listbox("Changement", environment.lb);
			}
			/* RER. */
			if ((numligne[INDICE_LIGNE + 1] >= INDICE_RER_DEBUT) && 
				(numligne[INDICE_LIGNE + 1] <= INDICE_RER_FIN))
			{
				/* Concatene les 2 chaines. */
				strcat(tmp, "RER : ligne");
				strcat(tmp, nomligne);		
			
				add_item_listbox(tmp, environment.lb);
			}
			/* Marche a pied. */
			else if (numligne[INDICE_LIGNE + 1] == INDICE_PIETON)	
			{
				/* Concatene les 2 chaines. */
				strcat(tmp, "Marche: ligne");
				strcat(tmp, nomligne);		
			
				add_item_listbox(tmp, environment.lb);	
			}
			/* Metro. */
			else
			{	
				/* Concatene les 2 chaines. */
				strcat(tmp, "Metro : ligne");
				strcat(tmp, nomligne);

				add_item_listbox(tmp, environment.lb);
			}
		}

		/* Ajoute le nom de la station dans la listbox. */
		add_item_listbox(station_name, environment.lb);
		
		strcpy(derniereligne, numligne);

	}
	
	/* Dessine les items de la listbox. */
	draw_items(X_LB, Y_LB, L_LB, H_LB, environment.lb);
}

/*--------------------------------------------------*
 *		Fonction qui gere l'interface graphique.	*
 *--------------------------------------------------*/

void traite_interface(env environment)
{

	station * reseau = NULL;
	int station;
	bool enregistrer = FALSE;
	coord c;
	
	reseau = environment.reseau;

	do 
	{
		SourisPosition();
		
		c.x = _X*2;
		c.y = _Y*2;
		
		/* Test si la position de la souris se trouve 
			sur une station */
		station = is_station(c, environment);
	
		c.x = _X;
		c.y = _Y;

		/* Si on est sur une station. */		
		if (station != ERR_STATION)
		{

			if (SourisCliquee())
			{
				/* Depart */
				if (environment.station_depart == ERR_STATION)
				{
					environment.station_depart = station;

					CopierZone(2, 0, 0, 0, FEN_L, FEN_H, 0, 0);

					enregistrer = FALSE;

					/* Dessine le drapeau de depart. */
					draw_flag(reseau[station].x/2 + 2, 
							  reseau[station].y/2 - H_DRAP + TAILLE_STATION/2,
                              FALSE);
					
					/* On affiche le nom de la station de depart. */
					EcrireTexte(X_DEP + L_DEP + X_ESPACE_DEP, 
								Y_DEP + Y_ESPACE_DEP, 
								reseau[station].nom, TAILLE_DEP);
				}
				/* Arrivee */
				else if (environment.station_depart != station)
				{
					environment.station_arrivee = station;

					CopierZone(1, 0, 0, 0, FEN_L, FEN_H, 0, 0);

					/* Dessine le drapeau d'arrivee. */					
					draw_flag(reseau[station].x/2 + 2,  
                              reseau[station].y/2 - H_DRAP + TAILLE_STATION/2, 
                              TRUE);	

					/* On affiche le nom de la station d'arrivee. */
					EcrireTexte(X_ARR + L_ARR + X_ESPACE_ARR,
								Y_ARR + Y_ESPACE_ARR, 
								reseau[station].nom, TAILLE_ARR);
				
					/* On affiche le plus court chemin. */
					afficher_court_chemin(environment.station_depart, 
										environment.station_arrivee, 
										environment);
					enregistrer = TRUE;

					/* Dessine l'image "Enregistrer dans un fichier". */
					ChargerImage(IMG_NAME, X_ENR, Y_ENR, 
                                 OX_ENR, OY_ENR, L_ENR, H_ENR);

					environment.station_depart = ERR_STATION;
				}

				/* On dessine la station selectionnee. */
				RemplirArcC(reseau[station].x/2, reseau[station].y/2, 
							TAILLE_STATION, TAILLE_STATION,
							ANGLE1, ANGLE2,
							CouleurParNom(COUL_STA_SELECT));

				CopierZone(0, 1, 0, 0, FEN_L, FEN_H, 0, 0);
			}

			/* Autrement on affiche le nom de la station */
			else
				EcrireTexte((reseau[station].x)/2 + DECAL_TXT_STAT, 
							(reseau[station].y)/2 + DECAL_TXT_STAT, 
							reseau[station].nom, SIZE_TXT_STA);
		}
		
		else
		{
			if (SourisCliquee())
			{
				/* Traitement des checkbox. */
				traite_checkbox(c, &environment);
	
				/* Traitement des listbox. */
				traite_listbox(c, environment.lb);
			
				/* Traitement du bouton "Enregistrer dans un fichier". */
				
				if ((enregistrer) && 
					(c .x >= X_ENR) &&
					(c.x <= X_ENR + L_ENR) &&
					(c.y >= Y_ENR) &&
					(c.y <= Y_ENR + H_ENR))
					enregistrer_itineraire(*environment.lb);
				
				CopierZone(0, 1, 0, 0, FEN_L, FEN_H, 0, 0);

			}
			else			
				CopierZone(1, 0, 0, 0, FEN_L, FEN_H, 0, 0);
			
		}	
		/* Vidange de clique inutile. */
		while (SourisCliquee());

	} while (!ToucheEnAttente());
}

/*--------------------------------------------------*
 *	Fonction qui dessine les differentes lignes 	*
 *	de transports.									*
 *--------------------------------------------------*/

void draw_lines(ligne voie, coord a, string color)
{
	coord b;

	if (voie->nom_ligne[INDICE_LIGNE] == SEPARATEUR_DATA)
	{
		voie = voie->next;
		b.x = voie->station->x;
		b.y = voie->station->y;
	}

	else
	{
		b.x = voie->station->x;
		b.y = voie->station->y;
	
		DessinerSegmentC((TAILLE_STATION + a.x)/2, 
					 (TAILLE_STATION + a.y)/2, 
					 (TAILLE_STATION + b.x)/2, 
					 (TAILLE_STATION + b.y)/2,
					 CouleurParNom(color));
	}
	/* Arret suivant. */
	if (voie->next != NULL)
		draw_lines(voie->next, b, color);
}

/*--------------------------------------------------*
 * 	Dessine l'ensemble du reseau metropolitain.		*
 *--------------------------------------------------*/

void draw_reseau(env environment)
{
	coord a;

	/* Dessine les stations. */
	draw_stations(environment);

	/* Dessine les differentes lignes de transports. */
	draw_lines(environment.metro, a, COLOR_METRO);

	draw_lines(environment.rer, a, COLOR_RER); 

	draw_lines(environment.pieton, a, COLOR_PIETON);
}

/*--------------------------------------------------*
 * 			Dessine l'interface graphique.			*
 *--------------------------------------------------*/

void draw_interface(void)
{
	int i;

	ChoisirEcran(1);
		
	/* Arriere plan en blanc. */
	EffacerEcran(CouleurParNom(COUL_ARR_PLAN));

	ChargerImage(IMG_NAME, 0, 0, 0, 0, L_IMG, H_IMG);

	ChoisirEcran(0);
	
	/* Dessine les checkbox avec leurs etiquettes. */ 
	for (i = 0; i < MAX_CB; ++i)
	{	
		/* Checkbox OK. */
		CopierZone(1, 0, OX_CB_OK, OY_CB_OK, SIZE_CB, 
				   SIZE_CB, X_CB, Y_CB + i * ESPACE_CB);

		/* Etiquette. */
		CopierZone(1, 0, OX_LABEL, OY_LABEL + i * SIZE_CB, 
				   L_LABEL, SIZE_CB, X_CB + SIZE_CB + ESPACE_LABEL, 
                   Y_CB + i * ESPACE_CB);
	}

	/* Dessine la listbox. */	
	draw_listbox(X_LB, Y_LB, L_LB, H_LB);

	/* Dessine l'image "Modes de deplacement". */
	CopierZone(1, 0, OX_MODE, OY_MODE, L_MODE, H_MODE, X_MODE, Y_MODE);

	/* Dessine les images "depart" et "arrivee". */
	CopierZone(1, 0, OX_DEP, OY_DEP, L_DEP, H_DEP, X_DEP, Y_DEP);
	CopierZone(1, 0, OX_ARR, OY_ARR, L_ARR, H_ARR, X_ARR, Y_ARR);

	/* Dessine l'image du ticket. */
	CopierZone(1, 0, OX_ICN, OY_ICN, L_ICN, H_ICN, X_ICN, Y_ICN);	

	CopierZone(0, 1, 0, 0, FEN_L, FEN_H, 0, 0);
	CopierZone(0, 2, 0, 0, FEN_L, FEN_H, 0, 0);
}

/*------------------------ Fin du fichier metro_interface.c */
/* EOF */
