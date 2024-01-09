#include "GameObject.hpp"
#include "TextureManager.hpp"


GameObject::GameObject(const char* texture, int x, int y) {
	objectTexture = TextureManager::LoadTexture(texture);
	xpos = x;
	ypos = y;
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Volume(-1, (MIX_MAX_VOLUME * 80) / 100);
	hit = Mix_LoadWAV("sounds/hit.wav");
	impact = Mix_LoadWAV("sounds/impact.wav");
}

GameObject::~GameObject() {

}

void GameObject::SetTexture(SDL_Texture* texture) {
	objectTexture = texture;
}

void GameObject::Update() {
	srcR.h = 32;
	srcR.w = 32;
	srcR.x = 0;
	srcR.y = 0;

	destR.h = srcR.h;
	destR.w = srcR.w;
	destR.x = xpos;
	destR.y = ypos;



	if (isMoving) {

		velocity[0] =  ((force / launchedForce) * launchedVelocity[0])/reduc;
		velocity[1] =  ((force / launchedForce) * launchedVelocity[1])/reduc;

		xpos += velocity[0];
		if (xpos+velocity[0] >= 896 or xpos+velocity[0] <= 32) {
			launchedVelocity[0] *= -1;
			force -= friction*25;
			Mix_PlayChannel(0, impact, 0);
		}
		
		ypos += velocity[1];
		if (ypos+velocity[1] >= 486 or ypos+velocity[1] <= 32) {
			launchedVelocity[1] *= -1;
			force -= friction*25;
			Mix_PlayChannel(0, impact, 0);
		}
		
		if (force > 0) {
			force -= friction;
		} else {
			isMoving = false;
		}
	}
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objectTexture, &srcR, &destR);
}

void GameObject::getPos(int* x, int* y)
{
	*x = xpos;
	*y = ypos;
}


void GameObject::launchBall(float f, int v[2]) {
	Mix_PlayChannel(5, hit, 0);
	launchedForce = f;
	force = f;
	velocity[0] = v[0];
	velocity[1] = v[1];
	launchedVelocity[0] = v[0];
	launchedVelocity[1] = v[1];
	isMoving = true;
}

void GameObject::GetDamage() {
	health--;
	std::cout << "health = " << health << std::endl;
}

int GameObject::GetHealth() {
	return health;
}
