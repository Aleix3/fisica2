#ifndef __SCENE_EXERCISI2_H__
#define __SCENE_EXERCISI2_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scena_Exercisi2 : public Module {

public:
	Scena_Exercisi2(bool startEnabled);
	~Scena_Exercisi2();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2) override;

	SDL_Texture* textura_fondo = nullptr;
	SDL_Texture* textura_plataform = nullptr;
	SDL_Texture* textura_link = nullptr;
	SDL_Rect rectFondo;

	bool ResetPlayerPosition = false;
	bool ResetPlatform = false;
	bool stopGame = false;
	int start_time;
	int velocitatNivell = 0;

private:
	Animation _jumpAnimation;

	int weigthNivell = 1000;
	int heightNivell = 465;

	bool saltActivat = false;
};

#endif