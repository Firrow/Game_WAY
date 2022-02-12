#include <SFML/Graphics.hpp>
#include <math.h>
#include <SFML/Audio.hpp>
#include "affichage_laby.hpp"

#define PIXEL 30
#define EXTENSION 33
//CONSTANTES MARC
#define TEMPS_FIN 100
#define WOUAW "wouaw.png"
#define WOUAWE "wouawe.png"
#define LAB "lab.jpg"
#define HEROS "heros.png"
#define LUNETTE "lunette.png"
//CONSTANTES MORGANE
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 500
#define HAUTEUR_BARRE 20

using namespace sf;

Texture herostexture;
Texture lunettestexture;
Texture wouaw;
Texture wouawe;
Texture labe;
Texture imagetombe;
Font font;
Texture imagesablier;
Texture mur_brique;
Texture mur_sortie;
Texture spawn;
Texture spawnEnnemi;
Texture spawnEpee;
Texture spawnEtoile;
Texture haloTex;


void charger_textures()
{
    herostexture.loadFromFile(HEROS);
    lunettestexture.loadFromFile(LUNETTE);
    wouaw.loadFromFile(WOUAW);
    wouawe.loadFromFile(WOUAWE);
    labe.setSmooth(true);
    labe.loadFromFile(LAB);
    if (!imagetombe.loadFromFile("tombe.png"))
    {
        printf("Problème de chargement de l'image tombe.png");
    }
    if (!font.loadFromFile("PermanentMarker.ttf"))
    {
        printf("Erreur de police.\n");
    }
    if (!imagesablier.loadFromFile("sablier.png"))
    {
        printf("Problème de chargement de l'image sablier.png");
    }
    //charge bloc brique mur
    if (!mur_brique.loadFromFile("bloc_decouper.jpg"))
        printf("Probleme de chargement de l'image %s !\n", "bloc_decouper.jpg");

    //charge bloc sortie
    if (!mur_sortie.loadFromFile("bloc_sortie.jpg"))
        printf("Probleme de chargement de l'image %s !\n", "bloc_sortie.jpg");


    if (!spawn.loadFromFile("spawnable.jpg"))
        printf("Probleme de chargement de l'image %s !\n", "spawnable.jpg");
    if (!spawnEnnemi.loadFromFile("ennemi.jpg"))
        printf("Probleme de chargement de l'image %s !\n", "ennemi.jpg");
    if (!spawnEpee.loadFromFile("petiteEpee.jpg"))
        printf("Probleme de chargement de l'image %s !\n", "petiteEpee.jpg");
    if (!spawnEtoile.loadFromFile("etoile.jpg"))
        printf("Probleme de chargement de l'image %s !\n", "etoile.jpg");

    // dessin du halo
    // chargement de l'image halo
    haloTex.loadFromFile("halo.jpg");

}


void reset(int matrice[][100])
{
    for (int i; i<100; i++)
    {
        for (int j; j<100; j++)
        {
            matrice[i][j] = 0;
        }
    }
}

//fonction aléatoire utilisée
int alea(int mini, int maxi)
{
    return rand()%(maxi-mini+1)+mini;
}

//case possible pour spawnage personnage et ennemis
void numerotation_rec(int matrice[][100], int x, int y, int w, int h)
{
    // s'assure que x et y sont dans les bornes de la taille du niveau
    if (x < 0 || x >= w) return;
    if (y < 0 || y >= h) return;

    //attribution case actuelle = -1 --> on peut s'y déplacer
    matrice[x][y]=-1;
    //condition reccurence direction Nord (deplacement --> x reste le meme, y=y-1)
    if(matrice[x][y-1]==0)
    {
        //dans les if, on fait appel à la fonction meme, pour numéroté la case spawnable voisine
        numerotation_rec(matrice, x, y-1, w, h);
    }
    //condition récurrence direction Est (deplacement --> y reste le meme, x=x+1)
    if(matrice[x+1][y]==0)
    {
        numerotation_rec(matrice, x+1, y, w, h);
    }
    //condition réccurence direction Sud (deplacement --> x reste le meme, y=y+1)
    if(matrice[x][y+1]==0)
    {
        numerotation_rec(matrice, x, y+1, w, h);
    }
    //condition réccurence direction Ouest (deplacement --> y reste le meme, x=x-1)
    if(matrice[x-1][y]==0)
    {
        numerotation_rec(matrice, x-1, y, w, h);
    }
}




//choix de la case ou le personnage et les ennemis vont apparaitre
Point case_spawn(int matrice[][100], int tailleX, int tailleY)
{
    Point position_depart;
    do
    {
        position_depart.x=alea(0, tailleX-1);
        position_depart.y=alea(0, tailleY-1);
    }
    while(matrice[position_depart.x][position_depart.y]!=-1);
    return position_depart;
}


//creation matrice (sans affichage)
void matrice_laby(int matrice[][100], int tailleX, int tailleY)
{
    int x, y, x_atteignable, y_atteignable;



    //tableau a double entrée ligne
    for(x=0; x<tailleX; x++)
    {
        //tableau a double entrée colonne
        for(y=0; y<tailleY; y++)
        {

            //création de murs tout autour du labyrinthe
            if (x==0 || x==tailleX-1 || y==0 || y==tailleY-1)
            {
                matrice[x][y]=1;
            }

            //creation des pilliers sur les cases paires
            if (x%2==0 && y%2==0)
            {
                matrice[x][y]=1;
                //continue;
                //création des murs entre les pilliers
                //on a EXTENSION% de chance d'avoir une extension
                int extension=alea(1,100);
                if(extension<=EXTENSION)
                {
                    //direction et nbr de case de l'extension
                    int direction=alea(1,2);
                    int nbr_murs=alea(1,2);

                    //direction horizontale
                    if(direction==1)
                    {
                        //extension de 1
                        if(nbr_murs==1)
                        {
                            //extension à droite ou à gauche selon si -1^1=-1 (gauche) ou -1^2=1 (droite)
                            matrice[x+(int)pow(-1, alea(1,2))][y] = 1;
                        }
                        //extension de 2
                        else
                        {
                            //voisin de gauche
                            matrice[x-1][y]=1;
                            //voisin de droite
                            matrice[x+1][y]=1;
                        }
                    }
                    //direction verticale
                    else
                    {
                        //extension de 1
                        if(nbr_murs==1)
                        {
                            //extension à droite ou à gauche selon si -1^2=-1 (gauche) ou =1 (droite)
                            matrice[x][y+(int)pow(-1, alea(1,2))] = 1;
                        }
                        //extension de 2
                        else
                        {
                            //voisin de gauche
                            matrice[x][y-1]=1;
                            //voisin de droite
                            matrice[x][y+1]=1;
                        }
                    }
                }
            }
        }
    }

    //Choix du mur ou la sortie sera positionnée
    int sortie_mur=alea(1,2);

    // Direction horizontal
    if(sortie_mur==1)
    {
        //choisit un x sur le haut ou le bas (pour la sortie)
        x=alea(0,1)*(tailleX-1);
        //choisit n'importe quel y qui n'est pas un pilier (pour la sortie)
        y=2*alea(0,(tailleY-1)/2)+1;

        //si on est sur mur horizontal (Aide au spawn du personnage par rapport a la position de la sortie)
        //Sur le mur du haut
        if (x==0)
        {
            // Prochaine case atteignable est la case du dessous (x+1)
            x_atteignable = 1;
        }
        //Sur le mur du bas
        else
        {
            // Prochaine case atteignable est la case du dessous (x-1)
            x_atteignable = tailleX-2;
        }
        //y reste le meme dans tous les cas
        y_atteignable = y;
    }

    //direction verticale
    else
    {
        //choisit un y sur la gauche ou sur la droite (pour la sortie)
        y=alea(0,1)*(tailleY-1);
        //choisit n'importe quel x qui n'est pas un pilier (pour la sortie)
        x=2*alea(0,(tailleX-1)/2)+1;

        //si on est sur mur vertical (Aide au spawn du personnage par rapport a la position de la sortie)
        //Sur le mur de gauche
        if (y==0)
        {
            // Prochaine case atteignable est la case de droite (y+1)
            y_atteignable = 1;
        }
        else
        {
            // Prochaine case atteignable est la case de gauche (y-1)
            y_atteignable = tailleY-2;
        }
        //x reste le meme dans tous les cas
        x_atteignable = x;
    }
    // Mise en place de la sortie
    matrice[x][y]=2;

    //numérotation de toutes les cases spawnables
    numerotation_rec(matrice, x_atteignable, y_atteignable, tailleX, tailleY);

}

//affichage de chaque case de la matrice (passer en paramètre sous le nom de type_de_bloc
//qui représente chaque valeur individuelle de la matrice)
void afficher_case(RenderWindow *fenetre, int x, int y, int type_de_bloc)
{

    Sprite bloc;
    bloc.setPosition(x*PIXEL, (y+2)*PIXEL);

    if(type_de_bloc==1)
    {
        bloc.setTexture(mur_brique);
    }

    else if(type_de_bloc==2)
    {
        bloc.setTexture(mur_sortie);
    }
    //Remplissage des case non spawnables par des briques
    else if (type_de_bloc==0)
    {
        bloc.setTexture(mur_brique);
    }
    fenetre->draw(bloc);
}

//deplacement ennemi
Point deplacement_ennemi(int matrice[][100], Point position)
{
    //définition position de déplacement
    Point p_deplacement = position;
    //choix de future position entre gauche(-1) et droite(+1)
    int new_x = position.x + pow(-1, alea(1,2));
    //choix de future position entre haut(-1) et bas(+1)
    int new_y = position.y + pow(-1, alea(1,2));
    //test si la case gauche/droite est spawnable ou non
    if (matrice[new_x][position.y]==-1 && alea(1,100)<76) //alea sert a eviter de se déplacer systematiquement en x
        p_deplacement.x = new_x;
    //test si la case haut/bas est spawnable ou non
    else if(matrice[position.x][new_y]==-1)
        p_deplacement.y = new_y;
    //retourne la nouvelle position
    return p_deplacement;
}

//affiche tout le labyrinthe
void affichage_laby(RenderWindow *fenetre, int matrice[][100], int tailleX, int tailleY)
{
    int x, y;
    for(x=0; x<=tailleX; x++)
    {
        for(y=0; y<=tailleY; y++)
        {
            //appel de la fonction qui affiche cases une par une
            afficher_case(fenetre, x, y, matrice[x][y]);
        }
    }
}

//dessin du perso
void affichage_perso(RenderWindow *fenetre, Point position, int num_tete)
{
    //toutes les tete de perso possibles
    char nom_fichiers[10][50] = {"hero_de_WAY_tete_normale.png","hero_de_WAY_touche.png","hero_de_WAY_content.png","hero_de_WAY_arriere.png","hero_de_WAY_profil_droit_content.png","hero_de_WAY_profil_droit_normal.png","hero_de_WAY_droit_touche.png","hero_de_WAY_profil_gauche_content.png","hero_de_WAY_profil_gauche_normale.png","hero_de_WAY_profil_gauche_touche.png"};
    Texture spawnPerso;
    if (!spawnPerso.loadFromFile(nom_fichiers[num_tete]))
        printf("Probleme de chargement de l'image %s !\n", nom_fichiers[num_tete]);

    Sprite spawn_perso;
    spawn_perso.setPosition(position.x*PIXEL, (position.y+2)*PIXEL);
    spawn_perso.setTexture(spawnPerso);
    fenetre->draw(spawn_perso);
}

//dessin ennemis
void affichage_ennemis(RenderWindow *fenetre, Point position_ennemi)
{

    Sprite spawn_ennemi;
    spawn_ennemi.setPosition(position_ennemi.x*PIXEL, (position_ennemi.y+2)*PIXEL);
    spawn_ennemi.setTexture(spawnEnnemi);
    fenetre->draw(spawn_ennemi);
}

//dessin epee
void affichage_epee(RenderWindow *fenetre, Point position_epee)
{

    Sprite spawn_Epee;
    spawn_Epee.setPosition(position_epee.x*PIXEL, (position_epee.y+2)*PIXEL);
    spawn_Epee.setTexture(spawnEpee);
    fenetre->draw(spawn_Epee);
}

//dessin etoiles
void affichage_etoile(RenderWindow *fenetre, Point position_etoile)
{
    Sprite spawn_Etoile;
    spawn_Etoile.setPosition(position_etoile.x*PIXEL, (position_etoile.y+2)*PIXEL);
    spawn_Etoile.setTexture(spawnEtoile);
    fenetre->draw(spawn_Etoile);
}

void affichage_barre_de_vie(RenderWindow *fenetre, int degats, int largeur_barre_vie)
{
    //CODE MORGANE AFFICHAGE BARRE VIE
        //-------------BARRE GRISE DE FOND-------------------------

        RectangleShape fond(Vector2f(largeur_barre_vie,HAUTEUR_BARRE));
        fond.setFillColor(Color(100,100,100));
        fond.setPosition(10,10);

        //-------------BARRE VERTE DE VIE -------------------------

        RectangleShape barre(Vector2f(largeur_barre_vie-degats,HAUTEUR_BARRE));
        barre.setFillColor(Color::Green);
        barre.setPosition(10,10);

        //----------------AFFICHAGE PV-----------------------------

        Text pv;
        pv.setFont(font);
        char vie[30];
        sprintf(vie,"%i / %i",largeur_barre_vie-degats, largeur_barre_vie);
        pv.setString(vie);
        pv.setCharacterSize(20);
        pv.setColor(Color::White);
        pv.setPosition(largeur_barre_vie/2-50,8);
        ////////////////////////////////////////////////////////////////


            fenetre->draw(fond); // afficher le fond gris de la barre
            fenetre->draw(barre); // afficher la partie verte de la barre qui varie en fonction du nombre de pv restant
            fenetre->draw(pv);
}

//affichage fond noir et halo
void affichage_fond_noir_et_halo(RenderWindow *fenetre, Point position_perso)
{

    //dessin halo
    Sprite halo;
    halo.setTexture(haloTex);
    //positionnement du halo par rapport a la position du personnage et à la taille de la fenetre (on soustrait l'origine
    //de la fenetre (qui est en bas a gauche pour raisons inconnues) a la position du perso - le cartouche des infos en haut)
    halo.setPosition(position_perso.x*PIXEL, fenetre->getSize().y-position_perso.y*PIXEL - 60);

    halo.setScale(2, 2);
    halo.setOrigin(halo.getLocalBounds().width / 2, halo.getLocalBounds().height / 2);

    // création de l'overlay ( = ce qui va se mettre par-dessus toute la fenêtre)
    // qui est par défaut rempli en noir
    RenderTexture overlay;

    overlay.create(fenetre->getSize().x, fenetre->getSize().y);
    // sur lequel on rajoute le halo (à la position du joueur de préférence)
    overlay.draw(halo);

    Sprite overlaySpr;
    overlaySpr.setTexture(overlay.getTexture());
    // ajout de l'image en mode multiplication pour n'afficher que ce qui est sur le
    fenetre->draw(overlaySpr, RenderStates(BlendMultiply));
}

//collision avec ennemis
bool toucher_ennemi(Point position_joueur, Point position_ennemi[])
{
    bool resultat=false;
    for (int i=0; i<3; i++)
    {
        if (position_joueur.x == position_ennemi[i].x && position_joueur.y == position_ennemi[i].y)
            resultat = true;
    }
    return resultat;
}

//Toucher etoile
bool toucher_etoile(Point position_joueur, Point position_boost[])
{
    bool resultat=false;
    for (int i=0; i<8; i++)
    {
        if (position_joueur.x == position_boost[i].x && position_joueur.y == position_boost[i].y)
        {
            //quand étoile touché, sprite mise en dehors fenetre
            position_boost[i].x = -2;
            position_boost[i].y = -2;
            resultat = true;
        }
    }
    return resultat;
}

void affiche_temps(RenderWindow &fenetre, int time, int score, int posX)
{
    Text timer;
    timer.setPosition(posX, 8);
    timer.setFont(font);// --> choix de la police à utiliser

    char c[50];
    sprintf(c,"Temps : %i /%d    Score : %i / 230", TEMPS_FIN-time, TEMPS_FIN, score); // donne le timer
    timer.setString(c);//--> choix de la chaîne de caractères à afficher
    timer.setColor(Color::White);
    timer.setCharacterSize(20);

    fenetre.draw(timer);
}

//ECRAN GAGNER
void affiche_victoire(int time, int point, Sound soundmenu ) //sprite pour sortie
{

    RenderWindow fenetre(VideoMode(800,600),"GAGNE !!!");

    &soundmenu.stop;

        SoundBuffer sonVictoire;
    if (!sonVictoire.loadFromFile("Final Fantasy Victoire.wav"))
        printf("probleme de son victoire\n");
    Sound soundV;
    soundV.setBuffer(sonVictoire);
    soundV.play();

    Text timer, score, fin, espace;

    //Message recommancer
    espace.setPosition(300,135);
    espace.setFont(font);
    espace.setString("Pour recommencer utiliser la touche espace");
    espace.setColor(Color::White);
    espace.setCharacterSize(10);

    //affichage score
    score.setPosition(150,170);
    score.setFont(font);
    char sc[30];
    sprintf(sc,"Score : " "%i", point); //donne le score
    score.setString(sc);
    score.setColor(Color::White);
    score.setCharacterSize(40);

    timer.setPosition(400,170);
    timer.setFont(font);// --> choix de la police à utiliser

    char c[30];
    sprintf(c,"Temps : " "%i /%d", TEMPS_FIN-time, TEMPS_FIN); // donne le timer
    timer.setString(c);//--> choix de la chaîne de caractères à afficher
    timer.setColor(Color::White);
    timer.setCharacterSize(40);

    int x=450, y=100;
    RectangleShape rect(Vector2f(x,y));
    rect.setFillColor(Color::Black); // case pour la victoire
    rect.setPosition(175,50);


    fin.setPosition(220,75);
    fin.setFont(font);
    fin.setString("Vous avez gagné!");//message gagner
    fin.setColor(Color(150,50,255));
    fin.setCharacterSize(45);



    Sprite heros;
    heros.setTexture(herostexture);
    heros.setPosition(375,450);


    Sprite lunette;
    lunette.setTexture(lunettestexture);
    lunette.setPosition(378,480);

    Sprite feu;
    feu.setTexture(wouaw);
    feu.setPosition(100,250);

    Sprite f2;
    f2.setTexture(wouawe);
    f2.setPosition(500,250);

    Sprite lab;
    lab.setTexture(labe);
    lab.setPosition(0,0);


    while(fenetre.isOpen())
    {
        Event event;
        while(fenetre.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                fenetre.close();
                break;
            case Event::KeyPressed:
                if(event.key.code == Keyboard::Space)
                    fenetre.close();
                break;
            default:
                break;
            }
        }

        fenetre.clear();
        fenetre.draw(lab);
        fenetre.draw(score);
        fenetre.draw(timer);
        fenetre.draw(rect);
        fenetre.draw(fin);
        fenetre.draw(heros);
        fenetre.draw(lunette);
        fenetre.draw(feu);
        fenetre.draw(f2);
        fenetre.draw(espace);
        fenetre.display();

    }
}


void APerduTue () // Lorsque le personnage est tué
{
    RenderWindow fenetre(VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE),"PERDU !");
    //---------------TITRE------------------------


    Text titre;
    titre.setFont(font);
    titre.setString("Vous avez été tué(e).\n");
    titre.setCharacterSize(50);
    titre.setColor(Color::White);
    titre.setPosition(150,50);

    //----------------IMAGE------------------------

    Sprite tombe;
    tombe.setTexture(imagetombe);
    tombe.setScale(0.5,0.5);
    tombe.setPosition(235,120);

    //------------------SON------------------------

    SoundBuffer son1;
    if (!son1.loadFromFile("rire.wav"))
        printf("probleme de rire\n");
    Sound sound1;
    sound1.setBuffer(son1);
    sound1.play();

    //---------INSTRUCTION MENU--------------------

    Text instruction;
    instruction.setFont(font);
    instruction.setString("Appuyer sur la touche espace pour retourner au menu.\n");
    instruction.setCharacterSize(24);
    instruction.setColor(Color::White);
    instruction.setPosition(80,400);

    //-----------------AFFICHAGE-------------------

    while(fenetre.isOpen())
    {
        Event event;
        while(fenetre.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                fenetre.close();
                break;
            case Event::KeyPressed:
                if(event.key.code == Keyboard::Space)
                    fenetre.close();
                break;
            default:
                break;
            }
        }

        fenetre.clear();
        fenetre.draw(titre);
        fenetre.draw(tombe);
        fenetre.draw(instruction);
        fenetre.display();

    }
}

void APerduTmp () // Lorsque le personnage n'a plus de temps
{
    RenderWindow fenetre(VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE),"PERDU !");
    //---------------TITRE------------------------

    Text titre;
    titre.setFont(font);
    titre.setString("Time Out, vous avez échoué.\n");
    titre.setCharacterSize(50);
    titre.setColor(Color::White);
    titre.setPosition(80,50);

    //----------------IMAGE------------------------

    Sprite sablier;
    sablier.setTexture(imagesablier);
    sablier.setPosition(320,120);

    //------------------SON------------------------

    SoundBuffer son1;
    if (!son1.loadFromFile("coucou.wav"))
        printf("probleme de coucou\n");
    Sound sound1;
    sound1.setBuffer(son1);
    sound1.play();

    //---------INSTRUCTION MENU--------------------

    Text instruction;
    instruction.setFont(font);
    instruction.setString("Appuyer sur la touche espace pour retourner au menu.\n");
    instruction.setCharacterSize(24);
    instruction.setColor(Color::White);
    instruction.setPosition(80,400);

    //--------------AFFICHAGE----------------------


    while(fenetre.isOpen())
    {
        Event event;
        while(fenetre.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                fenetre.close();
                break;
            case Event::KeyPressed:
                if(event.key.code == Keyboard::Space)
                    fenetre.close();
                break;
            default:
                break;
            }
        }

        fenetre.clear();
        fenetre.draw(titre);
        fenetre.draw(sablier);
        fenetre.draw(instruction);
        fenetre.display();

    }
}
