#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "../Module.h"
#include "../Core/Render/Animation.h"
#include "../../Utils/p2Point.h"
#include "../../Utils/Directions.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module {

public:
	ModulePlayer(bool startEnabled);
	~ModulePlayer();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	void OnCollision(Collider* c1, Collider* c2) override;

	void PlaceHolderMove();
	void GetInputDirection();
	void ApplyMovement();

	int lives = 3;
	bool godMode = false;
	bool alive = true;
	iPoint position;
	iPoint positionAnterior;
	bool stopGame = false;
	int speed = 5;
	SDL_Texture* texturePlayer = nullptr;
	Collider* collider = nullptr;
	Collider* secCollider = nullptr;

private:
	int _numFrames = 6; // Frames que tiene cada fila
	int _start_time;
	Directions _actualDirection;
	Animation* _currentAnimation = nullptr;

	Animation _eastAnim;
	Animation _weastAnim;
};

#endif 