//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_ROCKET_H
#define OSCARGAME_ROCKET_H

#include "header.h"

class Rocket {
private:
    int posX;
    int posY;
    bool isMoving;

    SDL_Rect collisionRect;
    SDL_Surface* pSprite;
    SDL_Texture* pTexture;

public:
    Rocket();
    ~Rocket();
    void fly();
    void reset();
    bool testCollision();
    void toRenderer(SDL_Renderer *pRenderer);
};


#endif //OSCARGAME_ROCKET_H
