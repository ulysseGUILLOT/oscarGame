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

class Game {
private:
    int score;
    int lifeNb;

    std::vector <Trash> trashes;
    Rocket rocket;

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

public:
    Game();
    ~Game();
    void initSdl();
    void initWindow(std::string title, int width, int height);
    void initRenderer();
    void presentRenderer();
};


#endif //OSCARGAME_GAME_H
