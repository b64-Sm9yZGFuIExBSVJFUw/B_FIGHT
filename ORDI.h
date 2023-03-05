bool ADroite = false;
bool AGauche = false;
bool CombatLance = false; //True quand le combat commence
int QuelCoup = -1;

void Approcher()
{
	ADroite = false; //On remet "à zéro" les variables
	AGauche = false;
	
	if((Enemy.x - Perso.x) > 0) //Si l'ennemi est à droite du personnage
	{
		ADroite = true;
	}
	else //Si il est à gauche
	{
		AGauche = true;
	}
	
	if(ADroite == true)
	{
		while((Enemy.x - (Perso.x + 130) > 0)) //L'ennemi s'approche jusqu'à qu'il atteigne la hitbox du personnage
		{
			Enemy.x--; 
			CacheCoupEnnemi.x--;
			if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Run", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
			if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Run", Enemy, WIDTH, HEIGHT);}
			affiche_all();
			Enemy.x--;
			CacheCoupEnnemi.x--;
			if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Run2", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
			if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Run2", Enemy, WIDTH, HEIGHT);}
			affiche_all();
			if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Fixe", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
			if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Fixe", Enemy, WIDTH, HEIGHT);}
		} 
	}
	
	if(AGauche == true)
	{
		while(((Perso.x + 130) - Enemy.x) > 0) //L'ennemi s'approche jusqu'à qu'il atteigne la hitbox du personnage
		{
			Enemy.x++;
			CacheCoupEnnemi.x++;
			if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Run", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
			if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Run", Enemy, WIDTH, HEIGHT);}
			affiche_all();
			Enemy.x++;
			CacheCoupEnnemi.x++;
			if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Run2", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
			if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Run2", Enemy, WIDTH, HEIGHT);}
			affiche_all();
			if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Fixe", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
			if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Fixe", Enemy, WIDTH, HEIGHT);}
		} 		
	}
	
	if(CombatLance == false)
	{
		CombatLance = true; //L'ennemi est là, le combat commence!
		LancementChrono(); //On démarre le chrono au début du programme
	}
}

void Frapper()
{
	QuelCoup = alea_int(2);
	if(QuelCoup == 0)
	{
		affiche_all();
		if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Punch", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
		if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Punch", Enemy, WIDTH, HEIGHT);}
		affiche_all();
		if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Punch2", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
		if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Punch2", Enemy, WIDTH, HEIGHT);}
		if(DonutSelec == false){draw_fill_rectangle(Enemy, CacheCoupEnnemi, noir);} 
		affiche_all();
    }
    else
    {
		affiche_all();
		if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Kick", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
		if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Kick", Enemy, WIDTH, HEIGHT);}
		affiche_all();
		if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Kick2", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
		if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Kick2", Enemy, WIDTH, HEIGHT);}
		if(DonutSelec == false){draw_fill_rectangle(Enemy, CacheCoupEnnemi, noir);} 
		affiche_all();
	}
    if(Enemy.x > Perso.x) //Si il est dans la hitbox du joueur (Si il peut le toucher)
    {
		//Audio("Data/Sons/Punch.wav");
        if(QuelCoup == 0){Attaque = 30;} //Si coup de poing
        if(QuelCoup == 1){Attaque = 50;} //Si /////// pied
        if(strcmp(CodeEntre, "LAZY") == 0){Attaque = 1;} //Si le code LAZY a été entré, il attaquera toujours que 10
        BoboJ1(Attaque); //On appelle la fonction qui va infliger "Attaque" (Les points aléatoires) au sac (Joueur 2 ici)
    }

    if(DonutSelec == true){affiche_image("Data/Player/Tavuk/Ennemi/Fixe", Enemy, WIDTH, HEIGHT);} //On affiche l'image de l'animation de Bruno si J1 est lui
	if(TavukSelec == true){affiche_image("Data/Player/Donut/Ennemi/Fixe", Enemy, WIDTH, HEIGHT);}
}
