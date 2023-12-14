#ifndef __MODULEANIMATION_H__
#define __MODULEANIMATION_H__

#include <vector>
#include <string>
#include "App.h"
#include "Module.h"
#include "Player.h"
#include "Score.h"
#include "Animation.h"
#include "Render.h"
#include "SDL/include/SDL.h" 
#include "SDL_image/include/SDL_image.h" 

#include "../Module.h"



class ModuleAnimation : public Module {

public:
	ModuleAnimation();
	~ModuleAnimation();
	bool Awake(pugi::xml_node config);
	bool Start() override;
	bool Update();
	bool PostUpdate();
	bool CleanUp();

private:
	SDL_Rect _rectLight1;
	Animation* currentAnimLight1 = nullptr;
	Animation AnimLight1;
	SDL_Rect _rectLight2;
	Animation* currentAnimLight2 = nullptr;
	Animation AnimLight2;
	SDL_Rect _rectLight3;
	Animation* currentAnimLight3 = nullptr;
	Animation AnimLight3;
	SDL_Rect _rectLight4;
	Animation* currentAnimLight4 = nullptr;
	Animation AnimLight4;
	SDL_Rect _rectLight5;
	Animation* currentAnimLight5 = nullptr;
	Animation AnimLight5;
	SDL_Rect _rectLight6;
	Animation* currentAnimLight6 = nullptr;
	Animation AnimLight6;

	SDL_Rect _rectArrow1;
	Animation* currentAnimArrow1 = nullptr;
	Animation AnimArrow1;
	SDL_Rect _rectArrow2;
	Animation* currentAnimArrow2 = nullptr;
	Animation AnimArrow2;
	SDL_Rect _rectSpring;

	SDL_Texture* _texturaSprite = nullptr;
	//SDL_Texture* _texturaGeneral = nullptr;

};

#endif
