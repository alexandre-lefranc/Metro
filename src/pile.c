/*---------------------------- Fichier pile.c */

/* Bibliotheque standard. */
#include <stdlib.h> /* malloc(), free() ... */

/* Inclusion pour assurer la coherence. */
#include "../inc/pile.h"

/*--------------------------------------------------*
 * 	Ajoute une donnee (qui devient donc le nouveau	*
 *  sommet de la pile).								*
 *--------------------------------------------------*/

void push(pile * pp, int n)
{
	pile nouveau = (pile) malloc(sizeof(struct maillon));
	nouveau->valeur = n;
	nouveau->suivant = *pp;
	*pp = nouveau;
}

/*--------------------------------------------------*
 * Retire et renvoie la donnee la plus recente (si	*
 * la pile n'est pas vide).							*
 *--------------------------------------------------*/

int pop(pile *pp)
{
	struct maillon tmp;

	if (empty(*pp))
		return PILE_ERR; 
	
	tmp = **pp;
	free(*pp);
	*pp = tmp.suivant;

	return tmp.valeur;
}

/*--------------------------------------------------*
 * 		Determine si la pile est vide.				*
 *--------------------------------------------------*/

bool empty(pile p)
{
	return (p == NULL);
}

/*--------------------------------------------------*
 * Renvoie sans la retirer la donnee la plus 		*
 * recente (si la pile n'est pas vide).				*
 *--------------------------------------------------*/

int top(pile p)
{
	if (!empty(p))
		return p->valeur;
	else 
		return PILE_ERR;
}

/*--------------------------------------------------*
 * 		Retire toutes les donnees de la pile.		*
 *--------------------------------------------------*/
void clean(pile *pp)
{
	while (!empty(*pp))
		pop(pp);
}

/*-------------------------- Fin du fichier pile.c */
/* EOF */
