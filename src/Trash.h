//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_TRASH_H
#define OSCARGAME_TRASH_H

#define TRASH_ORBIT_RADIUS 450
#define TRASH_ROTATION_SPEED 0.4

#include "header.h"

class Trash {
private:
    float rotationAngleDegrees;
    int posX;
    int posY;

    SDL_Rect collisionRect;
    SDL_Surface* pSprite;
    SDL_Texture* pTexture;

public:
    Trash();
    void toRender(SDL_Renderer* pRenderer);
    void calculateCoordFromAngle();
    bool testCollision(int posX, int posY, SDL_Renderer* pDevRenderer, bool devMode);
};


#endif //OSCARGAME_TRASH_H
