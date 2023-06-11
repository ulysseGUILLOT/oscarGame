//
// Created by RBatty on 29/05/2023.
//

#include "Rocket.h"

Rocket::Rocket() {
    posX = WSCREEN / 2;
    posY = HSCREEN / 2;
    moving = false;
    pSurfaceRocket = SDL_LoadBMP("../src/img/rocket.bmp");
    if (!pSurfaceRocket) {
        std::cout << "Echec de chargement du sprite : " << SDL_GetError() << std::endl;
    }
    pSurfaceCollisionRocket = SDL_LoadBMP("../src/img/rocketCollision.bmp");
    if (!pSurfaceCollisionRocket) {
        std::cout << "Echec de chargement du sprite de collision : " << SDL_GetError() << std::endl;
    }
}

Rocket::~Rocket() {
    SDL_FreeSurface(pSurfaceRocket);
    SDL_FreeSurface(pSurfaceCollisionRocket);
}

void Rocket::display(SDL_Renderer *pRenderer, SDL_Surface* pSurfaceCollision) {
    SDL_SetColorKey(pSurfaceRocket, SDL_TRUE, SDL_MapRGB(pSurfaceRocket->format, 0, 255, 255));
    pTextureRocket = SDL_CreateTextureFromSurface(pRenderer, pSurfaceRocket);
    if (pTextureRocket) {
        SDL_Rect dest = {posX - pSurfaceRocket->w / 2, posY - pSurfaceRocket->h / 2, pSurfaceRocket->w, pSurfaceRocket->h};
        SDL_RenderCopy(pRenderer, pTextureRocket, NULL, &dest);
        SDL_DestroyTexture(pTextureRocket);

        // affichage de la hitbox de la fusée
        SDL_SetColorKey(pSurfaceCollisionRocket, SDL_TRUE, SDL_MapRGB(pSurfaceCollisionRocket->format, 0, 255, 255));
        SDL_BlitSurface(pSurfaceCollisionRocket, nullptr, pSurfaceCollision, &dest);
    } else {
        std::cout << "Echec de la creation de la texture : " << SDL_GetError() << std::endl;
    }
}

bool Rocket::checkAndRefreshPos() {
    if (moving) {
        if (posY >= 0 - pSurfaceRocket->h / 2) {
            posY = posY - ROCKET_SPEED;
            return false;
        } else {
            moving = false;
            posY = HSCREEN / 2;
            return true;
        }
    }
    return false;
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

void Rocket::reset() {
    posY = HSCREEN / 2;
    moving = false;
}

