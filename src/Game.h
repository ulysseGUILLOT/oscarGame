//
// Created by RBatty on 29/05/2023.
//

#ifndef OSCARGAME_GAME_H
#define OSCARGAME_GAME_H

#define NB_SPRITE_EXPLOSION 2

#include "header.h"
#include "Trash.h"
#include "Rocket.h"

class Game {
private:
    bool devMode;
    int score;
    int lifeNb;
    bool active;
    bool playing;
    bool gameOver;

    Uint32 lastFrameTime;

    std::vector<Trash> trashes;
    Rocket rocket;

    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

    SDL_Surface *pSurfaceBackground;
    SDL_Texture *pTextureBackground;

    SDL_Surface *pSurfaceEarth;
    SDL_Texture *pTextureEarth;

    SDL_Surface *pSurfaceFullHeart;
    SDL_Texture *pTextureFullHeart;

    SDL_Surface *pSurfaceEmptyHeart;
    SDL_Texture *pTextureEmptyHeart;

    std::vector<SDL_Surface *> pSurfaceExplosions;
    std::vector<SDL_Texture*> pTextureExplosions;
    int explosionState;
    int explosionX;
    int explosionY;

    SDL_Surface *pSurfaceCollision;

    TTF_Font *pFont;
    SDL_Surface *pSurfaceTextScore;
    SDL_Texture *pTextureTextScore;

    SDL_Surface *pSurfaceStartMenuText;
    SDL_Texture *pTextureStartMenuText;

    SDL_Surface *pSurfaceGameOverText;
    SDL_Texture *pTextureGameOverText;

    Mix_Chunk *pChunkMusicPlaying;
    int channelChunkMusicPlaying;
    Mix_Chunk *pChunkMusicStartMenu;
    int channelChunkMusicStartMenu;
    Mix_Chunk *pChunkLaunch;
    int channelChunkLaunch;
    Mix_Chunk *pChunkCollision;
    Mix_Chunk *pChunkScoreNotification;

public:
    Game();

    ~Game();

    void initSdl();

    void initWindow();

    void initRenderer();

    void renderStartScreen();

    void renderPlaying();

    void renderGameOver();

    void addTrash();

    void displayBackground();

    void displayStartMenuText();

    void displayGameOverText();

    void displayEarth();

    void displayHearts();

    void displayScore();

    void displayExplosion(bool collision);

    void regulateFps();

    Mix_Chunk *loadChunk(const char *path);

    int playChunk(Mix_Chunk *pSound, int loop);

    SDL_Renderer *getPRenderer() const;

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

    void setDevMode(bool devMode);

    bool isDevMode();

    Mix_Chunk *getPChunkMusic() const;

    void setPChunkMusic(Mix_Chunk *pChunkMusic);

    Mix_Chunk *getPChunkLaunch() const;

    void setPChunkLaunch(Mix_Chunk *pChunkLaunch);

    Mix_Chunk *getPChunkCollision() const;

    void setPChunkCollision(Mix_Chunk *pChunkCollision);

    int getChannelChunkLaunch() const;

    void setChannelChunkLaunch(int channelChunkLaunch);

    int getChannelChunkMusicStartMenu() const;

    bool isPlaying() const;

    void setPlaying(bool playing);

    bool isGameOver() const;

    void setGameOver(bool gameOver);

    Mix_Chunk *getPChunkMusicStartMenu() const;

    void setChannelChunkMusicStartMenu(int channelChunkMusicStartMenu);

    int getChannelChunkMusicPlaying() const;

    void setChannelChunkMusicPlaying(int channelChunkMusicPlaying);

    Mix_Chunk *getPChunkScoreNotification() const;

    void resetGame();

    void loadSpritesExplosion();
};


#endif //OSCARGAME_GAME_H
