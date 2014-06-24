/*------------------------------ Fichier pile.h */

/* Encapsulation contre les inclusions multiples */
#ifndef PILE_H
#define PILE_H

#include "../inc/metro_main.h" /* bool */

/* Constante qui represente la pile vide. */
#define PILE_ERR -1 

/* ======================================= Structures */

/* 
 * Definition d'une liste chainee qui servira a representer 
 * une pile (le sommet de la pile correspond au debut de la 
 * liste chainee).
 */

struct maillon 
{
	int valeur;
	struct maillon * suivant;
};

typedef struct maillon * pile;

/* ============================ Fonctions publiques */

/*--------------------------------------------------*
 * 	Ajoute une donnee (qui devient donc le nouveau	*
 *  sommet de la pile).								*
 *--------------------------------------------------*/

void push(pile * pp, int n);

/*--------------------------------------------------*
 * Retire et renvoie la donnee la plus recente (si	*
 * la pile n'est pas vide).							*
 *--------------------------------------------------*/

int pop(pile *pp);

/*--------------------------------------------------*
 * 		Determine si la pile est vide.				*
 *--------------------------------------------------*/

bool empty(pile p);

/*--------------------------------------------------*
 * Renvoie sans la retirer la donnee la plus 		*
 * recente (si la pile n'est pas vide).				*
 *--------------------------------------------------*/

int top(pile p);

/*--------------------------------------------------*
 * 		Retire toutes les donnees de la pile.		*
 *--------------------------------------------------*/

void clean(pile *pp);

#endif /* #ifndef PILE_H */

/*-------------------------- Fin du fichier pile.h */
/* EOF */
