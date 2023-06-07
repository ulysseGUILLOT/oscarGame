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
        SDL_Rect dest = {posX - pSprite->w / 2, posY - pSprite->h / 2, pSprite->w, pSprite->h};
        SDL_RenderCopy(pRenderer, pTexture, NULL, &dest);
    } else {
        std::cout << "Echec de la creation de la texture dechet : " << SDL_GetError() << std::endl;
    }
    SDL_DestroyTexture(pTexture);
}

void Trash::calculateCoordFromAngle() {
    int centerX = WSCREEN / 2;
    int centerY = HSCREEN / 2;
    double rotationAngleRadians = rotationAngleDegrees * M_PI / 180;
    posX = int(centerX + TRASH_ORBIT_RADIUS * cos(rotationAngleRadians));
    posY = int(centerY + TRASH_ORBIT_RADIUS * sin(rotationAngleRadians));
}

bool Trash::testCollision(int rocketX, int rocketY, SDL_Surface *pSurfaceCollision) {
    int trashVertexX[4];
    int trashVertexY[4];

    trashVertexX[0] = posX - (pSprite->w / 2);
    trashVertexY[0] = posY - (pSprite->h / 2);

    trashVertexX[1] = posX + (pSprite->w / 2);
    trashVertexY[1] = posY - (pSprite->h / 2);

    trashVertexX[2] = posX - (pSprite->w / 2);
    trashVertexY[2] = posY + (pSprite->h / 2);

    trashVertexX[3] = posX + (pSprite->w / 2);
    trashVertexY[3] = posY + (pSprite->h / 2);

    /*
     * Boucle de test de collision :
     * Obtention de la couleur du pixel sour les 4 sommets du carr� du dechet
     * si la couleur est "verte" alors il y a une colision entre le dechet et la fus�e
     */
    for (int i = 0; i < 4; i++) {
        SDL_Color color = getPixelColor(pSurfaceCollision, trashVertexX[i], trashVertexY[i]);
        //std::cout << "r:" << color.r << " g:" << color.g << " b:" << color.b << std::endl;
        if (color.r == 0 && color.g == 255 && color.b == 0) {
            std::cout << "collision" << std::endl;
            return true;
        }
    }

    for (int i = 0; i < 4; i++) {
        int rectSize = 8;
        int destRectX = trashVertexX[i] - rectSize / 2;
        int destRectY = trashVertexY[i] - rectSize / 2;

        SDL_Rect destRect = {destRectX, destRectY, rectSize, rectSize};
        SDL_FillRect(pSurfaceCollision, &destRect, SDL_MapRGB(pSurfaceCollision->format, 255, 0, 0));
    }

    return false;
}
