//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_TRASH_H
#define OSCARGAME_TRASH_H

#include "header.h"

class Trash {
private:
    int rotationDegree;

    SDL_Rect collisionRect;
    SDL_Surface* pSprite;
    SDL_Texture* pTexture;

public:
    Trash(SDL_Renderer* pRenderer);
    ~Trash();
    void toRender(SDL_Renderer* pRenderer);
};


#endif //OSCARGAME_TRASH_H
