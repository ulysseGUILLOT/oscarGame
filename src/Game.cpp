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

    pSurfaceCollision = SDL_CreateRGBSurface(0, WSCREEN, HSCREEN, 32, 0, 0, 0, 0);
    if (!pSurfaceCollision) {
        std::cout << "Echec de la création de la surface de collision : " << SDL_GetError() << std::endl;
    }

    pSurfaceBackground = SDL_LoadBMP("../src/img/background.bmp");
    if (!pSurfaceBackground) {
        std::cout << "Echec de chargement du background : " << SDL_GetError() << std::endl;
    }
    pTextureBackground = SDL_CreateTextureFromSurface(pRenderer, pSurfaceBackground);
    if (!pTextureBackground) {
        std::cout << "Echec de la creation de la texture : " << SDL_GetError() << std::endl;
        active = false;
    }

    pSurfaceEarth = SDL_LoadBMP("../src/img/earth.bmp");
    if (!pSurfaceEarth) {
        std::cout << "Echec de chargement du background : " << SDL_GetError() << std::endl;
    }
    SDL_SetColorKey(pSurfaceEarth, SDL_TRUE, SDL_MapRGB(pSurfaceEarth->format, 0, 255, 255));
    pTextureEarth = SDL_CreateTextureFromSurface(pRenderer, pSurfaceEarth);
    if (!pTextureEarth) {
        std::cout << "Echec de la creation de la texture : " << SDL_GetError() << std::endl;
        active = false;
    }
}

Game::~Game() {
    rocket.~Rocket();
    SDL_DestroyTexture(pTextureBackground);
    SDL_DestroyTexture(pTextureEarth);
    SDL_DestroyRenderer(pRenderer);
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
    SDL_Rect dest = {0, 0, pSurfaceBackground->w, pSurfaceBackground->h};
    SDL_RenderCopy(pRenderer, pTextureBackground, NULL, &dest);

    //Affichage de la terre
    dest = {(WSCREEN / 2) - (pSurfaceEarth->w / 2), (HSCREEN / 2) - (pSurfaceEarth->h / 2), pSurfaceEarth->w,
            pSurfaceEarth->h};
    SDL_RenderCopy(pRenderer, pTextureEarth, NULL, &dest);

    // affichage de la fusée
    rocket.display(pRenderer, pSurfaceCollision);

    // affichage des déchets
    for (int i = 0; i < trashes.size(); i++) {
        trashes[i].toRender(pRenderer);
        trashes[i].testCollision(0, 0, pSurfaceCollision);
    }

    if (devMode) {
        SDL_Texture* pTextureDev = SDL_CreateTextureFromSurface(pRenderer, pSurfaceCollision);
        dest = {0, 0, WSCREEN, HSCREEN};
        SDL_RenderCopy(pRenderer, pTextureDev, nullptr,&dest);
        // nettoyage de la surface de collision après son affichage
        SDL_FillRect(pSurfaceCollision, nullptr, SDL_MapRGB(pSurfaceCollision->format, 0, 0, 0));
        SDL_DestroyTexture(pTextureDev);
    }

    // attend le temps necessaire pour obtenir 60fps
    regulateFps();

    // afficher le rendu total
    SDL_RenderPresent(pRenderer);
}

void Game::regulateFps() {
    Uint32 targetFrameTime = 1000 / FPS; // obtention du temps d'une frame en ms
    Uint32 elapsedFrameTime = SDL_GetTicks() - lastFrameTime;

    if (elapsedFrameTime < targetFrameTime) {
        SDL_Delay(targetFrameTime - elapsedFrameTime);
    }
}

void Game::addTrash() {
    Trash trash;
    trashes.push_back(trash);
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
