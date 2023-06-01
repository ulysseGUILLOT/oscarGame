//
// Created by RBatty on 29/05/2023.
//

#include "Trash.h"

Trash::Trash() {
    rotationAngleDegrees = 0;

    pSprite = SDL_LoadBMP("../src/img/trash.bmp");
    if (!pSprite) {
        std::cout << "Echec de chargement de l'image dechet : " << SDL_GetError() << std::endl;
    }
}

Trash::~Trash() {
    SDL_DestroyTexture(pTexture);
}

void Trash::toRender(SDL_Renderer *pRenderer) {
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite);
    if (pTexture) {
        calculateCoordFromAngle();
        SDL_Rect dest = {posX, posY, pSprite->w, pSprite->h};
        SDL_RenderCopy(pRenderer, pTexture, NULL, &dest);
    } else {
        std::cout << "Echec de la creation de la texture dechet : " << SDL_GetError() << std::endl;
    }

}

void Trash::calculateCoordFromAngle() {
    int centerX = WSCREEN / 2;
    int centerY = HSCREEN / 2;
    double rotationAngleRadians = rotationAngleDegrees * M_PI / 180;
    posX = int(centerX + TRASH_ORBIT_RADIUS * cos(rotationAngleRadians));
    posY = int(centerY + TRASH_ORBIT_RADIUS * sin(rotationAngleRadians));
}
