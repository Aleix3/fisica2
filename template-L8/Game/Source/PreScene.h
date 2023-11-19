#ifndef __PRESCENE_H__
#define __PRESCENE_H__

#include "Module.h"
#include "Player.h"
#include "Score.h"
#include "Animation.h"

struct SDL_Texture;

class PreScene : public Module{

public:
	PreScene();
	virtual ~PreScene();
	bool Awake(pugi::xml_node config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();


private:
	Score* score;
	SDL_Texture* img;
	SDL_Rect rectImg;
	float textPosX, textPosY = 0;

};

#endif // __SCENE_H__