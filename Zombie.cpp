#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(int x, int y, GameObject *player) : GameObject("assets/zombie_0.png", x, y), ball(player)
{
	f0 = TextureManager::LoadTexture("assets/zombie_0.png");
	f1 = TextureManager::LoadTexture("assets/zombie_1.png");
	f2 = TextureManager::LoadTexture("assets/zombie_2.png");
	f3 = TextureManager::LoadTexture("assets/zombie_3.png");
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Volume(-1, (MIX_MAX_VOLUME * 80) / 100);
	touch = Mix_LoadWAV("sounds/zombie.wav");
}

Zombie::~Zombie() {

}


void Zombie::Update() {
	if (!isDead) {
		srcR.h = 64;
		srcR.w = 64;
		srcR.x = 0;
		srcR.y = 0;

		destR.h = srcR.h;
		destR.w = srcR.w;
		destR.x = xpos;
		destR.y = ypos;

		if (cnt % 15 == 0) {
			currentFrame = (currentFrame + 1) % nbFrames;
			ChangeFrame();
		}
		cnt++;
		xpos-= 1 * (Game::difficulte/10 +1);

		if (IsTouched()) {
			Die();
		} if (xpos < 0) {
			ball->GetDamage();
			Die();
		}
	}
	
}

void Zombie::Render() {
	if (!isDead) {
		SDL_RenderCopy(Game::renderer, GameObject::objectTexture, &srcR, &destR);
	}
}

void Zombie::ChangeFrame() {
	switch (currentFrame) {
	case 0:
		GameObject::SetTexture(f0);
		break;

	case 1:
		GameObject::SetTexture(f1);
		break;

	case 2:
		GameObject::SetTexture(f2);
		break;

	case 3:
		GameObject::SetTexture(f3);
		break;

	default:
		break;
	}
}

bool Zombie::IsTouched() {
	int ballPos[2] = { 0,0 };
	int zombiePos[2] = { 0,0 };
	ball->getPos(&ballPos[0], &ballPos[1]);
	getPos(&zombiePos[0], &zombiePos[1]);
	return (ballPos[0] <= zombiePos[0] + 64 && ballPos[0] + 32 >= zombiePos[0]) && (ballPos[1] <= zombiePos[1] + 64 && ballPos[1] + 32 >= zombiePos[1]);
}

void Zombie::Die() {
	Mix_PlayChannel(1, touch, 0);
	Game::score += 10;
	std::cout << "Score = " << Game::score << std::endl;
	isDead = true;
}
