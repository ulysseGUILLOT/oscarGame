#include "header.h"
#include "Game.h"

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    // initialisation de la partie
    Game game;

    // lancement de la boucle de jeu
    SDL_Event event;
    while (game.isActive()) {
        game.setLastFrameTime(SDL_GetTicks());
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
                    case SDLK_d:
                        if (game.isDevMode()) {
                            game.setDevMode(false);
                        } else {
                            game.setDevMode(true);
                        }
                        break;
                }
            }
        }

        // r�actualise la position de la fus�e
        if (game.getRocket().checkAndRefreshPos()) {
            // ajoute un dechet si la fus�e atteint le ciel
            game.addTrash();
            game.setScore(game.getScore() + 10);
            std::cout << "score : " << game.getScore() << std::endl;
        }

        // affichage de la fenetre de jeu
        game.presentRenderer();
    }

    // detruire la partie et quitter
    game.~Game();
    return 0;
}

SDL_Color getPixelColor(const SDL_Surface* pSurface, int x, int y) {
    // Bytes per pixel
    const Uint8 Bpp = pSurface->format->BytesPerPixel;

    Uint8* pPixel = (Uint8*)pSurface->pixels + y * pSurface->pitch + x * Bpp;

    Uint32 PixelData = *(Uint32*)pPixel;

    SDL_Color Color = { 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };

    // Retrieve the RGB values of the specific pixel
    SDL_GetRGB(PixelData, pSurface->format, &Color.r, &Color.g, &Color.b);

    return Color;
}