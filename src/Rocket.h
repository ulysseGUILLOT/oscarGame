//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_ROCKET_H
#define OSCARGAME_ROCKET_H

#define ROCKET_SPEED 4

#include "header.h"

class Rocket {
private:
    int posX;
    int posY;
    bool moving;

    SDL_Surface* pSprite;
    SDL_Texture* pTexture;

    SDL_Surface* pSurfaceCollisionRocket;
    SDL_Texture* pTextureCollision;

public:
    Rocket();
    ~Rocket();
    bool checkAndRefreshPos();
    void reset();
    bool testCollision();
    void display(SDL_Renderer *pRenderer, SDL_Surface* pSurfaceCollision);

    bool isMoving() const;
    void setMoving(bool moving);
    int getPosX() const;
    void setPosX(int posX);
    int getPosY() const;
    void setPosY(int posY);
};


#endif //OSCARGAME_ROCKET_H
