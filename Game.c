///FICHIER PRINCIPAL DU JEU POSSEDANT TOUTES LES GRANDES FONCTIONS

#include <stdio.h>
#include "graphics.h"

SDL_AudioSpec desired, obtained, soundfile;
SDL_AudioCVT cvt;
Uint32 soundlength; //Taille du fichier du son charg� (Octets)
Uint32 soundpos; //Position courante de lecture dans le fichier son
Uint8 * sounddata; //Donn�es du fichiers charg�

#include "Audio.h"
#include "BFIGHT.h"

int main(int argc, char *argv[])
{
	init_graphics(1360,680);
	//Audio("Data/Sons/Intro.wav");
	MenuPrincipal(); //On affiche le menu principal
	ChoixPerso(); //On affiche le menu de choix du perso
	InitVies(); //On dessine les barres de vies, on les initialise
	Jeu(); //Le d�roulement du jeu
}
