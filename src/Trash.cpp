//
// Created by RBatty on 29/05/2023.
//

#include "Trash.h"

Trash::Trash() {
    // todo : initialiser le rayon de l'orbite avec + ou - 20 pixels sur la constante
    rotationAngleDegrees = -90;

    pSprite = SDL_LoadBMP("../src/img/trash.bmp");
    if (!pSprite) {
        std::cout << "Echec de chargement de l'image dechet : " << SDL_GetError() << std::endl;
    }
}

void Trash::toRender(SDL_Renderer *pRenderer) {
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite);
    if (pTexture) {
        rotationAngleDegrees = rotationAngleDegrees + TRASH_ROTATION_SPEED;
        calculateCoordFromAngle();
        SDL_Rect dest = {posX - pSprite->w / 2, posY- pSprite->h / 2, pSprite->w, pSprite->h};
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
