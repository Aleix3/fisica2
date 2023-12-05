#ifndef __HUD_H__
#define __HUD_H__

#include <vector>
#include <string>
#include "App.h"
#include "SDL/include/SDL.h" 
#include "SDL_image/include/SDL_image.h" 

#include "../Module.h"

struct abecedari {
	char lletra;
	int posicio;
};


class Hud : public Module {

public:
	Hud();
	~Hud();

	bool Start() override;
	bool Update();
	bool PostUpdate();
	bool CleanUp();

	void PaintSentence(std::string sentenceToPaint, iPoint positionToPaint);


private:
	int sizeVector;
	int widthLetter = 15;

	std::vector<abecedari> vectorABC;

	SDL_Texture* textureFont = nullptr;
	SDL_Texture* textureIcons = nullptr;

	int PosLetter(char leterToSearch);
	int LoadVector();

	//IMPRIMEIX ELS CARÀCTER DEL VECTOR 
};

#endif