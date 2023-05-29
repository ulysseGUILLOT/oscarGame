//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_GAME_H
#define OSCARGAME_GAME_H

#include <string>
#include <vector>
#include "Trash.h"
#include "Rocket.h"

class Game {
private:
    int score;
    int lifeNb;
    bool active;
    std::string playerName;
    std::vector <Trash> trashes;
    Rocket rocket;
};


#endif //OSCARGAME_GAME_H
