/*------------------------------ Fichier metro_main.h */

/* Encapsulation contre les inclusions multiples. */
#ifndef METRO_MAIN_H                    
#define METRO_MAIN_H 

/* ======================================= Constantes */

/* Choix arbitraire de la longueur de la chaine
   d'une station. */
#define STATION_NAME_MAX 50

/* Choix arbitraire de la longueur de la chaine
   d'une ligne. */
#define LINE_NAME_MAX 90

/* Chaine de caractere qui separe le nom de la ligne 
   et la station concernee. */
#define STR_SEPARATEUR_LIGNE ":"

/* Indice de ligne. */
#define INDICE_LIGNE 0

/* 2 eme indice qui separe un numero et un nom de ligne. */
#define INDICE_LIGNE2 5

/* Caractere qui separe le nom de la ligne 
   et la station concernee. */
#define SEPARATEUR_LIGNE ':'

/* Caractere qui correspond au pieton. */
#define INDICE_PIETON 'P'

/* 1er caractere qui correspond au RER. */
#define INDICE_RER_DEBUT 'A'

/* Dernier caractere qui correspond au RER. */
#define INDICE_RER_FIN 'D'

/* Caractere saut de ligne. */
#define ENDL '\n'

/* Nombre d'item dans la listbox. */
#define ITEM_MAX 40

/* Constante d'erreur si aucune station
 * n'as ete trouvee. */
#define ERR_STATION -1

/* Caractere qui separe les differentes voies. */ 
#define SEPARATEUR_DATA '#'

/* Nombre de caractere maximum dans la listbox. */
#define STR_MAX 100

/* ============================================ Types */

/* Type chaine de caracteres. */
typedef char * string;

/* ====================================== Enumeration */

/* Enumeration booleen. */
typedef enum { FALSE, TRUE } bool;

/* ======================================= Structures */

/* Structure qui represente une station. */
typedef struct
{
	int x;
	int y;
	char nom[STATION_NAME_MAX];
} station;

/* Structure qui represente une coordonnee. */
typedef struct
{
	int x;
	int y;
} coord;

/* 
 * Definition d'une liste chainee qui servira 
 * a representer une voie de transport.
 */
struct arret
{
	char nom_ligne[LINE_NAME_MAX];	
	station * station;
	struct arret * next;
};

typedef struct arret * ligne;

/* Structure contenant des variables necessaire a la listbox. */
typedef struct 
{
	int current_indice;
	int data_indice;
	int n_item;
	char tablistbox[ITEM_MAX][STR_MAX];
} listbox;

/* Structure qui represente l'environnement du programme. */
typedef struct
{
	int station_depart;
	int station_arrivee;

	int n_station;
	int n_metro;
	int n_pieton;
	int n_rer;
	
	bool avec_rer;
	bool avec_metro;
	bool avec_pieton;
	
	station * reseau;

	ligne metro;
	ligne rer;
	ligne pieton;

	float ** matrice;

	listbox * lb;
} env;

#endif /* #ifndef METRO_MAIN_H */
/*-------------------------- Fin du fichier metro_main.h */
/* EOF */
