#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Game.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include <SDL_mixer.h>

class Zombie : public GameObject
{
private:
	static const int nbFrames = 4;
	int currentFrame = 0;
	SDL_Texture  *f0, *f1, *f2, *f3;
	int cnt = 0;
	GameObject *ball;
	bool isDead = false;
	Mix_Chunk* touch = NULL;


public:
	Zombie(int x, int y, GameObject *player);
	~Zombie();
	void Update();
	void Render();
	void ChangeFrame();
	bool IsTouched();
	void Die();
};
#endif
