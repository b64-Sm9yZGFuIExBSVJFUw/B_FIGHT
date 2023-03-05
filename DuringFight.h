///AUTRE HEADER DU JEU INCULANT LES SOUS-FONCTIONS DE LA FONCTION JEU (PENDANT LE COMBAT)

//=============== VARIABLES DE DECOR ===================

    POINT Perso; //Points pour afficher et supprimer le personnage
    POINT CacheCoup; //Point qui va servir à dessiner le rectangle qui va effacer l'image lors d'un coup de Donut qui "dépasse"
    POINT CacheCoupEnnemi; //Idem mais pour l'ennemi
    POINT Enemy; //Points identiques sauf que c'est pour l'ennemi
    POINT Vie1A, Vie1B; //Points qui vont servir pour faire la barre de vie du J1
	POINT Vie2A, Vie2B; //Points qui vont servir pour faire la barre de vie du J2
	POINT Vie1Retirebg, Vie1Retirehd; //Points qui vont servir pour faire la barre rouge sur la vie (Dégâts) du J1
	POINT Vie2Retirebg, Vie2Retirehd; //Points qui vont servir pour faire la barre rouge sur la vie (Dégâts) du J2

//=============== VARIABLES DU JOUEUR =================

	int Attaque = 0; //Points d'attaque
	int VaFrapper = 0;
    bool Droite = false; //True si le personnage marche vers la droite
    bool Gauche = false; //True si le personnage marche vers la gauche
    bool J1Gagne = false; //True si le J1 a plus de vie quand le chrono est à 0 donc gagne
    bool J2Gagne = false; //Idem pour J2
	bool DoubleKO = false; //Si le compte à rebours est à 0 et que les deux joueurs ont la même vie, il y a double K.O et la variable passe à true

//======================================================


void BoboJ2(int ViePerdue) //Quand le joueur 2 perd de la vie
{
	int i = 0; //i va servir pour incrémenter la boucle pour chaque tour de boucle, 1 pixel de rouge apparait, pour faire une sorte d'animation de vie qui descend

	while(i <= ViePerdue)
	{
		Vie2Retirebg.x++; //Donc à chaque tour, 1 pixel de rouge en plus et "en plus" car la vie descend vers la droite pour le J2
		draw_fill_rectangle(Vie2Retirehd, Vie2Retirebg,0x990d0d); //On dessine donc le nouveau pixel apparu
		i++; //Evidemment, on incrémente à chaque tour
		if(Vie2Retirebg.x >= 1340) //Si la vie retirée au total est supérieure ou égale à la vie entière, alors toute la barre est rouge, donc il est mort
		{
			Vie2Retirebg.x = 1340; //Alors on fait en sorte que toute la barre soit rouge et ne dépasse pas
			break; //Et on casse la boucle du while
		}
	}
}

void BoboJ1(int VieQuilPerd) //Quand le joueur 1 perd de la vie
{
	int i = 0; //i va servir pour incrémenter la boucle pour chaque tour de boucle, 1 pixel de rouge apparait, pour faire une sorte d'animation de vie qui descend

	while(i <= VieQuilPerd)
	{
		Vie1Retirebg.x--; //Donc à chaque tour, 1 pixel de rouge en plus et "en moins" car la vie descend vers la gauche pour le J1
		draw_fill_rectangle(Vie1Retirehd, Vie1Retirebg,0x990d0d); //On dessine donc le nouveau pixel apparu
		i++; //Evidemment, on incrémente à chaque tour
		if(Vie1Retirebg.x <= 20) //Si la vie retirée au total est inférieure ou égale à la vie entière, alors toute la barre est rouge, donc il est mort
		{
			Vie1Retirebg.x = 20; //Alors on fait en sorte que toute la barre soit rouge et ne dépasse pas
			break; //Et on casse la boucle du while
		}
	}
}


void Marcher()
{
    if(Droite == true) //Si c'est vers la droite
    {
        Perso.x++; //Il avance, donc on augmente les x de sa position
        CacheCoup.x++;
    }
    if(Gauche == true) //Si c'est vers la gauche
    {
        Perso.x--; //Il recule, donc on diminue les x de sa position
        CacheCoup.x--;
    }
    if(DonutSelec == true){affiche_image("Data/Player/Donut/Joueur/Run", Perso, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
    if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Run", Perso, WIDTH, HEIGHT);}
    affiche_all();

    if(Droite == true) //Si vers droite
    {
        Perso.x++; //Il avance, donc on augmente les x de sa position
        CacheCoup.x++;
    }
    if(Gauche == true) //Si vers gauche
    {
        Perso.x--; //Il recule, donc on diminue les x de sa position
        CacheCoup.x--;
    }

    if(DonutSelec == true){affiche_image("Data/Player/Donut/Joueur/Run2", Perso, WIDTH, HEIGHT);}
    if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Run2", Perso, WIDTH, HEIGHT);}
    affiche_all();
    if(DonutSelec == true){affiche_image("Data/Player/Donut/Joueur/Fixe", Perso, WIDTH, HEIGHT);}
    if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Fixe", Perso, WIDTH, HEIGHT);} //Je fais ça pour éviter que le jeu affiche  des images du joueur quand il joue pas: C'est inutile
}

void CoupPoing()
{
    affiche_all();
    if(DonutSelec == true){affiche_image("Data/Player/Donut/Joueur/Punch", Perso, WIDTH, HEIGHT);}
    if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Punch", Perso, WIDTH, HEIGHT);} //Animation du coup de poing
    attendre(100);
    affiche_all();
    if(DonutSelec == true){affiche_image("Data/Player/Donut/Joueur/Punch2", Perso, WIDTH, HEIGHT);}
    if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Punch2", Perso, WIDTH, HEIGHT);}
    attendre(100);
	affiche_all();


    if((Perso.x + 130) >= Enemy.x) //Si il est dans la hitbox de l'ennemi (Si il peut le toucher)
    {
        Attaque = 30;
        if(strcmp(CodeEntre, "POWER") == 0){Attaque = 100;}
        BoboJ2(Attaque); //On appelle la fonction qui va infliger "Attaque" (Les points aléatoires) au sac (Joueur 2 ici)
    }

   	if(DonutSelec == true){draw_fill_rectangle(Perso, CacheCoup, noir);affiche_image("Data/Player/Tavuk/Ennemi/Fixe", Enemy, WIDTH, HEIGHT);}
    if(DonutSelec == true){affiche_image("Data/Player/Donut/Joueur/Fixe", Perso, WIDTH, HEIGHT);}
    if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Fixe", Perso, WIDTH, HEIGHT);} //On le remet dans sa position initiale
}

void CoupPied()
{
    affiche_all();
    attendre(100);
    if(DonutSelec == true){affiche_image("Data/Player/Donut/Joueur/Kick", Perso, WIDTH, HEIGHT);}
    if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Kick", Perso, WIDTH, HEIGHT);} //Animation du coup de pied
	affiche_all();
    if(DonutSelec == true){affiche_image("Data/Player/Donut/Joueur/Kick2", Perso, WIDTH, HEIGHT);}
    if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Kick2", Perso, WIDTH, HEIGHT);};
    attendre(100);
    affiche_all();

    if((Perso.x + 130) >= Enemy.x) //Si il est dans la hitbox de l'ennemi (Si il peut le toucher)
    {
        Attaque = 50;
        if(strcmp(CodeEntre, "POWER") == 0){Attaque = 200;}
        BoboJ2(Attaque); //On appelle la fonction qui va infliger "Attaque" (Les points aléatoires) au sac (Joueur 2 ici)
    }

    if(DonutSelec == true){draw_fill_rectangle(Perso, CacheCoup, noir);affiche_image("Data/Player/Tavuk/Ennemi/Fixe", Enemy, WIDTH, HEIGHT);}
    if(DonutSelec == true){affiche_image("Data/Player/Donut/Joueur/Fixe", Perso, WIDTH, HEIGHT);}
    if(TavukSelec == true){affiche_image("Data/Player/Tavuk/Joueur/Fixe", Perso, WIDTH, HEIGHT);}
}

void ORDI()
{
	if(((Enemy.x - Perso.x + 120) > 0) || ((Perso.x + 130 - Enemy.x) > 0))
	{
		Approcher();
	}

	VaFrapper = alea_int(4);

	if((Enemy.x < Perso.x + 131) && (VaFrapper == 1))
	{
		Frapper();
	}
}

void QuiALePlusDeVie() //Fonction qu'on appelle quand le compte à rebours tombe à 0, qui va calculer quel joueur à le plus de vie
{
	if((Vie2A.x - Vie2Retirebg.x) > ((Vie1Retirebg.x - Vie1A.x)))
	{
		J2Gagne = true;
	}

	if((Vie2A.x - Vie2Retirebg.x) < ((Vie1Retirebg.x - Vie1A.x)))
	{
		J1Gagne = true;
	}

	if((Vie2A.x - Vie2Retirebg.x) == ((Vie1Retirebg.x - Vie1A.x)))
	{
		DoubleKO = true;
	}
}

void Rapprochement() //Sorte de cinématique du début, où les deux personnages marchent jusqu'à se rencontrer
{
	while((Enemy.x - Perso.x) > 250)
	{
		if(DonutSelec == true) //Si J1 est Donut
		{
			Perso.x++; CacheCoup.x++;
			Enemy.x--;
			affiche_image("Data/Player/Donut/Joueur/Run", Perso, WIDTH, HEIGHT);
			affiche_image("Data/Player/Tavuk/Ennemi/Run", Enemy, WIDTH, HEIGHT);
			affiche_all();
			affiche_image("Data/Player/Donut/Joueur/Run2", Perso, WIDTH, HEIGHT);
			affiche_image("Data/Player/Tavuk/Ennemi/Run2", Enemy, WIDTH, HEIGHT);
			affiche_all();
		}
		else //Si J1 est Tavuk
		{
			Perso.x++;
			Enemy.x--;
			affiche_image("Data/Player/Tavuk/Joueur/Run", Perso, WIDTH, HEIGHT);
			affiche_image("Data/Player/Donut/Ennemi/Run", Enemy, WIDTH, HEIGHT);
			affiche_all();
			affiche_image("Data/Player/Tavuk/Joueur/Run2", Perso, WIDTH, HEIGHT);
			affiche_image("Data/Player/Donut/Ennemi/Run2", Enemy, WIDTH, HEIGHT);
			affiche_all();
		}
	}
}
