///HEADER PRINCIPAL DU JEU POSSEDANT TOUTES LES FONCTIONS (SAUF LES SOUS-FONCTIONS COMME PAR EXEMPLE LES QUATRE MOUVEMENT LORS DE LA SELECTION DU PERSONNAGE

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "CodeTriche.h"
#include "ChoixPerso.h"
#include "DuringFight.h"
#include "Timer.h"

//============== VARIABLES DE DECOR ================

	POINT Img; //Point qui est tout en haut à gauche pour afficher les images qui prennent tout l'écran comme le Menu et le Choix des persos
    POINT Nom1, Nom2; //Points qui va faire afficher les noms des joueurs
    POINT Choix; //Touche où le joueur va appuyer
    POINT hg;
    POINT KO; //Point qui va permettre d'afficher le K.O lorsque qu'un joueur a gagné
    char AffichageGagnant[200]; //Chaîne de caractère, le texte qui va être écrit quand un joueur aura gagné

//============== VARIABLES DE NOMS ===============

	char NomJ1[100];
	char NomJ2[100];

//============== VARIABLES SDL ===============

    SDL_Event event; //Création d'un évènement

//=========================================

#include "ORDI.h" //On l'inclut ici car event doit être déclaré pour l'utiliser

void MenuPrincipal() //Affichage du menu principal
{
	char *MenuPrincipal = "Data/MenuPrincipal"; //Définit le nom de l'image
	RecuperationCode(); //On récupère le code
	hg.x = 0; hg.y = 680; //Coordonnées du point en haut à gauche
	affiche_image(MenuPrincipal, hg, 100, 100); //On affiche le menu principal
	while(BarreSelec == false) //Tant que le personnage n'est pas sélectionné
    {
        SDL_PollEvent(&event);
            switch(event.type)
            {
                case(SDL_KEYDOWN): //Si touche espace appuyé

                    switch(event.key.keysym.sym)
                    {
                        case(SDLK_s):
                          BarreSelec = true;
                            SDL_WaitEvent(&event);
                            break;

						case(SDLK_ESCAPE):
							exit(0);
							break;
					}

                    break;

            }
    }
}

void ChoixPerso() //Affichage du choix des personnages
{
    H1.x = 472; H1.y = 333; H2.x = 680; H2.y = 340; //Initialisation des points pour faire le carré qui indique qu'on a sélectionné un tel (Par défaut le personnage noir)
    G1.x = 472; G1.y = 125; G2.x = 480; G2.y = 340;
    D1.x = 472; D1.y = 125; D2.x = 680; D2.y = 132;
    B1.x = 672; B1.y = 125; B2.x = 680; B2.y = 340;
    Img.x = 0; Img.y = 680;
    Choix = get_arrow();
	affiche_image("Data/MenuPerso", Img, WIDTH, HEIGHT); //On affiche le menu
    draw_fill_rectangle(H1,H2,cyan); //On dessine le rectangle pour dire qu'on a sélectionné un tel
    draw_fill_rectangle(G1,G2,cyan);
    draw_fill_rectangle(D1,D2,cyan);
    draw_fill_rectangle(B1,B2,cyan);

    while(PersoPris == false) //Tant que le personnage n'est pas sélectionné
    {
        Choix = get_arrow(); //Choix va prendre quelle flèche on va cliquer
        MouvementChoix();

        SDL_PollEvent(&event);
            switch(event.type)
            {
                case(SDL_KEYDOWN): //Si touche espace appuyé
                    switch(event.key.keysym.sym)
                    {
                        case(SDLK_SPACE):
                            PersoPris = true; //On a pris le personnage
                            SDL_WaitEvent(&event);
                            break;
                    }
            }
    }

    if(DonutSelec == true) //Si Donut a été sélectionné
    {
        sprintf(NomJ1, "%s", "DONUT"); //Le nom du j1 affiché sera Donut
        sprintf(NomJ2, "%s", "TAVUK"); //Et donc le J2, l'autre, Tavuk
    }
	else //Si Tavuk a été sélectionné
	{
		sprintf(NomJ1, "%s", "TAVUK"); //Vice-Versa
        sprintf(NomJ2, "%s", "DONUT");
	}
}

void InitVies() //Initialisation des barres de vie et des barres de "dégâts"
{
    fill_screen(noir);
	Nom1.x = 20; Nom1.y = 629;
	Nom2.x = 1150; Nom2.y = 629;
	Vie1A.x = 20; Vie1A.y = 660;
	Vie1B.x = 600; Vie1B.y = 630;
	Vie2A.x = 1340; Vie2A.y = 660;
	Vie2B.x = 760; Vie2B.y = 630;
	draw_fill_rectangle(Vie1A, Vie1B, 0xffd642); //On dessine la barre de vie du joueur 1
	draw_fill_rectangle(Vie2A, Vie2B, 0xffd642); //On dessine la barre de vie du joueur 2
	Vie1Retirebg.x = 600; Vie1Retirebg.y = 630;
	Vie1Retirehd.x = 600; Vie1Retirehd.y = 660;
	Vie2Retirebg.x = 760; Vie2Retirebg.y = 630;
	Vie2Retirehd.x = 760; Vie2Retirehd.y = 660;
	KO.x = 400; KO.y = 300; //Points qui initialise la position du texte quand un joueur sera K.O
    aff_pol(NomJ1,40,Nom1,blanc);
	aff_pol(NomJ2,40,Nom2,blanc);
}

void Jeu() //Le déroulement du jeu
{
    Perso.x = 30; Perso.y = 413;                //Initialisation des points
    CacheCoup.x = 400; CacheCoup.y = 0;
    Enemy.x = 1200; Enemy.y = 413;
    CacheCoupEnnemi.x = 1500; CacheCoupEnnemi.y = 0;
    if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Fixe", Enemy, WIDTH, HEIGHT); affiche_image("Data/Player/Donut/Joueur/Fixe", Perso, WIDTH, HEIGHT);} //SI Bruno sélectionné, on affiche l'ennemi Tavuk et le joueur Bruno, dans leurs positions de "non-action"
	if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Fixe", Perso, WIDTH, HEIGHT); affiche_image("Data/Player/Donut/Joueur/Fixe", Enemy, WIDTH, HEIGHT);} //Vice-Versa
	Rapprochement();
	LancementChrono();

	while((Vie2Retirebg.x < Vie2A.x) && (Vie1Retirebg.x > Vie1A.x) && (Temps > 0)) //Tant que le joueur 2 et le joueur 1 sont vivants et que le chrono n'est pas à 0
	{
		ORDI();
		printf("\n");
		Chrono(); //On met à jour le chrono
        printf("\n");
        Droite = false; Gauche = false;
        printf("\n");

        SDL_PollEvent(&event);
            switch(event.type)
            {
                case(SDL_KEYDOWN): //Si touche appuyé
                    switch(event.key.keysym.sym)
                    {
                    case(SDLK_SPACE): //Si c'est la touche espace
						//Audio("Data/Sons/Punch.wav");
                        CoupPoing(); //On met un coup de poing donc on appelle la fonction concernée
                        SDL_WaitEvent(&event); //On évite la répétition de l'évent (Donc coup sans rien faire)
                        break; //On casse la boucle

                    case(SDLK_x): //Si c'est la touche X
                        CoupPied(); //On met un coup de pied donc on appelle la fonction concernée
                        SDL_WaitEvent(&event);
                        break;

                    case(SDLK_LEFT):
                        Gauche = true;
                        Marcher();
                        SDL_WaitEvent(&event);
                        break;

                    case(SDLK_RIGHT):
                        Droite = true;
                        Marcher();
                        SDL_WaitEvent(&event);
                        break;

                    case(SDLK_ESCAPE):
                        exit(0);
                    }
            }
	}

	if(TempsFini == true) //Si le comabt s'est terminé car le chrono a été à 0
	{
		QuiALePlusDeVie(); //On va appeller la fonction qui va calculer quel joueur à le plus de vie

		if(J1Gagne == true) //Si J1 a gagné
		{
			sprintf(AffichageGagnant, "KO !!   %s WIN !", NomJ1); //Comme le texte est variable selon le perso choisi, on écrit "K.O [NOM DU JOUEUR] etc.." dans la chaîne AffichageGagnant
			aff_pol(AffichageGagnant, 70, KO, 0xffd642); //On écrit le texte "AffichageGagnant" avec du coup le nom du joueur du J1
		}

		if(J2Gagne == true) //Si J2 gagne
		{
			sprintf(AffichageGagnant, "KO !!   %s WIN !", NomJ2); //Idem pour J1
			aff_pol(AffichageGagnant, 70, KO, 0xffd642);
		}

		if(DoubleKO == true) //Si les deux joueurs avaient la même vie (Très rare)
		{
			aff_pol("DOUBLE KO !!", 70, KO, 0xffd642);
		}
	}
	else //Si ce n'est pas le temps à 0 qui a signifié la fin du combat, c'est que c'est un des deux joueurs qui a fini à K.O avant la fin du décompte
	{
		if(Vie2A.x <= Vie2Retirebg.x) //Si le joueur 2 n'a plus de vie, donc J1 gagne
		{
			sprintf(AffichageGagnant, "KO !!   %s WIN !", NomJ1); //Comme le texte est variable selon le perso choisi, on écrit "K.O [NOM DU JOUEUR] etc.." dans la chaîne AffichageGagnant
			aff_pol(AffichageGagnant, 70, KO, 0xffd642); //On écrit le texte "AffichageGagnant" avec du coup le nom du joueur du J1
		}
		else //Si J2 Gagne
		{
			sprintf(AffichageGagnant, "KO !!   %s WIN !", NomJ2); //Idem pour J1
			aff_pol(AffichageGagnant, 70, KO, 0xffd642);
		}
	}

	wait_escape();
}
