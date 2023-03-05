char CaractereLu = 'NULL'; //Variable qui va stocker chaque caractère lu
char CodeEntre[200]; //Chaîne qui va stocker le code entré
FILE* Pointeur = NULL; //Le pointeur qui va permettre la lecture du fichier
int incrementeur = 0; //Son nom explique tout

void RecuperationCode()
{
	Pointeur = fopen("INSERTION_TRICHE", "r"); //On ouvre le fichier en lecture seule

	rewind(Pointeur);
	
	while(CaractereLu != '#') //Tant qu'on est pas arrivé au commencement de la lecture du code
	{
		CaractereLu = fgetc(Pointeur); //On lit tout les caractère afin d'arriver au '#'
	}
	
	CaractereLu = 'A'; //A ce stade, CaractereLu = '#', donc on la "remet à zéro"

	while(CaractereLu != '#') //Tant qu'on pas atteint la fin du code entré
	{
		CaractereLu = fgetc(Pointeur); 
		CodeEntre[incrementeur] = CaractereLu;
		incrementeur++;
	}
	
	incrementeur--; //On retourne en arrière pour modifier la dernière case de la chaîne caractère
	CodeEntre[incrementeur] = 0; //Comme la dernière case de la chaîne de caractère est '#', on l'enlève
	fclose(Pointeur); //On ferme le fichier qui a été ouvert évidemment à la fin
}
