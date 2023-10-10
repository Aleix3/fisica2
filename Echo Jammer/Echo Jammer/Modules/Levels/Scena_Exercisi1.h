#ifndef __SCENE_EXERCISI1_H__
#define __SCENE_EXERCISI1_H__

#include "../Module.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scena_Exercisi1 : public Module {

public:
	Scena_Exercisi1(bool startEnabled);
	~Scena_Exercisi1();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

private:
	int boxX = 200;
	int boxY = 320;

	int plX = 1000;
	int plY = 500;

	int plX2 = 1000;
	int plY2 = 500;

	int direcction = boxX;

	SDL_Texture* _caja;	
	SDL_Texture* _planta;
	SDL_Texture* _planta2;
	SDL_Texture* _suelo;
};

#endif // __SCENE_EXERCISI1_H__