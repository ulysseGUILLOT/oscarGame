//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_GAME_H
#define OSCARGAME_GAME_H

#include "header.h"
#include "Trash.h"
#include "Rocket.h"

class Game {
private:
    int score;
    int lifeNb;
    bool active;

    Uint32 lastFrameTime;

    std::vector <Trash> trashes;
    Rocket rocket;

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    SDL_Surface* pSurfaceBackground;
    SDL_Texture* pTextureBackground;

    SDL_Surface* pSurfaceEarth;
    SDL_Texture* pTextureEarth;

public:
    Game();
    ~Game();
    void initSdl();
    void initWindow();
    void initRenderer();
    void presentRenderer();
    void regulateFps();
    void addTrash();

    SDL_Renderer* getPRenderer() const;
    void setPRenderer(SDL_Renderer *pRenderer);
    int getScore() const;
    void setScore(int score);
    int getLifeNb() const;
    void setLifeNb(int lifeNb);
    bool isActive() const;
    void setActive(bool active);
    std::vector<Trash> &getTrashes();
    void setTrashes(const std::vector<Trash> &trashes);
    Rocket &getRocket();
    void setRocket(const Rocket &rocket);
    SDL_Window *getPWindow() const;
    void setPWindow(SDL_Window *pWindow);
    void setLastFrameTime(Uint32 lastFrameTime);
};


#endif //OSCARGAME_GAME_H
