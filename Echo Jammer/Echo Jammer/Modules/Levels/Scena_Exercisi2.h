#ifndef __SCENE_EXERCISI2_H__
#define __SCENE_EXERCISI2_H__

#include "../../Application/FileNames.h"
#include "../Module.h"
#include "../Core/Render/Animation.h"

struct SDL_Texture;

class Scena_Exercisi2 : public Module {

public:
	Scena_Exercisi2(bool startEnabled);
	~Scena_Exercisi2();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

private:
	void OnCollision(Collider* c1, Collider* c2) override;

	SDL_Texture* textura_fondo = nullptr;
	SDL_Texture* textura_plataform = nullptr;
	SDL_Texture* textura_link = nullptr;
	SDL_Rect rectFondo;

	Animation _jumpAnimation;

	int weigthNivell = 1000;
	int heightNivell = 465;
	int start_time;
	int velocitatNivell = 0;
	int InitialVel = 0;

	bool isJumping = false; 
	int JumpForce = 0;    
	int JumpSpeed = 8;      
	int Gravity = 1;
	bool gravityOn = true;  

	bool saltActivat = false;
	bool stopGame = false;
	bool ResetPlayerPosition = false;
	bool ResetPlatform = false;
};

#endif