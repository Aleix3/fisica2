#ifndef __SCENE_EXERCISI3_H__
#define __SCENE_EXERCISI3_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scena_Exercisi3 : public Module {

public:
	Scena_Exercisi3(bool startEnabled);
	~Scena_Exercisi3();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2) override;

	SDL_Texture* textura_fondo = nullptr;
	SDL_Texture* textura_link = nullptr;
	SDL_Rect rectFondo;
	Collider* botcoll = nullptr;
	Collider* topcoll = nullptr;
	Collider* leftcoll = nullptr;
	Collider* raightcoll = nullptr;

	bool stopGame = false;
	int start_time;
	int velocitatNivell = 0;

private:
	Animation _deathAnim;
	Animation _jumpAnimation;

	int weigthNivell = 1000;
	int heightNivell = 465;

	bool saltActivat = false;
};

#endif