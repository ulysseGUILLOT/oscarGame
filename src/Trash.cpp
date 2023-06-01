//
// Created by RBatty on 29/05/2023.
//

#include "Trash.h"

Trash::Trash(SDL_Renderer* pRenderer) {
    rotationDegree = 0;

    pSprite = SDL_LoadBMP("../src/img/trash.bmp");
    if (!pSprite) {
        std::cout << "Echec de chargement de l'image dechet : " << SDL_GetError() << std::endl;
    }
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite);
    if (!pTexture) {
        std::cout << "Echec de la creation de la texture dechet : " << SDL_GetError() << std::endl;
    }
}

Trash::~Trash() {
    SDL_DestroyTexture(pTexture);
}

void Trash::toRender(SDL_Renderer *pRenderer) {
    SDL_Rect dest = {100, 100, pSprite->w, pSprite->h};
    SDL_RenderCopy(pRenderer, pTexture, NULL, &dest);
    std::cout << "affichage trash" << std::endl;
}
