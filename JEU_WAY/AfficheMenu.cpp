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

//Structure  bouton Jade
typedef struct
{
    int x;
    int y;
    Color couleur;
}   Bouton;

//Fonction de définitions des aractéristiques d'un bouton
RectangleShape aff_bouton(Bouton b)
{
    RectangleShape Bouton(Vector2f(LARGEUR_BOUTON,HAUTEUR_BOUTON));
    Bouton.setFillColor(b.couleur);
    Bouton.setPosition(b.x,b.y);
    return Bouton;
}

//Affiche le menu
void AfficheMenu(RenderWindow *fenetre)
{
    //Définition de l'image de fond
    Texture labyrinth;
    labyrinth.loadFromFile("labyrinth.jpg");
    labyrinth.setSmooth(true);
    Sprite maze;
    maze.setTexture(labyrinth);
    maze.setScale(1.05,1.05);

    //Définition des caractéristiques des boutons
    Bouton Jouer = {LARGEUR_FENETRE/2-LARGEUR_BOUTON/2, JOUER-HAUTEUR_BOUTON/2, Color::White};
    Bouton Regle = {LARGEUR_FENETRE/2-LARGEUR_BOUTON/2, REGLE-HAUTEUR_BOUTON/2, Color::White};
    Bouton Commande = {LARGEUR_FENETRE/2-LARGEUR_BOUTON/2, COMMANDE-HAUTEUR_BOUTON/2, Color::White};
    Bouton Credit = {LARGEUR_FENETRE/2-LARGEUR_BOUTON/2, CREDIT-HAUTEUR_BOUTON/2, Color::White};

    //Appelle la fonction d'affichage de bouton et la stock
    RectangleShape bJouer = aff_bouton(Jouer);
    RectangleShape bRegle = aff_bouton(Regle);
    RectangleShape bCommande = aff_bouton(Commande);
    RectangleShape bCredit = aff_bouton(Credit);

    //Téléchargement de la police
    Font f;
    f.loadFromFile("PermanentMarker.ttf");

    //Création du texte
    Text titre, sous_titre, t1, t2, t3, t4;

    //Titre
    titre.setFont(f);
    titre.setCharacterSize(70);
    titre.setColor(Color::White);
    titre.setString("WAY");
    titre.setPosition((LARGEUR_FENETRE/2)-75,10);

    //Sous-titre
    sous_titre.setFont(f);
    sous_titre.setCharacterSize(30);
    sous_titre.setColor(Color::White);
    sous_titre.setString("Where Are You ?");
    sous_titre.setPosition((LARGEUR_FENETRE/2)-120,90);

    //Jouer
    t1.setFont(f);
    t1.setColor(Color::Black);
    t1.setString("Jouer");
    t1.setPosition((LARGEUR_FENETRE/2)-45,JOUER-HAUTEUR_BOUTON/2);

    //Regles
    t2.setFont(f);
    t2.setColor(Color::Black);
    t2.setString("Regles");
    t2.setPosition((LARGEUR_FENETRE/2)-50,REGLE-HAUTEUR_BOUTON/2);

    //Commandes
    t3.setFont(f);
    t3.setColor(Color::Black);
    t3.setString("Commandes");
    t3.setPosition((LARGEUR_FENETRE/2)-85,COMMANDE-HAUTEUR_BOUTON/2);

    //Crédits
    t4.setFont(f);
    t4.setColor(Color::Black);
    t4.setString("Credits");
    t4.setPosition(LARGEUR_FENETRE/2-55,CREDIT-HAUTEUR_BOUTON/2);

    //Dessine les éléments
    (*fenetre).draw(maze);
    (*fenetre).draw(bJouer);
    (*fenetre).draw(bRegle);
    (*fenetre).draw(bCommande);
    (*fenetre).draw(bCredit);
    (*fenetre).draw(titre);
    (*fenetre).draw(sous_titre);
    (*fenetre).draw(t1);
    (*fenetre).draw(t2);
    (*fenetre).draw(t3);
    (*fenetre).draw(t4);
}

//Affiche les différents niveaux
void AfficheNiveaux(RenderWindow * fenetre)
{

    //Définition de l'image de fond
    Texture labyrinth;
    labyrinth.loadFromFile("labyrinth.jpg");
    labyrinth.setSmooth(true);
    Sprite maze;
    maze.setTexture(labyrinth);
    maze.setScale(1.05,1.05);

    //Définition des caractéristiques des boutons
    Bouton Niveau1 = {LARGEUR_FENETRE/2-LARGEUR_BOUTON/2,NIVEAU_1-HAUTEUR_BOUTON/2, Color::White};
    Bouton Niveau2 = {LARGEUR_FENETRE/2-LARGEUR_BOUTON/2,NIVEAU_2-HAUTEUR_BOUTON/2, Color::White};
    Bouton Niveau3 = {LARGEUR_FENETRE/2-LARGEUR_BOUTON/2,NIVEAU_3-HAUTEUR_BOUTON/2, Color::White};
    Bouton Retour = {10, 10, Color::White};

    //Appelle la fonction d'affichage de bouton et la stock
    RectangleShape bNiveau1 = aff_bouton(Niveau1);
    RectangleShape bNiveau2 = aff_bouton(Niveau2);
    RectangleShape bNiveau3 = aff_bouton(Niveau3);
    RectangleShape bRetour = aff_bouton(Retour);

    //Téléchargement de la police
    Font f;
    f.loadFromFile("PermanentMarker.ttf");

    //Création du texte
    Text t1, t2, t3, retour;

    //Niveau 1
    t1.setFont(f);
    t1.setColor(Color::Black);
    t1.setString("Niveau 1");
    t1.setPosition(LARGEUR_FENETRE/2-60,NIVEAU_1-HAUTEUR_BOUTON/2);

    //Niveau 2
    t2.setFont(f);
    t2.setColor(Color::Black);
    t2.setString("Niveau 2");
    t2.setPosition(LARGEUR_FENETRE/2-60,NIVEAU_2-HAUTEUR_BOUTON/2);

    //Niveau 3
    t3.setFont(f);
    t3.setColor(Color::Black);
    t3.setString("Niveau 3");
    t3.setPosition(LARGEUR_FENETRE/2-60,NIVEAU_3-HAUTEUR_BOUTON/2);

    //Retour
    retour.setFont(f);
    retour.setColor(Color::Black);
    retour.setString("Retour");
    retour.setPosition(LARGEUR_BOUTON/4+10,HAUTEUR_BOUTON/4);

    //Dessine les éléments
    (*fenetre).draw(maze);
    (*fenetre).draw(bNiveau1);
    (*fenetre).draw(bNiveau2);
    (*fenetre).draw(bNiveau3);
    (*fenetre).draw(bRetour);
    (*fenetre).draw(t1);
    (*fenetre).draw(t2);
    (*fenetre).draw(t3);
    (*fenetre).draw(retour);

}

//Affiche les règles
void AfficheRegle(RenderWindow * fenetre)
{
    //Définition de l'image des règles
    Texture regle;
    regle.loadFromFile("Regle.png");
    regle.setSmooth(true);
    Sprite Regle;
    Regle.setTexture(regle);
    Regle.setPosition(0,50);

    //Définition des caractéristiques des boutons
    Bouton Retour = {10, 10, Color::White};
    //Appelle la fonction d'affichage de bouton et la stock
    RectangleShape bRetour = aff_bouton(Retour);

    //Téléchargement de la police
    Font f;
    f.loadFromFile("PermanentMarker.ttf");

    //Création du texte
    Text retour;

    //Retour
    retour.setFont(f);
    retour.setColor(Color::Black);
    retour.setString("Retour");
    retour.setPosition(LARGEUR_BOUTON/4+10,HAUTEUR_BOUTON/4);

    //Dessine les éléments
    (*fenetre).draw(Regle);
    (*fenetre).draw(bRetour);
    (*fenetre).draw(retour);

}

//Affiche les commandes
void AfficheCommande(RenderWindow * fenetre)
{
    //Définition de l'image de fond
    Texture labyrinth;
    labyrinth.loadFromFile("labyrinth.jpg");
    labyrinth.setSmooth(true);
    Sprite maze;
    maze.setTexture(labyrinth);
    maze.setScale(1.05,1.05);

    //Définition de l'image des copmmandes de jeu
    Texture fleche_gauche;
    fleche_gauche.loadFromFile("fleche_gauche_bas.png");
    fleche_gauche.setSmooth(true);
    Sprite gauche;
    gauche.setTexture(fleche_gauche);
    gauche.setScale(0.1,0.1);
    gauche.setPosition(290,95);

    Texture fleche_droite;
    fleche_droite.loadFromFile("fleche_droite_haut.png");
    fleche_droite.setSmooth(true);
    Sprite droite;
    droite.setTexture(fleche_droite);
    droite.rotate(90);
    droite.setScale(0.1,0.1);
    droite.setPosition(340,195);

    Texture fleche_haut;
    fleche_haut.loadFromFile("fleche_droite_haut.png");
    fleche_haut.setSmooth(true);
    Sprite haut;
    haut.setTexture(fleche_haut);
    haut.setScale(0.1,0.1);
    haut.setPosition(290,295);

    Texture fleche_bas;
    fleche_bas.loadFromFile("fleche_gauche_bas.png");
    fleche_bas.setSmooth(true);
    Sprite bas;
    bas.setTexture(fleche_bas);
    bas.rotate(270);
    bas.setScale(0.1,0.1);
    bas.setPosition(290,445);

    //Définition des caractéristiques des boutons
    Bouton Retour = {10, 10, Color::White};
    //Appelle la fonction d'affichage de bouton et la stock
    RectangleShape bRetour = aff_bouton(Retour);

    //Téléchargement de la police
    Font f;
    f.loadFromFile("PermanentMarker.ttf");

    //Création du texte
    Text t1, t2, t3, t4, retour;

    //Gauche
    t1.setFont(f);
    t1.setColor(Color::White);
    t1.setCharacterSize(20);
    t1.setString("Aller a gauche");
    t1.setPosition(350,105);

    //Droite
    t2.setFont(f);
    t2.setColor(Color::White);
    t2.setCharacterSize(20);
    t2.setString("Aller a droite");
    t2.setPosition(350,205);

    //Avant
    t3.setFont(f);
    t3.setColor(Color::White);
    t3.setCharacterSize(20);
    t3.setString("Aller en avant");
    t3.setPosition(350,305);

    //Arrière
    t4.setFont(f);
    t4.setColor(Color::White);
    t4.setCharacterSize(20);
    t4.setString("Aller en arriere");
    t4.setPosition(350,405);


    //Retour
    retour.setFont(f);
    retour.setColor(Color::Black);
    retour.setString("Retour");
    retour.setPosition(LARGEUR_BOUTON/4+10,HAUTEUR_BOUTON/4);

    //Dessine les éléments
    (*fenetre).draw(maze);
    (*fenetre).draw(gauche);
    (*fenetre).draw(droite);
    (*fenetre).draw(haut);
    (*fenetre).draw(bas);
    (*fenetre).draw(bRetour);
    (*fenetre).draw(t1);
    (*fenetre).draw(t2);
    (*fenetre).draw(t3);
    (*fenetre).draw(t4);
    (*fenetre).draw(retour);
}

//Affiche les crédits
int AfficheCredits(RenderWindow * fenetre, int y)
{
    //Téléporte l'image en dehors de l'image en bas quand elle a quittée l'écran
    if(y == -700)
    {
        y = HAUTEUR_FENETRE;
    }

    //Définition de l'image de fond
    Texture labyrinth;
    labyrinth.loadFromFile("labyrinth.jpg");
    labyrinth.setSmooth(true);
    Sprite maze;
    maze.setTexture(labyrinth);
    maze.setScale(1.05,1.05);

    //Définition de l'image des crédits
    Texture credits;
    credits.loadFromFile("Credits.png");
    credits.setSmooth(true);
    Sprite Credits;
    Credits.setTexture(credits);
    Credits.setScale(1.25,1.25);
    Credits.setPosition(LARGEUR_FENETRE/2-475/2,510);

    //Définition des caractéristiques des boutons
    Bouton Retour = {10, 10, Color::White};
    //Appelle la fonction d'affichage de bouton et la stock
    RectangleShape bRetour = aff_bouton(Retour);

    //Téléchargement de la police
    Font f;
    f.loadFromFile("PermanentMarker.ttf");

    //Création du texte
    Text retour;

    //Retour
    retour.setFont(f);
    retour.setColor(Color::Black);
    retour.setString("Retour");
    retour.setPosition(LARGEUR_BOUTON/4+10,HAUTEUR_BOUTON/4);

    //Décrémente le y de l'image de 1 pixel toutes les mili-secondes
    y --;
    Credits.setPosition(LARGEUR_FENETRE/2-382/2,y);

    //Dessine les éléments
    (*fenetre).draw(maze);
    (*fenetre).draw(Credits);
    (*fenetre).draw(bRetour);
    (*fenetre).draw(retour);

    return y;
}
