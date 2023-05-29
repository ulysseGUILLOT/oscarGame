//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_TRASH_H
#define OSCARGAME_TRASH_H

#include <SDL.h>

class Trash {
private:
    int posX;
    int posY;

    SDL_Rect collisionRect;
    SDL_Surface* pSurface;
    SDL_Texture* pTexture;
};


#endif //OSCARGAME_TRASH_H
