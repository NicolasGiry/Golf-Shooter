#ifndef GAME_hpp
#define GAME_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game {
private:
    int t;
    int cnt = 0;
    bool isRunning;
    SDL_Window *window;

public:

    static SDL_Renderer* renderer;
    static int score;
    static int difficulte;

    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();
    void Lose();

    bool running();
    float calculerDistance(int pos1[2], int pos2[2]);


};

#endif