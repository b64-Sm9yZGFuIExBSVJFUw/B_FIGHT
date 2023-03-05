///HEADER PERMETTANT LA LECTURE DES SONS


void CopyData(void * userdata, Uint8 * stream, int len) //Fonction rappel qui copie les données sonores dans le tampon audio
	{
		Uint32 tocopy = soundlength - soundpos > len ? len : soundlength - soundpos; //Attention à ne pas déborder lors de la copie
		memcpy(stream, sounddata + soundpos, tocopy); //Copie des données sonores dans le tampon audio
		soundpos += tocopy; //Mise à jour de la position de lecture
	}

void Audio(char* NomDuFichier)
{
	desired.freq = 48000; //Son 16 bits stéréo à 44100 Hz
	desired.format = AUDIO_U8;
	desired.channels = 2;
	desired.samples = 1536;
	/*Création de la fronction de rappel et des données utilisateur*/
	desired.callback = &CopyData;
	desired.userdata = NULL;

	if(SDL_OpenAudio(&desired, &obtained) != 0)
	{
		printf("Erreur lors de l'ouverture de périphérique audio: %s\n", SDL_GetError());
		return 1;
	}

	printf("Paramètres audio obtenus: %d canaux, fréquence %d, %d échantillons. \n", obtained.format & 0xff, obtained.channels, obtained.freq, obtained.samples); //Afin de vérifier si ça a bien ouvert avec les bon paramètres

	OuvrirFichier(NomDuFichier);
	Converter();
	//Fermer le périphérique audio
	SDL_CloseAudio();
}

void OuvrirFichier(char* NomDuFichier)
{
	if(SDL_LoadWAV(NomDuFichier, &soundfile, &sounddata, &soundlength) == NULL) //Si le fichier n'a pas été ouvert
	{
		printf("\n");
		printf("Erreur lors du chargement du fichier son: %s\n", SDL_GetError());
		return 1;
	}

	printf("Propriétés du fichier audio: %d canaux, fréquence %d, octets. \n", soundfile.format & 0xff, soundfile.channels, soundfile.freq, soundlength);
}

void Converter()
{
	if(SDL_BuildAudioCVT(&cvt, soundfile.format, soundfile.channels, soundfile.freq, obtained.format, obtained.channels, obtained.freq) < 0)
	{
		printf("Impossible de construire le convertisseur audio!\n");
		return 1;
	}

	/*Création du tampon utilisé pour la conversion*/
	cvt.buf = malloc(soundlength * cvt.len_mult);
	cvt.len = soundlength;
	memcpy(cvt.buf, sounddata, soundlength);

	/*Conversion...*/
	if(SDL_ConvertAudio(&cvt) != 0)
	{
		printf("Erreur lors de la conversion du fichier audio: %s\n", SDL_GetError());
		return 1;
	}

	//Libération de l'ancien tampon, création du nouveau, copie des données converties, effacement du tampon de conversion
	SDL_FreeWAV(sounddata);
	sounddata = malloc(cvt.len_cvt);
	memcpy(sounddata, cvt.buf, cvt.len_cvt);
	free(cvt.buf);

	soundlength = cvt.len_cvt;
	printf("Taille du son converti: %d octets\n", soundlength);
	soundpos = 0;

	//La fonction de rappel commence à être appelée à partir de maintenant
	printf("Démarrage de la lecture...\n");
	SDL_PauseAudio(0);

	//On attend que l'autre thread ait fini la lecture du son...
	while(soundpos < soundlength)
	{
		attendre(1); //Ralentissement de la boucle dû à des problèmes
	}

	//On arrête d'appeller la fonction de rappel
	SDL_PauseAudio(1);
}
