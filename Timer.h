int Temps = 99; //Variable qui affichera et stockera le temps en compte à rebours (100 à 0)
int TempsInitial = 0; //Dès le début du combat, on stocke les ticks du début ici pour que le temps soit "fidèle" au combat
char* TempsEcrit[4]; //Chaîne qui va stocker le compte à rebours
POINT PointTemps, PointTemps2; //Points qui vont permettre l'affichage du timer
bool TempsFini = false; //True si le combat est fini à cause du compte à rebours

void LancementChrono()
{
	TempsInitial = (SDL_GetTicks())/1000; //On prend les ticks actuel qui correspondent au début du combat et on divise par 1000 pour avoir les secondes (Ticks étant en millisecondes)
	PointTemps.x = 640; PointTemps.y = 680;
	PointTemps2.x = 730; PointTemps2.y = 600;
}

void Chrono()
{
	draw_fill_rectangle(PointTemps, PointTemps2, noir); //Effacer le temps précédent pour mettre à jour
	sprintf(TempsEcrit, "%d", Temps); //Comme c'est une chaîne de caractère qui va être variable (Le temps), on va écrire tout le temps pour mettre à jour la valeur du temps dans la variable TempsEcrit
	if(Temps > 10){aff_pol(TempsEcrit,70, PointTemps, blanc);} //On écrit à l'écran le chrono en blanc
	if(Temps <= 10){aff_pol(TempsEcrit,70, PointTemps, rouge);} //En dessous de 10, on l'affiche en rouge pour dire que c'est bientôt fini
	Temps = 99 - (SDL_GetTicks()/1000 - TempsInitial); //Calcule qui divise par 1000 pour avoir en secondes les ticks actuels moins celui du début du combat pour avoir les ticks du combat (0 au début et augmentent durant le déroulement) et "90 -" au début pour faire un compte à rebours partant de 100
	if(strcmp(CodeEntre, "TIMER") == 0){Temps = 99;} //Si le code entré est TIMER, le TIMER est bloqué à 99
	if(Temps == 0){TempsFini = true;} //Si le compte à rebours tombe à 0, le temps est fini ! Donc il passe à true
}
