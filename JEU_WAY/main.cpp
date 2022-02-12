#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstring>

#define PIXEL 30
#define EXTENSION 40
#include "affichage_laby.hpp"
#define PAUSE 20
//CONSTANTES MORGANE
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 500
#define HAUTEUR_BARRE 20
//CONSTANTES JADE
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
#define PAUSE_CREDIT 15
#include "AfficheMenu.hpp"
//CONSTANTE MARC
#define TEMPS_FIN 100

using namespace sf;

int play(int choix_niveau, Sound soundmenu);

int main()
{
    bool menu_principal = true, menu_niveau = false, menu_regle = false, menu_commande = false, menu_credit = false;
    int y_credit = HAUTEUR_FENETRE, jouer_a_un_level = 0;

    RenderWindow ecranmenu(VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "WAY ?");

    SoundBuffer menuson;


    if (!menuson.loadFromFile("Creepy_Clown_Symphony_-_myuu.wav"))
        printf("Erreur");
    Sound soundmenu;
    soundmenu.setBuffer(menuson);
    soundmenu.setVolume(20);
    soundmenu.play();
    soundmenu.setLoop(true);


    while(ecranmenu.isOpen())
    {
        Event event;
        while(ecranmenu.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                ecranmenu.close();
            case Event::MouseButtonPressed:
                if(event.mouseButton.button == Mouse::Left)
                {
                    if(event.mouseButton.x >= BOUTON_X-LARGEUR_BOUTON/2
                            && event.mouseButton.x <= BOUTON_X+LARGEUR_BOUTON+LARGEUR_BOUTON/2
                            && event.mouseButton.y >= JOUER-HAUTEUR_BOUTON/2
                            && event.mouseButton.y <= JOUER+HAUTEUR_BOUTON/2 && menu_principal)
                    {
                        menu_principal = false;
                        menu_niveau = true;
                    }
                    if(event.mouseButton.x >= BOUTON_X-LARGEUR_BOUTON/2
                            && event.mouseButton.x <= BOUTON_X+LARGEUR_BOUTON+LARGEUR_BOUTON/2
                            && event.mouseButton.y >= NIVEAU_1-HAUTEUR_BOUTON/2
                            && event.mouseButton.y <= NIVEAU_1+HAUTEUR_BOUTON/2 && menu_niveau)
                    {
                        menu_niveau = false;
                        menu_principal = true;
                        jouer_a_un_level = 1;
                    }
                    if(event.mouseButton.x >= BOUTON_X-LARGEUR_BOUTON/2
                            && event.mouseButton.x <= BOUTON_X+LARGEUR_BOUTON+LARGEUR_BOUTON/2
                            && event.mouseButton.y >= NIVEAU_2-HAUTEUR_BOUTON/2
                            && event.mouseButton.y <= NIVEAU_2+HAUTEUR_BOUTON/2 && menu_niveau)
                    {
                        menu_niveau = false;
                        menu_principal = true;
                        jouer_a_un_level = 2;
                    }
                    if(event.mouseButton.x >= BOUTON_X-LARGEUR_BOUTON/2
                            && event.mouseButton.x <= BOUTON_X+LARGEUR_BOUTON+LARGEUR_BOUTON/2
                            && event.mouseButton.y >= NIVEAU_3-HAUTEUR_BOUTON/2
                            && event.mouseButton.y <= NIVEAU_3+HAUTEUR_BOUTON/2 && menu_niveau)
                    {
                        menu_niveau = false;
                        menu_principal = true;
                        jouer_a_un_level = 3;
                    }
                    if(event.mouseButton.x >= BOUTON_X-LARGEUR_BOUTON/2
                            && event.mouseButton.x <= BOUTON_X+LARGEUR_BOUTON+LARGEUR_BOUTON/2
                            && event.mouseButton.y >= REGLE-HAUTEUR_BOUTON/2
                            && event.mouseButton.y <= REGLE+HAUTEUR_BOUTON/2 && menu_principal)
                    {
                        menu_principal = false;
                        menu_regle = true;
                    }
                    if(event.mouseButton.x >= BOUTON_X-LARGEUR_BOUTON/2
                            && event.mouseButton.x <= BOUTON_X+LARGEUR_BOUTON+LARGEUR_BOUTON/2
                            && event.mouseButton.y >= COMMANDE-HAUTEUR_BOUTON/2
                            && event.mouseButton.y <= COMMANDE+HAUTEUR_BOUTON/2 && menu_principal)
                    {
                        menu_principal = false;
                        menu_commande = true;
                    }
                    if(event.mouseButton.x >= BOUTON_X-LARGEUR_BOUTON/2
                            && event.mouseButton.x <= BOUTON_X+LARGEUR_BOUTON+LARGEUR_BOUTON/2
                            && event.mouseButton.y >= CREDIT-HAUTEUR_BOUTON/2
                            && event.mouseButton.y <= CREDIT+HAUTEUR_BOUTON/2 && menu_principal)
                    {
                        menu_principal = false;
                        menu_credit = true;
                    }
                    if(event.mouseButton.x >= 10
                            && event.mouseButton.x <= 10+LARGEUR_BOUTON
                            && event.mouseButton.y >= 10
                            && event.mouseButton.y <= 10+HAUTEUR_BOUTON && (menu_niveau || menu_regle || menu_commande || menu_credit))
                    {
                        // reset de toutes les valeurs pour s'assurer de ne pas avoir deux niveaux qui se super-posent
                        menu_niveau = false;
                        menu_regle = false;
                        menu_commande = false;
                        menu_credit = false;
                        menu_principal = true;
                    }
                }
            case Event::KeyPressed:
                if(menu_niveau)
                {
                    if(event.key.code == Keyboard::K)
                    {
                        menu_niveau = false;
                        menu_principal = true;
                    }
                }
            default:
                break;
            }
        }

        // Affichage
        ecranmenu.clear();
        if(menu_principal)
        {
            AfficheMenu(&ecranmenu);
        }
        else if (menu_niveau)
        {
            AfficheNiveaux(&ecranmenu);
        }
        else if(menu_regle)
        {
            AfficheRegle(&ecranmenu);
        }
        else if(menu_commande)
        {
            AfficheCommande(&ecranmenu);
        }
        else if(menu_credit)
        {
            y_credit = AfficheCredits(&ecranmenu, y_credit);
        }
        ecranmenu.display();
        sleep(milliseconds(PAUSE_CREDIT));

        if (jouer_a_un_level!=0)
        {
            play(jouer_a_un_level, soundmenu);
            jouer_a_un_level = 0;
        }
    }

    return 0;
}



//fonction jeu = equivalent d'un main
int play(int choix_niveau, Sound soundmenu)
{
    charger_textures();
    srand(time(NULL));
    //timer Marc
    Clock clok ; //avant le while isopen
    Time temps = clok.getElapsedTime() ;
    int timer = temps.asSeconds(); //VARIABLE A REMPLIR


    //INITIALISATION LABYRINTHE ENTIER
//différentes matrices possible en fonction niveau
    int nbr_ligne, nbr_colonne;
    int matrice[100][100];

    //remet la matrice a zero (où on veut remettre a zero, la valeur qu'on veut mettre, sizeof donne la taille de la matrice)
    memset(matrice, 0, sizeof(matrice));
    int nbr_ennemi;
    int nbr_etoile;
    int num_tete=0;
    int largeur_barre_vie;
    //DEGATS INITIAUX
    int degats=0;
    //Tuer ennemi
    bool invu=false;
    //Victoire ?
    bool victoire=false;
    //score
    int point=0;
    //création positions
    Point position_perso, position_ennemi[3], position_epee, position_etoile[8];

//en fonction choix du niveaux
    switch (choix_niveau)
    {
    case 1:
        nbr_ligne=19;
        nbr_colonne=19;
        largeur_barre_vie = 200 ;
        break;
    case 2:
        nbr_ligne=23;
        nbr_colonne=23;
        largeur_barre_vie = 300;
        break;
    case 3:
        nbr_ligne=21;
        nbr_colonne=35;
        largeur_barre_vie = 500;
        break;
    default:
        nbr_ligne=19;
        nbr_colonne=19;
        largeur_barre_vie = 200 ;
        break;
    }

    reset(matrice);

    RenderWindow fenetre(VideoMode(nbr_colonne*PIXEL, (nbr_ligne+2)*PIXEL), "Play !");
    matrice_laby(matrice, nbr_colonne, nbr_ligne);

    //spawn perso
    position_perso = case_spawn(matrice, nbr_colonne, nbr_ligne);
    position_epee = case_spawn(matrice, nbr_colonne, nbr_ligne);


    for(nbr_ennemi=0; nbr_ennemi<3; nbr_ennemi++)
    {
        position_ennemi[nbr_ennemi] = case_spawn(matrice, nbr_colonne, nbr_ligne);
    }

    for(nbr_etoile=0; nbr_etoile<8; nbr_etoile++)
    {
        position_etoile[nbr_etoile] = case_spawn(matrice, nbr_colonne, nbr_ligne);
    }

    fenetre.setFramerateLimit(5);

    while(fenetre.isOpen())
    {
        temps = clok.getElapsedTime() ;
        timer = temps.asSeconds();

        Event event;
        while(fenetre.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                fenetre.close();
                break;
            case Event::KeyPressed:
                //Déplacement personnage
                switch(event.key.code)
                {
                case Keyboard::Up:
                    //si la case est une case spawnable ou que la case est la sortie
                    if(matrice[position_perso.x][position_perso.y-1]==-1 || matrice[position_perso.x][position_perso.y-1]==2)
                    {
                        num_tete=3;
                        position_perso.y-=1;
                    }
                    break;
                case Keyboard::Down:
                    if(matrice[position_perso.x][position_perso.y+1]==-1 || matrice[position_perso.x][position_perso.y+1]==2)
                    {
                        num_tete=0;
                        position_perso.y+=1;
                    }
                    break;
                case Keyboard::Right:
                    if(matrice[position_perso.x+1][position_perso.y]==-1 || matrice[position_perso.x+1][position_perso.y]==2)
                    {
                        num_tete=5;
                        position_perso.x+=1;
                    }
                    break;
                case Keyboard::Left:
                    if(matrice[position_perso.x-1][position_perso.y]==-1 || matrice[position_perso.x-1][position_perso.y]==2)
                    {
                        num_tete=8;
                        position_perso.x-=1;
                    }
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }

        if(matrice[position_perso.x][position_perso.y]==2)
        {
            victoire=true;
            fenetre.close();
        }
        if(degats==largeur_barre_vie)
        {
            fenetre.close();
            APerduTue();
        }

        //collision epee
        if(position_perso.x == position_epee.x && position_perso.y == position_epee.y)
        {
            position_epee.x=-2;
            position_epee.y=-2;
            num_tete=2;

            invu=true;
        }

        //collision ou non ? Si oui avec epee ou sans ?
        for (int i=0; i<3; i++)
        {
            if (position_perso.x == position_ennemi[i].x && position_perso.y == position_ennemi[i].y)
            {
                if(invu)
                {
                    position_ennemi[i].x=-2;
                    position_ennemi[i].y=-2;
                    num_tete=2;
                    point+=50;
                }
                else
                {
                    degats+=50;
                    num_tete=1;
                }
            }
        }
        //collision ou non ?
        if(toucher_etoile(position_perso, position_etoile))
        {
            point+=10;
            num_tete=2;
        }

        for(nbr_ennemi=0; nbr_ennemi<3; nbr_ennemi++)
        {
            position_ennemi[nbr_ennemi] = deplacement_ennemi(matrice, position_ennemi[nbr_ennemi]);
        }

        fenetre.clear();


        // Affichages laby + perso + ennemis + epee + etoiles
        affichage_laby(&fenetre, matrice, nbr_colonne, nbr_ligne);


        if (timer==TEMPS_FIN)
        {
            fenetre.close();
            APerduTmp ();
        }


        affichage_perso(&fenetre, position_perso, num_tete);
        affichage_epee(&fenetre, position_epee);
        for(nbr_ennemi=0; nbr_ennemi<3; nbr_ennemi++)
        {
            affichage_ennemis(&fenetre, position_ennemi[nbr_ennemi]);
        }

        for(nbr_etoile=0; nbr_etoile<8; nbr_etoile++)
        {
            affichage_etoile(&fenetre, position_etoile[nbr_etoile]);
        }

        affichage_fond_noir_et_halo(&fenetre, position_perso);        //affichage fond noir + halo

        affichage_barre_de_vie(&fenetre, degats, largeur_barre_vie);
        affiche_temps(fenetre, timer, point, largeur_barre_vie+20);

        fenetre.display();
    }

    if(victoire)
    {
        fenetre.close();
        affiche_victoire(timer, point, soundmenu);
    }

    return 0;
}
