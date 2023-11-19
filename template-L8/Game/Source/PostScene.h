#ifndef __POSTSCENE_H__
#define __POSTSCENE_H__

#include "Module.h"
#include "Player.h"
#include "Score.h"
#include "Animation.h"

struct SDL_Texture;

class PostScene : public Module{

public:
	PostScene();
	virtual ~PostScene();
	bool Awake(pugi::xml_node config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

private:
	Score* score;
	SDL_Texture* img;
	float textPosX, textPosY = 0;



};

#endif // __SCENE_H__