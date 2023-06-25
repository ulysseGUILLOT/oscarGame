#include "header.h"
#include "Game.h"

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    TTF_Init();

    // ouverture de l'audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Erreur lors de l'initialisation de l'audio : " << Mix_GetError() << std::endl;
        SDL_Quit();
    }

    // initialisation de la partie
    Game game;
    game.addTrash();

    // désactive le curseur de la souris
    SDL_ShowCursor(SDL_DISABLE);

    // connexion du joystick
    SDL_Joystick *pJoystick = connectJoystick();

    // affichage de l'écran de démarrage
    game.renderStartScreen();

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
                        if (game.isPlaying()) {
                            if (!game.getRocket().isMoving()) {
                                game.setChannelChunkLaunch(game.playChunk(game.getPChunkLaunch(), 0));
                            }
                            game.getRocket().setMoving(true);
                        } else {
                            Mix_HaltChannel(game.getChannelChunkMusicStartMenu());
                            game.playChunk(game.getPChunkMusic(), -1);
                            game.setPlaying(true);
                        }
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

            if (event.type == SDL_JOYBUTTONDOWN) {
                if (event.jbutton.button == 0 || event.jbutton.button == 3) {
                    if (game.isPlaying()) {
                        if (!game.getRocket().isMoving()) {
                            game.setChannelChunkLaunch(game.playChunk(game.getPChunkLaunch(), 0));
                        }
                        game.getRocket().setMoving(true);
                    } else {
                        Mix_HaltChannel(game.getChannelChunkMusicStartMenu());
                        game.playChunk(game.getPChunkMusic(), -1);
                        game.setPlaying(true);
                    }
                }
            }
        }

        if (game.isPlaying()) {
            // réactualise la position de la fusée
            if (game.getRocket().checkAndRefreshPos()) {
                // ajoute un dechet si la fusée atteint le ciel
                game.addTrash();
                game.setScore(game.getScore() + 10);
            }

            // affichage de la fenetre de jeu
            game.renderPlaying();
        }
    }

    // detruire la partie et quitter
    game.~Game();
    return 0;
}

SDL_Color getPixelColor(const SDL_Surface *pSurface, int x, int y) {
    // Bytes per pixel
    const Uint8 Bpp = pSurface->format->BytesPerPixel;

    Uint8 *pPixel = (Uint8 *) pSurface->pixels + y * pSurface->pitch + x * Bpp;

    Uint32 PixelData = *(Uint32 *) pPixel;

    SDL_Color Color = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};

    // Retrieve the RGB values of the specific pixel
    SDL_GetRGB(PixelData, pSurface->format, &Color.r, &Color.g, &Color.b);

    return Color;
}

SDL_Joystick *connectJoystick() {
    SDL_Joystick *pJoystick = nullptr;
    if (SDL_NumJoysticks() != 0) {
        pJoystick = SDL_JoystickOpen(0);
        if (!pJoystick) {
            std::cout << "Erreur lors de la connexion du joystick : " << SDL_GetError() << std::endl;
            SDL_Quit();
        }
    } else {
        std::cout << "Pas de joystick connecte !" << std::endl;
    }

    return pJoystick;
}