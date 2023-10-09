#ifndef __MODULE_HUD_H__
#define __MODULE_HUD_H__

#include <vector>
#include <string>

#include <SDL.h> 
#include <SDL_image.h> 

#include "../Module.h"
#include "../../Utils/p2Point.h"

struct abecedari {
	char lletra;
	int posicio;
};


class ModuleHUD : public Module {

public:
	ModuleHUD(bool startEnabled);
	~ModuleHUD();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	void PaintSentence(std::string sentenceToPaint, iPoint positionToPaint);


private:	
	int sizeVector;
	int widthLetter = 25;

	std::vector<abecedari> vectorABC;	

	SDL_Texture* textureFont = nullptr;
	SDL_Texture* textureIcons = nullptr;

	int PosLetter(char leterToSearch);
	int LoadVector();

	//IMPRIMEIX ELS CARÀCTER DEL VECTOR 
};

#endif