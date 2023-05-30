//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_ROCKET_H
#define OSCARGAME_ROCKET_H

#include <SDL.h>

class Rocket {
private:
    int posX;
    int posY;
    bool isMoving;

    SDL_Rect collisionRect;
    SDL_Surface* pSurface;
    SDL_Texture* pTexture;

public:
    void fly();
    void reset();
    bool testCollision();
    void toRenderer();
};


#endif //OSCARGAME_ROCKET_H
