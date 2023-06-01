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
}

Rocket::~Rocket() {
    SDL_FreeSurface(pSprite);
    SDL_DestroyTexture(pTexture);
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
            // todo: gerer la vitesse de deplacement ici
            posY = posY - 4;
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

