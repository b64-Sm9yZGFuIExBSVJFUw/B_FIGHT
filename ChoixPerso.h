///AUTRE HEADER DU JEU INCULANT LES QUATRE MOUVEMENT (QUATRE SOUS-FONCTIONS) DE LA FONCTION SELECTION DU PERSONNAGE


//============== VARIABLES POUR LE CHOIX DU PERSONNAGE ===============
bool BarreSelec = false;
bool PersoPris = false; //True lorsque le choix du personnage est termin�
bool DonutSelec = true; //Noir s�lectionn� (par d�faut apr�s)
bool TavukSelec = false; //Rouge

POINT Choix;
POINT H1,H2,G1,G2,D1,D2,B1,B2; //Pour faire le "s�lectionnement" de la case, on va faire 4 rectangles pour chaque c�t� du carr�, H = haut etc...

//===================================================================

void MouvementChoix()
{
    if(DonutSelec == true) //Si le joueur Noir est actuellement s�lectionn�
        {
            if(Choix.x > 0) //Si on a cliqu� sur la  fl�che droite
            {
                MouvementSelecDroite(); //Alors le carr� cyan va � droite
                DonutSelec = false; //On ne s�lectionne plus le joueur Noir...
                TavukSelec = true; //...mais maintenant le joueur rouge
            }
        }

        if(TavukSelec == true) //Si le joueur Rouge est actuellement s�lectionn�
        {
            if(Choix.x < 0) //Si on a cliqu� sur la fl�che gauche
            {
                MouvementSelecGauche();
                TavukSelec = false;
                DonutSelec = true;
            }
        }
}

void MouvementSelecDroite()
{
    draw_fill_rectangle(H1,H2,noir);
    draw_fill_rectangle(G1,G2,noir);
    draw_fill_rectangle(D1,D2,noir);
    draw_fill_rectangle(B1,B2,noir);
    H1.x = H1.x + 200;
    H2.x = H2.x + 200;
    G1.x = G1.x + 200;
    G2.x = G2.x + 200;
    D1.x = D1.x + 200;
    D2.x = D2.x + 200;
    B1.x = B1.x + 200;
    B2.x = B2.x + 200;
    draw_fill_rectangle(H1,H2,cyan);
    draw_fill_rectangle(G1,G2,cyan);
    draw_fill_rectangle(D1,D2,cyan);
    draw_fill_rectangle(B1,B2,cyan);
}

void MouvementSelecGauche()
{
    draw_fill_rectangle(H1,H2,noir);
    draw_fill_rectangle(G1,G2,noir);
    draw_fill_rectangle(D1,D2,noir);
    draw_fill_rectangle(B1,B2,noir);
    H1.x = H1.x - 200;
    H2.x = H2.x - 200;
    G1.x = G1.x - 200;
    G2.x = G2.x - 200;
    D1.x = D1.x - 200;
    D2.x = D2.x - 200;
    B1.x = B1.x - 200;
    B2.x = B2.x - 200;
    draw_fill_rectangle(H1,H2,cyan);
    draw_fill_rectangle(G1,G2,cyan);
    draw_fill_rectangle(D1,D2,cyan);
    draw_fill_rectangle(B1,B2,cyan);
}
