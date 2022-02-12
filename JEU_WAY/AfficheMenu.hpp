#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define HAUTEUR_FENETRE 500
#define LARGEUR_FENETRE 800
#define HAUTEUR_BOUTON 40
#define LARGEUR_BOUTON 200
#define BOUTON_X 250
#define NIVEAU_1 125
#define NIVEAU_2 250
#define NIVEAU_3 375
#define JOUER 175
#define REGLE 250
#define COMMANDE 325
#define CREDIT 400

using namespace sf;

void AfficheMenu(RenderWindow * fenetre);
void AfficheNiveaux(RenderWindow * fenetre);
void AfficheRegle(RenderWindow * fenetre);//code jade
void AfficheCommande(RenderWindow * fenetre);
int AfficheCredits(RenderWindow * fenetre, int y);
