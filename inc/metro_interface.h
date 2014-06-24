/*----------------------- Fichier metro_interface.h */

/* Encapsulation contre les inclusions multiples */
#ifndef METRO_INTERFACE_H                    
#define METRO_INTERFACE_H

#include "../inc/metro_main.h" /* station * ... */

/* ====================================== Constantes */

/* Taille de la fenetre */

#define FEN_L 800 /* Largeur de la fenetre */
#define FEN_H 710 /* Hauteur de la fenetre */

/* Couleur de l'arriere plan */
#define COUL_ARR_PLAN "white" 

/* Nom du fichier comportant les images */
#define IMG_NAME "img/images.xpm"

#define L_IMG 299 /* Largeur de l'image */
#define H_IMG 246 /* Hauteur de l'image */

/* Taille d'une station */
#define TAILLE_STATION 4
/* Angle d'un cercle. */
#define ANGLE1 0
#define ANGLE2 360

/* Taille du texte d'une station survolee. */
#define SIZE_TXT_STA 0
/* Couleur d'une station selectionnee. */
#define COUL_STA_SELECT "red"
/* Decalage du texte d'une station survolee. */
#define DECAL_TXT_STAT -10

/* Nom du fichier ou l'on sauvegarde  
 * l'itineraire. */
#define FILENAME_SAVE "itineraire.txt"

/* Image "Depart" */

#define X_DEP 20  /* Abcisse du coin superieur gauche de l'image. */
#define Y_DEP 490 /* Ordonnee du coin superieur gauche de l'image. */

#define OX_DEP 0 /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_DEP 0 /* Ordonnee du coin superieur gauche de l'image dans le fichier. */

#define L_DEP 97 /* Largeur de l'image. */
#define H_DEP 31 /* Hauteur de l'image. */

/* Texte station de depart. */

#define X_ESPACE_DEP 20 /* Abcisse du coin superieur gauche du texte. */
#define Y_ESPACE_DEP 19 /* Ordonnee du coin superieur gauche du texte. */

#define TAILLE_DEP 1 /* Taille du texte */

/* Image "Arrivee" */

#define X_ARR 20  /* Abcisse du coin superieur gauche de l'image. */
#define Y_ARR 530 /* Ordonnee du coin superieur gauche de l'image. */

#define OX_ARR 0  /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_ARR 31 /* Ordonnee du coin superieur gauche de l'image dans le fichier. */

#define L_ARR 101 /* Largeur de l'image. */
#define H_ARR 31  /* Hauteur de l'image. */

/* Texte station d'arrivee. */

#define X_ESPACE_ARR 20 /* Abcisse du coin superieur gauche du texte. */
#define Y_ESPACE_ARR 19 /* Ordonnee du coin superieur gauche du texte. */
#define TAILLE_ARR 1 /* Taille du texte */

/* Checkbox */
#define SIZE_CB 46 /* Taille de la checkbox */

#define X_CB 570 /* Abcisse du coin superieur gauche de l'image. */
#define Y_CB 160 /* Ordonnee du coin superieur gauche de l'image. */

#define OX_CB 0  /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_CB 62 /* Ordonnee du coin superieur gauche de l'image dans le fichier. */

/* Checkbox valide */
#define OX_CB_OK 46 /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_CB_OK 62 /* Ordonnee du coin superieur gauche de l'image dans le fichier. */

#define ESPACE_CB 60 /* Espace entre les checkbox. */

#define MAX_CB 3 /* Nombre de checkbox */

/* "Etiquettes" des checkbox */

#define OX_LABEL 0   /* Abcisse du coin superieur gauche de la 1ere image dans le fichier. */
#define OY_LABEL 108 /* Ordonnee du coin superieur gauche de la 1ere image dans le fichier. */
#define L_LABEL 131  /* Largeur de l'image. */
#define ESPACE_LABEL 20 /* Espace entre l'etiquette et la checkbox */

/* Image : "Enregistrer dans un fichier" */

#define X_ENR 560  /* Abcisse du coin superieur gauche de l'image. */
#define Y_ENR 610  /* Ordonnee du coin superieur gauche de l'image. */
#define OX_ENR 109 /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_ENR 63  /* Ordonnee du coin superieur gauche de l'image dans le fichier. */
#define L_ENR 139  /* Largeur de l'image. */
#define H_ENR 45   /* Hauteur de l'image. */

/* Image : "Modes de deplacement" */

#define X_MODE 600  /* Abcisse du coin superieur gauche de l'image. */
#define Y_MODE 60   /* Ordonnee du coin superieur gauche de l'image. */
#define OX_MODE 101 /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_MODE 0   /* Ordonnee du coin superieur gauche de l'image dans le fichier. */
#define L_MODE 152  /* Largeur de l'image. */
#define H_MODE 46   /* Hauteur de l'image. */

/* Listbox */

#define X_LB 20   /* Abcisse du coin superieur gauche de la listbox. */
#define Y_LB 570  /* Ordonnee du coin superieur gauche de la listbox. */
#define L_LB 520  /* Largeur de la listbox. */
#define H_LB 133  /* Hauteur de la listbox. */

/* Scrollbar */

#define OX_SCRLB_UP 92 /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_SCRLB_UP 62 /* Ordonnee du coin superieur gauche de l'image dans le fichier. */

#define OX_SCRLB_DOWN 92 /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_SCRLB_DOWN 81 /* Ordonnee du coin superieur gauche de l'image dans le fichier. */

#define H_SCRLB 19  /* Hauteur de l'image. */
#define L_SCRLB 16  /* Largeur de l'image. */

#define SIZE_TXT 0 /* Taille du texte d'un item */
#define ESPACE_TXT 5 /* Decalage du texte */

/* Drapeau */

#define DRAP "img/drapeau.xpm" /* Nom du fichier. */ 

#define L_DRAP 23 /* Largeur de l'image. */
#define H_DRAP 20 /* Hauteur de l'image. */
#define OX_DRAP 0 /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_DRAP 0 /* Ordonnee du coin superieur gauche de l'image dans le fichier. */

/* Image du "ticket" */
#define X_ICN 570 /* Abcisse du coin superieur gauche de l'image. */
#define Y_ICN 420 /* Ordonnee du coin superieur gauche de l'image. */
#define L_ICN 167 /* Largeur de l'image. */
#define H_ICN 185 /* Hauteur de l'image. */
#define OX_ICN 131 /* Abcisse du coin superieur gauche de l'image dans le fichier. */
#define OY_ICN 110 /* Ordonnee du coin superieur gauche de l'image dans le fichier. */

#define COLOR_METRO "orange" /* Couleur des lignes du metro. */
#define COLOR_RER "magenta" /* Couleur des lignes du RER. */
#define COLOR_PIETON "green" /* Couleur des lignes pieton. */
#define COLOR_ITINERAIRE "blue" /* Couleur de l'itineraire. */

/* ============================ Fonctions publiques */

/*--------------------------------------------------*
 * 		Fonction qui dessine une listbox.			*
 *--------------------------------------------------*/

void draw_listbox(int x, int y, int l, int h);

/*--------------------------------------------------*
 * 	Fonction qui dessine les items de la listbox.	*
 *--------------------------------------------------*/

void draw_items(int x, int y, int l, int h, listbox * lb);

/*--------------------------------------------------*
 * 		 	Fonction qui ajoute un item.			*
 *--------------------------------------------------*/

void add_item_listbox(string text, listbox * lb);

/*--------------------------------------------------*
 * 	Fonction qui enregistre un itineraire dans un 	*
 *	fichier.										*
 *--------------------------------------------------*/

void enregistrer_itineraire(listbox lb);

/*--------------------------------------------------*
 *		Fonction qui initialise une listbox.		*
 *--------------------------------------------------*/

void listbox_init(listbox * lb);

/*--------------------------------------------------*
 *	Fonction qui recherche une station et retourne 	*
 *	son adresse.									*
 *--------------------------------------------------*/

station * get_station(string station_name, 
						env environment);

/*--------------------------------------------------*
 *          Cree une interface graphique. 			*
 *--------------------------------------------------*/

void interface_init(void);

/*--------------------------------------------------*
 * 			Ferme l'interface graphique.			*
 *--------------------------------------------------*/

void interface_shutdown(void);

/*--------------------------------------------------*
 * 	Fonction qui cherche si la coordonnee transmit 	*
 *	par argument existe, la fonction retourne son 	*
 *	indice ou ERR_STATION (-1) si elle n'existe pas.*	
 *--------------------------------------------------*/

int is_station(coord c, env environment);

/*--------------------------------------------------*
 * Fonction qui retourne le numero de ligne desiree.*
 *--------------------------------------------------*/

string get_line_name(string station, env environment, 
						string station_next);

/*--------------------------------------------------*
 * Fonction qui cherche le numero de ligne desiree. *
 *--------------------------------------------------*/

string find_line_name(ligne voie, string station, 
					  string station_next);

/*--------------------------------------------------*
 * 		Fonction qui affiche un itineraire.	  		*
 *--------------------------------------------------*/

void affiche_itineraire(ligne itineraire, env environment);

/*--------------------------------------------------*
 *		Fonction qui gere l'interface graphique.	*
 *--------------------------------------------------*/

void traite_interface(env environment);

/*--------------------------------------------------*
 *	Fonction qui dessine les differentes lignes 	*
 *	de transports.									*
 *--------------------------------------------------*/

void draw_lines(ligne voie, coord a, string color);

/*--------------------------------------------------*
 * 	Dessine l'ensemble du reseau metropolitain.		*
 *--------------------------------------------------*/

void draw_reseau(env environment);

/*--------------------------------------------------*
 * 			Dessine l'interface graphique.			*
 *--------------------------------------------------*/

void draw_interface(void);

#endif	/* #ifndef METRO_INTERFACE_H */

/*---------------- Fin du fichier metro_interface.h */
/* EOF */
