//
// Created by RBatty on 29/05/2023.
//

#include "Rocket.h"

Rocket::Rocket() {
    posX = 0;
    posY = 0;
    isMoving = false;
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
        SDL_Rect dest = { posX - pSprite->w/2,posY - pSprite->h/2, pSprite->w, pSprite->h};
        SDL_RenderCopy(pRenderer, pTexture, NULL, &dest);

        SDL_DestroyTexture(pTexture);
    } else {
        std::cout << "Echec de la creation de la texture : " << SDL_GetError() << std::endl;
    }
}

