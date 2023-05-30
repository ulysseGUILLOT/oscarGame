//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_GAME_H
#define OSCARGAME_GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include "Trash.h"
#include "Rocket.h"

#define LIFENB 3
#define WSCREEN 800
#define HSCREEN 600
#define TITLE "OscarGame"

class Game {
private:
    int score;
    int lifeNb;
    bool active;

    std::vector <Trash> trashes;
    Rocket rocket;

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

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
    const Rocket &getRocket() const;
    void setRocket(const Rocket &rocket);
    SDL_Window *getPWindow() const;
    void setPWindow(SDL_Window *pWindow);
};


#endif //OSCARGAME_GAME_H
