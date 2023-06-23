//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_HEADER_H
#define OSCARGAME_HEADER_H

#define FPS 60
#define LIFENB 3
#define WSCREEN 1920
#define HSCREEN 1080
#define TITLE "OscarGame"

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>

// proto :
SDL_Color getPixelColor(const SDL_Surface *pSurface, int x, int y);
SDL_Joystick *connectJoystick();

#endif //OSCARGAME_HEADER_H
