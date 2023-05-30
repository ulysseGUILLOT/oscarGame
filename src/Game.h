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

    std::vector <Trash> trashes;
    Rocket rocket;

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    SDL_Surface* pSurfaceBackground;
    SDL_Texture* pTextureBackground;

public:
    Game();
    ~Game();
    void initSdl();
    void initWindow();
    void initRenderer();
    void presentRenderer();

    SDL_Renderer* getPRenderer() const;
    void setPRenderer(SDL_Renderer *pRenderer);
    int getScore() const;
    void setScore(int score);
    int getLifeNb() const;
    void setLifeNb(int lifeNb);
    bool isActive() const;
    void setActive(bool active);
    const std::vector<Trash> &getTrashes() const;
    void setTrashes(const std::vector<Trash> &trashes);
    Rocket &getRocket();
    void setRocket(const Rocket &rocket);
    SDL_Window *getPWindow() const;
    void setPWindow(SDL_Window *pWindow);
};


#endif //OSCARGAME_GAME_H
