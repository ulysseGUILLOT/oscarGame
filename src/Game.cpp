//
// Created by RBatty on 29/05/2023.
//

#include "Game.h"

Game::Game() {
    devMode = false;
    score = 0;
    lifeNb = LIFENB;
    active = true;
    initSdl();
    initWindow();
    initRenderer();

    pSurfaceBackground = SDL_LoadBMP("../src/img/background.bmp");
    if (!pSurfaceBackground) {
        std::cout << "Echec de chargement de l'image background : " << SDL_GetError() << std::endl;
    }
    pTextureBackground = SDL_CreateTextureFromSurface(pRenderer, pSurfaceBackground);
    if (!pTextureBackground) {
        std::cout << "Echec de la creation de la texture du background : " << SDL_GetError() << std::endl;
        active = false;
    }

    pSurfaceEarth = SDL_LoadBMP("../src/img/earth.bmp");
    if (!pSurfaceEarth) {
        std::cout << "Echec de chargement de l'image de la terre : " << SDL_GetError() << std::endl;
    }
    SDL_SetColorKey(pSurfaceEarth, SDL_TRUE, SDL_MapRGB(pSurfaceEarth->format, 0, 255, 255));
    pTextureEarth = SDL_CreateTextureFromSurface(pRenderer, pSurfaceEarth);
    if (!pTextureEarth) {
        std::cout << "Echec de la creation de la texture de la terre : " << SDL_GetError() << std::endl;
        active = false;
    }

    pSurfaceFullHeart = SDL_LoadBMP("../src/img/fullHeart.bmp");
    if (!pSurfaceFullHeart) {
        std::cout << "Echec de chargement de l'image du coeur rempli : " << SDL_GetError() << std::endl;
    }
    SDL_SetColorKey(pSurfaceFullHeart, SDL_TRUE, SDL_MapRGB(pSurfaceFullHeart->format, 0, 255, 255));
    pTextureFullHeart = SDL_CreateTextureFromSurface(pRenderer, pSurfaceFullHeart);
    if (!pTextureFullHeart) {
        std::cout << "Echec de la creation de la texture du coeur rempli : " << SDL_GetError() << std::endl;
        active = false;
    }

    pSurfaceEmptyHeart = SDL_LoadBMP("../src/img/emptyHeart.bmp");
    if (!pSurfaceEmptyHeart) {
        std::cout << "Echec de chargement de l'image du coeur vide : " << SDL_GetError() << std::endl;
    }
    SDL_SetColorKey(pSurfaceEmptyHeart, SDL_TRUE, SDL_MapRGB(pSurfaceEmptyHeart->format, 0, 255, 255));
    pTextureEmptyHeart = SDL_CreateTextureFromSurface(pRenderer, pSurfaceEmptyHeart);
    if (!pTextureEmptyHeart) {
        std::cout << "Echec de la creation de la texture du coeur vide : " << SDL_GetError() << std::endl;
        active = false;
    }

    pSurfaceCollision = SDL_CreateRGBSurface(0, WSCREEN, HSCREEN, 32, 0, 0, 0, 0);
    if (!pSurfaceCollision) {
        std::cout << "Echec de la création de la surface de collision : " << SDL_GetError() << std::endl;
        active = false;
    }

    pFont = TTF_OpenFont("../src/font/Rocgrotesk-compressed-bold.ttf", 50);
    if (!pFont) {
        std::cout << "Echec du chargement de la police d'ecriture: " << TTF_GetError() << std::endl;
    }
}

Game::~Game() {
    rocket.~Rocket();
    SDL_DestroyTexture(pTextureBackground);
    SDL_DestroyTexture(pTextureEarth);
    SDL_DestroyTexture(pTextureFullHeart);
    SDL_DestroyTexture(pTextureEmptyHeart);
    SDL_DestroyRenderer(pRenderer);
    TTF_CloseFont(pFont);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}

void Game::initSdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        return;
    }
}

void Game::initWindow() {
    pWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080,
                               SDL_WINDOW_FULLSCREEN);
    if (!pWindow) {
        std::cout << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
}

void Game::initRenderer() {
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!pRenderer) {
        std::cout << "Erreur lors de la création du rendu : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        return;
    }
}

void Game::presentRenderer() {
    SDL_RenderClear(pRenderer);

    //Affichage du background
    SDL_Rect dest = {0, 0, WSCREEN, HSCREEN};
    SDL_RenderCopy(pRenderer, pTextureBackground, NULL, &dest);

    //Affichage de la terre
    dest = {(WSCREEN / 2) - (pSurfaceEarth->w / 2), (HSCREEN / 2) - (pSurfaceEarth->h / 2), pSurfaceEarth->w,
            pSurfaceEarth->h};
    SDL_RenderCopy(pRenderer, pTextureEarth, NULL, &dest);

    // affichage de la fusée
    rocket.display(pRenderer, pSurfaceCollision);

    // affichage des déchets et test de collision avec la fusée
    for (int i = 0; i < trashes.size(); i++) {
        bool collision = false;
        trashes[i].toRender(pRenderer);
        collision = trashes[i].testCollision(0, 0, pSurfaceCollision);
        if (collision) {
            rocket.reset();
            if (lifeNb > 1) {
                lifeNb--;
            } else {
                // todo : créer un attribut indiquant la fin du jeu qui ne ferme pas la fenêtre, puis afficher un écran de défaite
                std::cout << "fin de la partie" << std::endl;
                SDL_Delay(3000);
                active = false;
            }
        }
    }

    // affichage des vies
    displayHearts();

    // affichage du score
    displayScore();

    // si dev mode : affichage de la surface de la collision
    if (devMode) {
        SDL_Texture *pTextureDev = SDL_CreateTextureFromSurface(pRenderer, pSurfaceCollision);
        dest = {0, 0, WSCREEN, HSCREEN};
        SDL_RenderCopy(pRenderer, pTextureDev, nullptr, &dest);
        SDL_DestroyTexture(pTextureDev);
    }

    // nettoyage de la surface de collision
    SDL_FillRect(pSurfaceCollision, nullptr, SDL_MapRGB(pSurfaceCollision->format, 0, 0, 0));

    // attend le temps necessaire pour obtenir 60fps
    regulateFps();

    // afficher le rendu total
    SDL_RenderPresent(pRenderer);
}

void Game::addTrash() {
    Trash trash;
    trashes.push_back(trash);
}

void Game::displayHearts() {
    for (int i = 0; i < 3; i++) {
        SDL_Rect dest = {WSCREEN - 300 + i * 75, 50, pSurfaceFullHeart->w, pSurfaceFullHeart->h};

        if (lifeNb - i > 0) {
            SDL_RenderCopy(pRenderer, pTextureFullHeart, nullptr, &dest);
        } else {
            SDL_RenderCopy(pRenderer, pTextureEmptyHeart, nullptr, &dest);
        }
    }
}

void Game::displayScore() {
    SDL_Color textColor = {255, 255, 255};
    std::string stringScore = "Score : " + std::to_string(score);
    pSurfaceTextScore = TTF_RenderText_Solid(pFont, stringScore.c_str(), textColor);
    if (!pSurfaceTextScore) {
        std::cout << "Erreur lors de la création de la surface de score : " << SDL_GetError() << std::endl;
    }
    pTextureTextScore = SDL_CreateTextureFromSurface(pRenderer, pSurfaceTextScore);
    if (!pTextureTextScore) {
        std::cout << "Erreur lors de la création du rendu de score : " << SDL_GetError() << std::endl;
    }
    SDL_Rect destRect = {50, 50, pSurfaceTextScore->w, pSurfaceTextScore->h};
    SDL_RenderCopy(pRenderer, pTextureTextScore, nullptr, &destRect);
    SDL_FreeSurface(pSurfaceTextScore);
    SDL_DestroyTexture(pTextureTextScore);
}

void Game::regulateFps() {
    Uint32 targetFrameTime = 1000 / FPS; // obtention du temps d'une frame en ms
    Uint32 elapsedFrameTime = SDL_GetTicks() - lastFrameTime;

    if (elapsedFrameTime < targetFrameTime) {
        SDL_Delay(targetFrameTime - elapsedFrameTime);
    }
}

SDL_Renderer *Game::getPRenderer() const {
    return pRenderer;
}

void Game::setPRenderer(SDL_Renderer *pRenderer) {
    Game::pRenderer = pRenderer;
}

int Game::getScore() const {
    return score;
}

void Game::setScore(int score) {
    Game::score = score;
}

int Game::getLifeNb() const {
    return lifeNb;
}

void Game::setLifeNb(int lifeNb) {
    Game::lifeNb = lifeNb;
}

bool Game::isActive() const {
    return active;
}

void Game::setActive(bool active) {
    Game::active = active;
}

std::vector<Trash> &Game::getTrashes() {
    return trashes;
}

void Game::setTrashes(const std::vector<Trash> &trashes) {
    Game::trashes = trashes;
}

Rocket &Game::getRocket() {
    return rocket;
}

void Game::setRocket(const Rocket &rocket) {
    Game::rocket = rocket;
}

SDL_Window *Game::getPWindow() const {
    return pWindow;
}

void Game::setPWindow(SDL_Window *pWindow) {
    Game::pWindow = pWindow;
}

void Game::setLastFrameTime(Uint32 lastFrameTime) {
    Game::lastFrameTime = lastFrameTime;
}

void Game::setDevMode(bool devMode) {
    Game::devMode = devMode;
}

bool Game::isDevMode() {
    return devMode;
}
