//
// Created by RBatty on 29/05/2023.
//

#include "Rocket.h"

Rocket::Rocket() {
    posX = WSCREEN / 2;
    posY = HSCREEN / 2;
    moving = false;
    pSprite = SDL_LoadBMP("../src/img/rocket.bmp");
    if (!pSprite) {
        std::cout << "Echec de chargement du sprite : " << SDL_GetError() << std::endl;
    }
    pSurfaceCollision = SDL_LoadBMP("../src/img/rocketCollision.bmp");
    if (!pSurfaceCollision) {
        std::cout << "Echec de chargement du sprite de collision : " << SDL_GetError() << std::endl;
    }
}

Rocket::~Rocket() {
    SDL_FreeSurface(pSprite);
    SDL_DestroyTexture(pTexture);

    SDL_FreeSurface(pSurfaceCollision);
    SDL_DestroyTexture(pTextureCollision);
}

void Rocket::toRenderer(SDL_Renderer *pRenderer) {
    SDL_SetColorKey(pSprite, SDL_TRUE, SDL_MapRGB(pSprite->format, 0, 255, 255));
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite);
    if (pTexture) {
        SDL_Rect dest = {posX - pSprite->w / 2, posY - pSprite->h / 2, pSprite->w, pSprite->h};
        SDL_RenderCopy(pRenderer, pTexture, NULL, &dest);

        SDL_DestroyTexture(pTexture);
    } else {
        std::cout << "Echec de la creation de la texture : " << SDL_GetError() << std::endl;
    }
}

bool Rocket::checkAndRefreshPos() {
    if (moving) {
        if (posY >= 0 - pSprite->h / 2) {
            posY = posY - ROCKET_SPEED;
            return false;
        } else {
            moving = false;
            posY = HSCREEN / 2;
            return true;
        }
    }
}

bool Rocket::isMoving() const {
    return moving;
}

void Rocket::setMoving(bool moving) {
    Rocket::moving = moving;
}

int Rocket::getPosX() const {
    return posX;
}

void Rocket::setPosX(int posX) {
    Rocket::posX = posX;
}

int Rocket::getPosY() const {
    return posY;
}

void Rocket::setPosY(int posY) {
    Rocket::posY = posY;
}

