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
    bool moving;

    SDL_Surface* pSprite;
    SDL_Texture* pTexture;

    SDL_Surface* pSurfaceCollision;
    SDL_Texture* pTextureCollision;

public:
    Rocket();
    ~Rocket();
    bool checkAndRefreshPos();
    void reset();
    bool testCollision();
    void toRenderer(SDL_Renderer *pRenderer);

    bool isMoving() const;
    void setMoving(bool moving);
};


#endif //OSCARGAME_ROCKET_H
