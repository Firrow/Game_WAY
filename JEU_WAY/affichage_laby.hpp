#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#define PIXEL 30
#define EXTENSION 40

using namespace sf;

typedef struct
{
    int x, y;
}Point;
void charger_textures();
//fonctions calculs
int alea(int mini, int maxi);
void matrice_laby(int matrice[][100], int tailleX, int tailleY);
void numerotation_rec(int matrice[][100], int x, int y, int w, int h);
Point case_spawn(int matrice[][100], int tailleX, int tailleY);
Point deplacement_ennemi(int matrice[][100], Point position);
bool toucher_ennemi(Point position_joueur, Point position_ennemi[]);
bool toucher_etoile(Point position_joueur, Point position_boost[]);
void reset(int matrice[][100]);

//fonctions affichages
void affichage_laby(RenderWindow *fenetre, int matrice[][100], int tailleX, int tailleY);
void affichage_perso(RenderWindow *fenetre, Point position, int num_tete);
void affichage_ennemis(RenderWindow *fenetre, Point position_ennemi);
void affichage_epee(RenderWindow *fenetre, Point position_epee);
void affichage_etoile(RenderWindow *fenetre, Point position_etoile);
void affichage_fond_noir_et_halo(RenderWindow *fenetre, Point position_perso);
void affiche_victoire(int time, int point, Sound soundmenu);
void affiche_temps(RenderWindow &fenetre, int time, int score, int posX);
void affichage_barre_de_vie(RenderWindow *fenetre, int degats, int largeur_barre_vie);
void APerduTue ();
void APerduTmp ();




