#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Game.hpp"
#include <SDL_mixer.h>

class GameObject
{
protected:
	int xpos, ypos;
	SDL_Texture* objectTexture = nullptr;
	SDL_Rect srcR, destR;
	bool isMoving = false;
	float launchedForce = 0;
	float force = 0;
	int launchedVelocity[2];
	int velocity[2];
	const float friction = 0.5;
	const float reduc = 5;
	Mix_Chunk* hit = NULL;
	Mix_Chunk* impact = NULL;
	int health = 3;



public:
	GameObject(const char* texture, int x, int y);
	~GameObject();
	void Update();
	void Render();
	void getPos(int* x, int* y);
	void launchBall(float force, int velocity[2]);
	void SetTexture(SDL_Texture* texture);
	void GetDamage();
	int GetHealth();

};

#endif

