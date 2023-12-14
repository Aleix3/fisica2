#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <vector>
#include <string>
#include "App.h"
#include "SDL/include/SDL.h" 
#include "SDL_image/include/SDL_image.h" 

#include "../Module.h"



class Collider : public Module {

public:
	Collider();
	~Collider();

	bool Start() override;
	bool Update();
	bool PostUpdate();
	bool CleanUp();

private:
	int sizeVector;
	int widthLetter = 15;


	SDL_Texture* textureFont = nullptr;
	SDL_Texture* textureIcons = nullptr;

};

#endif

