#include "header.h"

int main(int argc, char* argv[]) {
    // initialisation de la partie
    Game game;

    // affichage de la fenetre de jeu
    game.presentRenderer();

    // Attendre un certain délai
    SDL_Delay(2000);

    // detruire la partie et quitter
    game.~Game();

    return 0;
}