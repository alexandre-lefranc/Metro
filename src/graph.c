#include<X11/Xlib.h>
#include<X11/cursorfont.h>
#include<X11/Xatom.h>
#include<X11/Xutil.h>
#include<X11/keysym.h>
#include<X11/xpm.h>

#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "graph.h"

void get_GC(Window win, GC *gc);

/******************** variables globales ****************************/

Display *display;
int screen;
int display_width=0,display_height=0;
int X_fen,Y_fen;
int conecte=0;
int nbfen=0;
Window win;
XColor coul; 
unsigned long couleur_dess;
XEvent report;                      /* structure des evenements */

GC gc;                              /* ID du contexte graphique */
unsigned int border_w=4; 
Cursor croix;
XSetWindowAttributes attribut;
Colormap pal;			    /* palette 			*/
Font f[3];			    /* font d'ecriture          */
XFontStruct *s[3];
XFontStruct *stemp;
Pixmap icone;
XImage * xi;
int num_ecran=0;
Window ecran[3];
int app=0;
XWMHints  wm_hints;
XClassHint  class_hints;
XSizeHints  size_hints;

XTextProperty nom_fenetre,nom_icone;

char *nf="Microprojet 2 - Metro";
char *ni="mon_icone";

int _X=0,_Y=0;

/******************************************************************/
/*                  icone de la fenetre en dur !!!                */
/******************************************************************/

#define icone_width 30
#define icone_height 30
static unsigned char icone_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x10, 0x00, 0x10, 0x10, 0x0c, 0x00,
   0x08, 0x20, 0x02, 0x00, 0x04, 0xc0, 0x01, 0x00, 0x04, 0x40, 0x00, 0x00,
   0x04, 0x70, 0xfc, 0x1f, 0x04, 0x48, 0x04, 0x10, 0x04, 0x44, 0x04, 0x10,
   0x04, 0x43, 0x04, 0x10, 0x84, 0x40, 0x04, 0x10, 0x68, 0x20, 0x04, 0x10,
   0x10, 0x10, 0x04, 0x10, 0xec, 0x0f, 0xfc, 0x1f, 0x02, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x02, 0x00, 0x81, 0x00, 0x01,
   0x80, 0x03, 0x01, 0x01, 0xc0, 0x03, 0x82, 0x00, 0xe0, 0x07, 0x44, 0x00,
   0xe0, 0x07, 0x48, 0x00, 0xf0, 0x0f, 0x30, 0x00, 0xf8, 0x1f, 0x50, 0x00,
   0xfc, 0x1f, 0x90, 0x00, 0xfe, 0x3f, 0x08, 0x01, 0xe0, 0x3f, 0x04, 0x02,
   0x00, 0x78, 0x04, 0x04, 0x00, 0x00, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00};

static char *iconet[]={
/*
"40 40 5 1",
"# c #000000",
"c c #0000ff",
". c #c0ffff",
"b c #ff0000",
"a c #ffff00",
"........................................",
"........................................",
"........................................",
".##########################.............",
".#aaaaaaaaaaaaaaaaaaaaaaaa#.............",
".#aaaaaaaaaaaaaaaaaaaaaaaa#.............",
".#aaaaaaaaaaaaaaaaaaaaaaaa#.............",
".#aaaaaaaaaaaaaaaaaaaaaa#####...........",
".#aaaaaaaaaaaaaaaaaaa###bb#bb##.........",
".#aaaaaaaaaaaaaaaaaa#bbbbb#bbb##........",
".#aaaaaaaaaaaaaaaaa##bbbbb#bbbbb#.......",
".#aaaaaaaaaaaaaaaaa#bbbbbb#bbbbb#.......",
".#aaaaaaaaaaaaaaaa#bbbbbbb#bbbbb#.......",
".#aaaaaaaaaaaaaaaa#bbbbbbb#bbbbbb#......",
".#aaaaaaaaaaaaaaaa#bbbbbbb#bbbbbb#......",
".##########################bbbbbb#......",
"..................#bbbbbbbbbbbbbb#......",
"...................#bbbbbbbbbbbbb#......",
"...................#bbbbbbbbbbbb#.......",
".........##........#bbbbbbbbbbb##.......",
".........#c#........##bbbbbbbbb#........",
".........#cc##.......##bbbbb###.........",
"........#ccccc#........#####............",
"........#cccccc##.......................",
"........#cccccccc#......................",
".......#cccccccccc##....................",
".......#cccccccccccc#...................",
".......#ccccccccccccc##.................",
"......#cccccccccccccccc#................",
"......#ccccccccccccccccc##..............",
".....#cccccccccccccccccccc#.............",
".....#ccccccccccccccccccccc##...........",
".....#ccccccccccccccccccccccc#..........",
"....#ccccccccccccccccccccccccc##........",
"....#ccccccccccccccccccccccccccc#.......",
"....#cccccccccccccccccccccccccccc##.....",
"...#ccccccccccccccccccccccccccccccc#....",
"...#cccccccccccccccccccccccccccccccc#...",
"..####################################..",
"........................................"};*/
/* XPM */
/* columns rows colors chars-per-pixel */
"21 21 127 2",
"|  c #3232AD",
"T  c #6767C2",
"3  c #2323A3",
">. c #D1D1ED",
"1  c #4949B6",
"2  c #050599",
"<. c #05059C",
"Q  c #6F6FC6",
"N  c #D9D9F0",
"6. c #6060BF",
"_  c #2B2BAB",
"   c #C0FFFF",
"k  c #8686CF",
"U  c #F0F0F9",
"4. c #E1E1F3",
"3. c #6868C2",
"R  c #2424A2",
"f  c #2424A7",
"O  c #15159D",
"t  c #C3C3E7",
"v  c #F8F8FC",
"r  c #7F7FCB",
"M  c #060697",
":  c #B4B4E1",
"Y  c #3B3BB1",
"(  c #0E0E99",
">  c #BCBCE4",
"#  c #4343B0",
"P  c #0E0E9D",
"-  c #4343B4",
"!  c #7878C9",
"Z  c #ADADDE",
"&. c #D3D3EE",
"z  c #F9F9FD",
"e. c #8080CC",
"1. c #B5B5E2",
"B  c #EAEAF7",
"7  c #3C3CB1",
":. c #A6A6DB",
"^  c #7171C7",
"5. c #DBDBF1",
"c  c #2D2DA8",
"$  c #9797D5",
"2. c #5353B8",
"*. c #00008B",
"$. c #1E1EA5",
"K  c #5353BA",
"~  c #00008F",
"b  c #BDBDE5",
"g  c #F2F2FA",
"j  c #000091",
"6  c #000094",
"J  c #3535AA",
"@  c #000096",
"I  c #E3E3F4",
"=  c #000098",
"[  c #9F9FD9",
"G  c #2626A8",
"<  c #9090D3",
"8. c #C5C5E8",
"F  c #FAFAFD",
"m  c #4C4CB6",
",  c #B6B6E1",
"+. c #3D3DAE",
",. c #EBEBF8",
"`  c #DCDCF1",
"{  c #1F1FA0",
"r. c #8989CF",
"O. c #10109A",
".  c #F3F3FA",
"w. c #4545B2",
"q  c #6B6BC3",
"D  c #6B6BC4",
"n  c #A0A0D9",
"u  c #FBFBFD",
"9. c #FBFBFE",
"s  c #B7B7E2",
";  c #8A8AD0",
"%. c #F4F4FB",
"l  c #020291",
"]  c #1111A0",
"0  c #7B7BCA",
"+  c #020295",
"C  c #3737AF",
"y  c #5D5DBE",
"w  c #FCFCFE",
"/  c #1919A3",
"q. c #0A0A97",
"W  c #4E4EB8",
" . c #8383CD",
"t. c #B8B8E3",
"=. c #EDEDF8",
"L  c #0A0A9B",
"x  c #3030AC",
")  c #CFCFEC",
"H  c #5656B9",
"#. c #2121A6",
"V  c #12129F",
"o  c #4747B4",
";. c #030397",
"&  c #B1B1E0",
"d  c #3838AD",
"y. c #A2A2D9",
"a  c #6D6DC5",
"0. c #A2A2DA",
"*  c #2929A5",
"i  c #D7D7EF",
"o. c #9393D4",
".. c #FDFDFE",
"A  c #1A1AA4",
"X. c #0B0B9E",
"h  c #7575C8",
"X  c #9B9BD7",
"@. c #5757BC",
"8  c #C1C1E6",
"7. c #F6F6FB",
"p  c #F6F6FC",
"}  c #7D7DCB",
"'  c #D8D8EF",
"-. c #5F5FBD",
"E  c #1B1B9E",
"9  c #C9C9E9",
"S  c #5050B9",
"5  c #8585CE",
"%  c #EFEFF9",
"e  c #7676C8",
"4  c #ABABDD",
/* pixels */
"          . X o O + @ + O # $ %           ",
"        & * = - ; : > , < 1 2 3 4         ",
"      5 6 7 8               9 o 6 0       ",
"    ; 6 q w                     e 6 r     ",
"  t + y   u i u             i p   a 6 s   ",
"u d f g   h j a           k l y   z x c v ",
"b 6 n     m j M N       B V j C     & 6 Z ",
"q A g     S 6 j D       5 j 6 7     F G H ",
"J K       S 6 L P I   U A L 2 Y       T R ",
"E 0       W = Q j !   < ~ ^ / C       < ( ",
"E ;       W 6 ) _ V ` f V ' ] C       [ ( ",
"{ }       W 6 I [ j | 6  ...X.C       o.O.",
"+.@.      W 6 i v #.j P B . X.C       D * ",
"! $.%.    W 6 &.  o.*.e   =.X.C     w _ -.",
") ;.:.    1 j >.  v , .   ,.<.|     1.6 s ",
"  2.G .   3.O 4.          . G S   F | d w ",
"  5.O.6.  F B               =.7.  Q + 8.  ",
"    4 6 T 9.                    e 6 <     ",
"      0.q.d >               8.w.+ ;       ",
"        9 +.= Y e.4 : Z r.- ;.c t.        ",
"          u Z 2.{ M ;.2 E m y.7.          "
};


/**************************************************************************/

void ChoisirModeDessin(int m)
{
	if (m==0) XSetFunction(display,gc,GXcopy);
	if (m==1) XSetFunction(display,gc,GXxor);
}

void ChoisirCouleurDessin(unsigned long couleur)
{
	couleur_dess=couleur;
	XSetForeground(display,gc,couleur);
	XFlush(display);
}

void ChoisirEcran(int n)
{
	if (0<=n&&n<=2) num_ecran=n;
}

int InitialiserGraphique()
{
	if (!conecte)
    {
		if((display=XOpenDisplay(NULL))==NULL) 
		{
	  		fprintf(stderr,"erreur : ne peut pas se connecter ");
	  		fprintf(stderr,"au serveur %s\n",XDisplayName(NULL));
	  		return (1);
		}
		if(conecte) 
			return 0;  

  	/* Recuperer les informations concernant l'ecran (root window) sur	*
     * lequel on va afficher notre application. Le numero de l'ecran	*
     * par defaut s'obtient a l'aide de la macro DefaultScreen(), la	*
     * taille a l'aide des macros DisplayWidth() et						*
     * DisplayHeight().													*/
 
	screen = DefaultScreen(display);
	display_width = DisplayWidth(display,screen);
	display_height = DisplayHeight(display,screen);
  pal=DefaultColormap(display,screen);
  conecte=1;
  return 0;
  }
}

int CreerFenetre(int posx,int posy,int X,int Y)
{
  int i;
  Visual *v;
	if (!conecte) {
			printf("initialisez d'abord le mode graphique\n");
			return (1);
			}
	
	if (nbfen==1) {
	             printf("une seule fentre on a dit !!!!\n");
                     return(1);
	              }

	
	ecran[0] = XCreateSimpleWindow(display, RootWindow(display, screen), posx, posy,
			    X, Y, border_w,
			    BlackPixel(display,screen),
			    WhitePixel(display,screen));
       		    
/* selection des evenements que l'on desirera traiter pour cette fenetre */

 XSelectInput(display, ecran[0], ExposureMask | KeyPressMask |
	      ButtonPressMask  );


  /* creation d'un contexte graphique pour cette fenetre,
     indispensable pour dessiner ou afficher du texte */
     
     
     get_GC(ecran[0], &gc);
  
  /* creation d'une fonte curseur */

	croix=XCreateFontCursor(display,XC_crosshair);
	XDefineCursor(display,ecran[0],croix);
	
 /* le contenu de la fenetre est persistant : le serveur le supporte-t-il ? */       

	attribut.backing_store=Always;
	XChangeWindowAttributes(display,ecran[0],CWBackingStore,&attribut);

  
  /* chargement d'une font par defaut pour l'ecriture de texte */
	// f[0]=XLoadFont(display,"-adobe-courier-medium-r-normal--12-120-75-75-m-70-iso8859-1");
	// f[1]=XLoadFont(display,"-adobe-courier-medium-r-normal--20-140-100-100-m-110-iso8859-1");
	//f[2]=XLoadFont(display,"-adobe-courier-medium-r-normal--34-240-100-100-m-200-iso8859-1");

	stemp=XLoadQueryFont(display,"-adobe-times-medium-r-*-*-12-*-*-*-*-*-*-*");
	if (stemp==NULL) stemp=XLoadQueryFont(display,"fixed");
	f[0]=stemp->fid;
	s[0]=stemp;

	stemp=XLoadQueryFont(display,"-adobe-times-medium-r-*-*-22-*-*-*-*-*-*-*");
	if (stemp==NULL) stemp=XLoadQueryFont(display,"fixed");
	f[1]=stemp->fid;
	s[1]=stemp;

	stemp=XLoadQueryFont(display,"-adobe-times-medium-r-*-*-32-*-*-*-*-*-*-*");
	if (stemp==NULL) stemp=XLoadQueryFont(display,"fixed");
	f[2]=stemp->fid;
	s[2]=stemp;

	
     XSetFont(display,gc,f[1]);


  
  /* creation du pixmap pour la sauvegarde d'images */
 
ecran[1]=XCreatePixmap( display , DefaultRootWindow(display), X , Y , DefaultDepth(display,screen) );
ecran[2]=XCreatePixmap( display , DefaultRootWindow(display), X , Y , DefaultDepth(display,screen) );
 
 /* variables globales pour la taille de la fenetre */
  
  X_fen=X;
  Y_fen=Y;

  //  icone=XCreateBitmapFromData(display,ecran[0],icone_bits,icone_width,icone_height);
  
  XCreatePixmapFromData(display,ecran[0],iconet,&icone,&icone,NULL);

  //wm_hints=XAllocWMHints();
  //class_hints=XAllocClassHint();
  //size_hints=XAllocSizeHints();
  
  XStringListToTextProperty(&nf,1,&nom_fenetre);
  XStringListToTextProperty(&ni,1,&nom_icone);
  wm_hints.initial_state=NormalState;
  wm_hints.input=True;
  wm_hints.icon_pixmap=icone;
  wm_hints.flags=StateHint|IconPixmapHint|InputHint;
  size_hints.x=posx;
  size_hints.y=posy;
  size_hints.flags=USPosition;

  XSetWMProperties(display,ecran[0],&nom_fenetre,&nom_icone,NULL,0,NULL,&wm_hints,NULL);
  XSetWMNormalHints(display,ecran[0],&size_hints);
  XSetIconName(display,ecran[0],"Super");
  //  XStoreName(display,ecran[0],"D.M Entertainment");
  XMapWindow(display,ecran[0]);
  //  v=DefaultVisual(display,screen);
  //printf("classe = %d\n",v->class);
  //printf("nb cellule : %d\n",DisplayCells(display,screen));
  //printf("%ld\n",couleur_nom("red"));
  //printf("%ld\n",couleur_composante(31,0,0));
  do 
    {
    XWindowEvent(display,ecran[0],ExposureMask,&report);
    }
  while(report.xexpose.count);
  nbfen=1;

  
  return 0;
}


/*----------------------*/

void get_GC(Window win, GC *gc)

{
  unsigned long valuemask = 0;                /* Ignore XGCvalues et prend les
					         valeurs par defaut */
  XGCValues values;

  /* creation d'un contexte graphique par defaut */
  
  *gc = XCreateGC(display, ecran[0], valuemask, &values);


  /* specification d'un background noir, puisque par defaut on fait du
     blanc sur du blanc */
  //XSetBackground(display,*gc,154);
 
  XSetForeground(display, *gc, BlackPixel(display, screen));
  
  //  XSetForeground(display, *gc, 150);
  //values.line_width=10;
  //XChangeGC(display,*gc,GCLineWidth,&values);
  //XSetForeground(display, *gc,1000);
}

int Maxx()
{
return display_width;
}

int Maxy()
{return display_height;}

void DessinerPixelC(int x,int y,unsigned long couleur)
{
XSetForeground(display,gc,couleur);
XDrawPoint(display,ecran[num_ecran],gc,x,y);
XSetForeground(display,gc,couleur_dess);
XFlush(display);
}

void DessinerPixel(int x,int y)
{
XDrawPoint(display,ecran[num_ecran],gc,x,y);
XFlush(display);
}

void DessinerSegmentC(int x,int y,int xx,int yy,unsigned long couleur)
{
XSetForeground(display,gc,couleur);
XDrawLine(display,ecran[num_ecran],gc,x,y,xx,yy);

XSetForeground(display,gc,couleur_dess);
XFlush(display);
}
void DessinerSegment(int x,int y,int xx,int yy)
{
XDrawLine(display,ecran[num_ecran],gc,x,y,xx,yy);
XFlush(display);
}

void FermerGraphique()
{ 
int i;
for (i=0;i<3;i++) XUnloadFont(display,f[i]);
XFreePixmap(display,ecran[1]);
XFreePixmap(display,ecran[2]);
XFreeGC(display,gc);
XCloseDisplay(display);
 nbfen=0;
 conecte=0;
 app=0;
}

unsigned long CouleurParNom(char * nom)
{
XParseColor(display,pal,nom,&coul);
XAllocColor(display,pal,&coul);
return coul.pixel;
}

void DessinerRectangleC(int x,int y,int l,int h,unsigned long c)
{
XSetForeground(display,gc,c);
XDrawRectangle(display,ecran[num_ecran],gc,x,y,l,h);

XSetForeground(display,gc,couleur_dess);
XFlush(display);
}
void DessinerRectangle(int x,int y,int l,int h)
{

XDrawRectangle(display,ecran[num_ecran],gc,x,y,l,h);
XFlush(display);

}
void RemplirRectangleC(int x,int y,int l,int h,unsigned long c)
{
XSetForeground(display,gc,c);
XFillRectangle(display,ecran[num_ecran],gc,x,y,l,h);
XSetForeground(display,gc,couleur_dess);
XFlush(display);
}

void DessinerArcC(int x,int y,int l,int h,int angle1,int angle2,unsigned long c)
{
XSetForeground(display,gc,c);
XDrawArc(display,ecran[num_ecran],gc,x,y,l,h,angle1*64,angle2*64);
XSetForeground(display,gc,couleur_dess);
XFlush(display);
}

void DessinerArc(int x,int y,int l,int h,int angle1,int angle2)
{

XDrawArc(display,ecran[num_ecran],gc,x,y,l,h,angle1*64,angle2*64);
XFlush(display);

}

void RemplirArcC(int x,int y,int l,int h,int angle1,int angle2,unsigned long c)
{
XSetForeground(display,gc,c);
XFillArc(display,ecran[num_ecran],gc,x,y,l,h,angle1*64,angle2*64);
XSetForeground(display,gc,couleur_dess);
XFlush(display);
}

int ToucheEnAttente()
{
if (app==1) return 1;
if (XCheckWindowEvent(display,ecran[0],KeyPressMask,&report)) {app=1;return 1;}
//app=0;
return 0;
}


KeySym Touche()
{
/* fonction bloquante */
int  buffer;
int c;
KeySym t;
if (app==0) XWindowEvent(display,ecran[0],KeyPressMask,&report);
//printf("%d\n",report.xkey.keycode);
c=XLookupString(&(report.xkey), NULL, sizeof(KeySym), &t,NULL);

//printf("%s\n",XKeysymToString(XKeycodeToKeysym(report.xkey.keycode)));
//printf("%d:%s\n",c,buffer);
//if (t==XK_Up) printf("oui\n");
//if (t==XK_Up) buffer=0x
app=0;
return t;
}

void EffacerEcran(unsigned long c)
{
  if (num_ecran==0){
XSetWindowBackground(display,ecran[num_ecran],c);
XClearWindow(display,ecran[num_ecran]);

  }
  else 
    { 
      XSetForeground(display,gc,c);
      XFillRectangle(display,ecran[num_ecran],gc,0,0,X_fen,Y_fen);
      XSetForeground(display,gc,couleur_dess);
      
  }
XFlush(display);

}

void EcrireTexteC(int x,int y,char *texte,unsigned long c,int mode)
{
if (mode<0||mode>2) return;
XSetFont(display,gc,f[mode]);
XSetForeground(display,gc,c);
XDrawString(display,ecran[num_ecran],gc,x,y,texte,strlen(texte));
XSetForeground(display,gc,couleur_dess);
XFlush(display);
}

void EcrireTexte(int x,int y,char *texte,int mode)
{
if (mode<0||mode>2) return;
XSetFont(display,gc,f[mode]);
XDrawString(display,ecran[num_ecran],gc,x,y,texte,strlen(texte));
XFlush(display);

}

void SauverImage(char * file,int x,int y,int l,int h)
{
  XEvent report;
Pixmap p1=0;
p1=XCreatePixmap( display , DefaultRootWindow(display), X_fen , Y_fen , DefaultDepth(display,screen) );
XCopyArea(display,ecran[num_ecran],p1,gc,x,y,l,h,0,0);
XpmWriteFileFromPixmap(display,file,p1,0,NULL);
if (p1) XFreePixmap(display,p1);
//XFlush(display);
while(XCheckWindowEvent(display,ecran[0],ExposureMask,&report));

while(XCheckTypedEvent(display,GraphicsExpose,&report));
  while(XCheckTypedEvent(display,NoExpose,&report));
}

void ChargerImage(char *file,int x,int y,int xx,int yy,int l,int h)
{
  XEvent report;
  Pixmap p1=0,p1mask=0;
XpmReadFileToPixmap(display,ecran[num_ecran],file,&p1,&p1mask,NULL);
XSetClipMask(display,gc,p1mask);
XSetClipOrigin(display,gc,x,y);
XCopyArea(display,p1,ecran[num_ecran],gc,xx,yy,l,h,x,y);

XSetClipMask(display,gc,None);
if (p1) XFreePixmap(display,p1);
if (p1mask) XFreePixmap(display,p1mask);

//XFlush(display);
  
   
while(XCheckWindowEvent(display,ecran[0],ExposureMask,&report));
while(XCheckTypedEvent(display,GraphicsExpose,&report));
  while(XCheckTypedEvent(display,NoExpose,&report));    
  
}

void ChargerImageFond(char *file)
{ 
XSetWindowAttributes att;
Pixmap pbackground=0,pmask=0;

XpmReadFileToPixmap(display,ecran[0],file,&pbackground,&pmask,NULL);

att.background_pixmap=pbackground;
XChangeWindowAttributes(display,ecran[0],CWBackPixmap,&att);
XClearWindow(display,ecran[0]);

if (pbackground) XFreePixmap(display,pbackground);
if (pmask) XFreePixmap(display,pmask);
XFlush(display);

}

int nsleep(long n)
{
  struct timespec t;
  t.tv_sec=0;
  t.tv_nsec=n;
  
return nanosleep(&t,NULL);

}
int TailleChaineEcran(char *t,int mode)
{
  if (mode<0||mode>2) return -1;
  else return XTextWidth(s[mode],t,strlen(t));
}
int TailleSupPolice(int mode)
{
  if (mode<0||mode>2) return -1;
  return s[mode]->ascent;
}

int TailleInfPolice(int mode)
{
  if (mode<0||mode>2) return -1;
  return s[mode]->descent;
}


void CopierZone(int src,int dst,int ox,int oy,int L,int H,int dx,int dy)
{
  XEvent report;
  XCopyArea(display,ecran[src],ecran[dst],gc,ox,oy,L,H,dx,dy);
  XFlush(display);
  while(XCheckWindowEvent(display,ecran[0],ExposureMask,&report));
  while(XCheckTypedEvent(display,GraphicsExpose,&report));
  while(XCheckTypedEvent(display,NoExpose,&report));
}


void CacherFenetre()
{
  XUnmapWindow(display,ecran[0]);
  XFlush(display);
};

void AfficherFenetre(void){XMapWindow(display,ecran[0]);XFlush(display);}


unsigned long CouleurParComposante(unsigned char r, unsigned char v,unsigned char b)
{
  XColor c;
  c.red=r;
  c.red<<=8;
  c.green=v;
  c.green<<=8;
  c.blue=b;
  c.blue<<=8;
  XAllocColor(display,DefaultColormap(display,screen),&c);
  return c.pixel;
  
}



/*
int souris(int *X,int *Y)
{
  XEvent r;
  if (XCheckWindowEvent(display,ecran[0],PointerMotionMask,&r))
    {*X=r.xmotion.x;*Y=r.xmotion.y;return 1;}
  return 0;
}
*/



void SourisPosition()
{
int x,y,rx,ry;
unsigned int etat;
Window a,b;
XQueryPointer(display, ecran[0], &a, &b, &rx, &ry, &x, &y, &etat);
_X=x;_Y=y;
}

int longueur()
{
  return XQLength(display);
}

int SourisCliquee()
{
	XEvent r;
  	if (XCheckWindowEvent(display,ecran[0],ButtonPressMask,&r))
    	{_X=r.xbutton.x;_Y=r.xbutton.y;return 1;}
  	return 0;
}

//int souris_cliquee(void)
//{
//  XEvent r;
//  return (XCheckWindowEvent(display, ecran[0], ButtonPressMask, &r)==True);
//}
