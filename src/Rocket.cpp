//
// Created by RBatty on 29/05/2023.
//

#include "Rocket.h"

Rocket::Rocket() {
    posX = WSCREEN / 2;
    posY = HSCREEN / 2;
    moving = false;

    pSurfaceCollisionRocket = SDL_LoadBMP("../src/img/rocketCollision.bmp");
    if (!pSurfaceCollisionRocket) {
        std::cout << "Echec de chargement du sprite de collision : " << SDL_GetError() << std::endl;
    }
}

Rocket::~Rocket() {
    for (int i = 0; i < NB_SPRITE_ROCKET; i++) {
        SDL_FreeSurface(pSurfaceRocket[i]);
    }
    SDL_FreeSurface(pSurfaceCollisionRocket);
}

void Rocket::loadSurfaces() {
    for (int i = 0; i < NB_SPRITE_ROCKET; i++) {
        std::string basePath = "../src/img/rocket/rocket_";
        std::string fullPath = basePath + std::to_string(i) + ".bmp";

        pSurfaceRocket.push_back(SDL_LoadBMP(fullPath.c_str()));
        if (!pSurfaceRocket[i]) {
            std::cout << "Echec de chargement du sprite : " << SDL_GetError() << std::endl;
        }

        SDL_SetColorKey(pSurfaceRocket[i], SDL_TRUE, SDL_MapRGB(pSurfaceRocket[i]->format, 0, 255, 255));
        pTextureRocket.push_back(SDL_CreateTextureFromSurface(pRenderer, pSurfaceRocket[i]));
        if (!pTextureRocket[i]) {
            std::cout << "Echec de la creation de la texture : " << SDL_GetError() << std::endl;
            return;
        }
    }
}

void Rocket::display(SDL_Surface *pSurfaceCollision) {
    SDL_Rect dest = {posX - pSurfaceRocket[0]->w / 2, posY - pSurfaceRocket[0]->h / 2, pSurfaceRocket[0]->w,
                     pSurfaceRocket[0]->h};
    SDL_RenderCopy(pRenderer, pTextureRocket[1], NULL, &dest);
    //SDL_DestroyTexture(pTextureRocket[0]);

    // affichage de la hitbox de la fusée
    SDL_SetColorKey(pSurfaceCollisionRocket, SDL_TRUE, SDL_MapRGB(pSurfaceCollisionRocket->format, 0, 255, 255));
    SDL_BlitSurface(pSurfaceCollisionRocket, nullptr, pSurfaceCollision, &dest);
}

bool Rocket::checkAndRefreshPos() {
    if (moving) {
        if (posY >= 0 - pSurfaceRocket[0]->h / 2) {
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

void Rocket::setPRenderer(SDL_Renderer *pRenderer) {
    Rocket::pRenderer = pRenderer;
}
