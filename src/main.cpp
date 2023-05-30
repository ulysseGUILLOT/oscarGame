#include "header.h"
#include "Game.h"

int main(int argc, char *argv[]) {
    // initialisation de la partie
    Game game;

    // lancement de la boucle de jeu
    SDL_Event event;
    while (game.isActive()) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game.setActive(false);
            }
        }

        // affichage de la fenetre de jeu
        game.presentRenderer();
    }

    // detruire la partie et quitter
    game.~Game();
    return 0;
}