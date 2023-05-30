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

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        game.setActive(false);
                        break;
                    case SDLK_SPACE:
                        game.getRocket().setMoving(true);
                        break;
                }
            }
        }
        game.getRocket().refreshPos();

        // affichage de la fenetre de jeu
        game.presentRenderer();
    }

    // detruire la partie et quitter
    game.~Game();
    return 0;
}