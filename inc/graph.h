#ifndef _GRAPH_H
#define _GRAPH_H


#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/keysym.h>

extern int _X;
extern int _Y;

typedef unsigned long couleur;

int InitialiserGraphique();
/* initialise le mode graphique : renvoie 1 en cas d'echec, 0 sinon */

int CreerFenetre(int posx,int posy,int X,int Y);
/* creer la fenetre graphique de largeur X et longueur Y, et la positionne
   sur l'ecran au point (posx,posy). Une seule fenetre autoris�e */

void CacherFenetre(void);
/* cache la fenetre */

void AfficherFenetre(void);
/* affiche la fenetre */

void ChoisirEcran(int n);
/* fixe l'ecran ou le dessin est effectue : cette ecran est soit 0 (la fenetre
   visible, ecran par defaut au demarrage), soit 1 ou 2 qui sont deux ecrans virtuels */

void ChoisirCouleurDessin(couleur c);
/* fixe la couleur qui sert au dessin */

int Maxx();
/* renvoie la largeur de l'ecran : il faut que le mode graphique ait �t� 
   initialise !!! */

int Maxy();
/* renvoie la hauteur de l'ecran : il faut que le mode graphique ait �t� 
   initialise !!! */

void DessinerPixelC(int x,int y, couleur c);
/* allume avec couleur un pixel de la fenetre : ne modifie pas la 
   couleur de dessin */

void DessinerPixel(int x,int y);
/* allume un pixel avec la couleur de dessin */

void DessinerSegmentC(int x,int y,int xx,int yy,couleur c);
/* trace un segment d'extremit�s (x,y) et (xx,yy) avec couleur : ne modifie 
   pas la couleur de dessin */

void DessinerSegment(int x,int y,int xx,int yy);
/* idem precedent, mais avec la couleur de dessin */

couleur CouleurParNom(char * nom);
/* fait la traduction d'une couleur a partir de son nom : le fichier rgb.txt
   contient la liste des couleurs accessibles via leur nom */

couleur CouleurParComposante(unsigned char r, unsigned char v,unsigned char b); 
/* renvoie la couleur d�finie par ses trois composantes */
 
void DessinerRectangleC(int x,int y,int l,int h,couleur c);
/* trace un rectangle dont le coin superieur gauche est (x,y), de largeur et 
   hauteur l+1 et h+1 */

void RemplirRectangleC(int x,int y,int l,int h,couleur c);
/* trace un rectangle plein, rempli avec c */

void DessinerRectangle(int x,int y,int l,int h);
/* idem, mais utilise la couleur de dessin */

void DessinerArcC(int x,int y,int l,int h,int angle1,int angle2,couleur c);
/* tra un arc inscrit dans le rectangle (x,y,x+l,y.h), rep�re par angle1 et 
   angle2 (cf doc pour plus d'explication */

void DessinerArc(int x,int y,int l,int h,int angle1,int angle2);
/* idem, mais utilise la couleur de dessin */

void RemplirArcC(int x,int y,int l,int h,int angle1,int angle2,couleur c);
/* trace un arc plein avec c */

int ToucheEnAttente();
/* renvoie 1 si une touche a �t� enfonc�e, 0 sinon */

KeySym Touche();
/* renvoie la premiere touche du tampon : cette fonction est bloquante => 
   utiliser ToucheEnAttente  pour la rendre non bloquante */

void EcrireTexteC(int x,int y,char *texte,couleur c,int taille);
/* ecrit la chaine texte au point (x,y) avec la couleur c : taille indique la taille (0<->petit,1<->moyen,2<->grand) */

void EcrireTexte(int x,int y,char *texte,int taille);
/* idem, avec la couleur de dessin  */

void SauverImage(char * file,int x,int y,int l,int h);
/* sauvegarde d'une partie de la fenetre (x,y,x+l,y+h) au format xpm */


void ChargerImage(char *file,int x,int y,int xx,int yy,int l,int h);
/* charge une partie (xx,yy,xx+l,yy+h) d'image au format xpm dans 
la fenetre a la position (x,y) */

void ChargerImageFond(char *file);
/* charge une image qui remplit le fond de la fen\^etre, en la r\'ep\'etant si necessaire */

void EffacerEcran(couleur c);
/* efface l'ecran avec la couleur c*/

void ChoisirModeDessin(int m);
/* fixe le mode d'affichage : 0<->ecrasement 1<->xor */

int TailleChaineEcran(char *t,int taile);
/* renvoie, en pixel, la taille horizontale occupee par la chaine � l'�cran :taille est la taille de la police (0,1,2) */

int TailleSupPolice(int taille);
/* renvoie la taiile maximale de la police, en pixel, au dessus de la ligne d'�criture */

int TailleInfPolice(int taille);
/* renvoie la taille maximale de la police, en pixel, en dessous de la ligne d'�criture */

void CopierZone(int src,int dst,int ox,int oy,int L,int H,int dx,int dy);
/* copie une zone de l'�cran vers l'�cran dst. La zone copi�e est le rectangle delimite par le coin superieure hauche (ox,oy) et sa largeur l et hauteur h. Cette zone est copi� au point (dx,dy) de l'ecran dst */ 

void FermerGraphique();
/* fermeture du mode graphique */


void SourisPosition();
/* recupere les coordonnees de la souris dans la fenetre et les place dans _X et _Y*/

int SourisCliquee();
/* indique un clic de souris (1 si oui, 0 sinon), et recupere si c'est le cas la position au moment du clic dans _X et _Y */





#endif
