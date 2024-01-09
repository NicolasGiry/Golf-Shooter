#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Zombie.hpp"
#include "Map.hpp"
#include <ctime>
#include <cmath>
#include <vector>

#define MAX_ZOMBIES 10

using namespace std;


GameObject* player;
Zombie* zombies[MAX_ZOMBIES];
int nb_zombies = 0;
int Game::difficulte = 0;
int next_spawn;
Map* map;
int mousePos[2] = { 0,0 };
float force = 0;
bool touchingBall = false;

SDL_Renderer* Game::renderer = nullptr;
int Game::score = 0;

Game::Game()
{
    
}

Game::~Game() 
{

}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Initialisation..." << endl;

        if (window = SDL_CreateWindow(title, xpos, ypos, width, height, flags)) {
            cout << "Window created" << endl;
        }

        if (renderer = SDL_CreateRenderer(window, -1, 0)) {
            SDL_SetRenderDrawColor(renderer, 48,40,50,255);
            cout << "Renderer created" << endl;
        }

        isRunning = true;

        t = time(nullptr);

        // START: Initialisation des objets

        player = new GameObject("assets/player.png", 64, 224);
        srand(t);
        next_spawn = rand() % 300 + 60;


        //zombie = new Zombie(800, 224);
        map = new Map();

        // FIN START

    } else {
        isRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&mousePos[0], &mousePos[1]);
            int playerPos[2];
            player->getPos(&playerPos[0], &playerPos[1]);
            if ((mousePos[0] <= playerPos[0] + 32 && mousePos[0] >= playerPos[0]) && (mousePos[1] <= playerPos[1] + 32 && mousePos[1] >= playerPos[1]) ) {
                touchingBall = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (touchingBall) {
                int newMousePos[2] = { 0,0 };
                SDL_GetMouseState(&newMousePos[0], &newMousePos[1]);
                int velocity[2] = { 0,0 };
                velocity[0] = mousePos[0] - newMousePos[0];
                velocity[1] = mousePos[1] - newMousePos[1];
                force = calculerDistance(mousePos, newMousePos);
                if (force > 150) {
                    force = 150;
                }if (velocity[0] > 150) {
                    velocity[0] = 150;
                }if (velocity[1] > 150) {
                    velocity[1] = 150;
                }if (velocity[0] < -150) {
                    velocity[0] = -150;
                }if (velocity[1] <  -150) {
                    velocity[1] = -150;
                }
                cout << "force = " << force << "velocity = " << velocity[0] << ", " << velocity[1] << endl;
                touchingBall = false;
                if (force > 0) {
                    player->launchBall(force, velocity);
                }
                    
            }
            break;
        
    }
}

float Game::calculerDistance(int pos1[2], int pos2[2]) {
    return sqrtf((float) (pos1[0] - pos2[0]) * (pos1[0] - pos2[0]) + (pos1[1] - pos2[1]) * (pos1[1] - pos2[1]));
}

void Game::update() {
    // calcul fps
    cnt++;
    /*if (time(nullptr)-t == 1) {
        cout << "fps : " << cnt << endl;
        cnt = 0;
        t = time(nullptr);
    }*/
    // fin calcul fps

    //zombie->Update();
    if (cnt == next_spawn) {
        zombies[nb_zombies] = new Zombie(rand() % 200 + 700, rand() % 400 + 64, player);
        nb_zombies = (nb_zombies+1) % MAX_ZOMBIES;
        next_spawn = rand() % (500-Game::difficulte) + 30;
        cnt = 0;
        Game::difficulte++;
    }

    for (int i = 0; i < MAX_ZOMBIES; i++) {
        if (zombies[i] != NULL) {
            zombies[i]->Update();
        }
    }

    player->Update();
    if (player->GetHealth() <= 0) {
        Lose();
    }

    /*if (touchingBall) {
        int currentMousePos[2] = { 0,0 };
        SDL_GetMouseState(&currentMousePos[0], &currentMousePos[1]);
        SDL_RenderDrawLine(renderer, mousePos[0], mousePos[1], currentMousePos[0], currentMousePos[1]);
        SDL_RenderPresent(renderer);
    }*/
    
}

void Game::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    for (int i = 0; i < MAX_ZOMBIES; i++) {
        if (zombies[i] != NULL) {
            zombies[i]->Render();
        }
    }
    player->Render();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game cleaned" << endl;
}

bool Game::running() {
    return isRunning;
}

void Game::Lose() {
    cout << "GameOver" << endl;
    clean();
}