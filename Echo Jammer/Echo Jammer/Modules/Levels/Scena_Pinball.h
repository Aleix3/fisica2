#ifndef __SCENE_PINBALL_H__
#define __SCENE_PINBALL_H__

#include "../../Application/FileNames.h"
#include "../Module.h"
#include "../Core/Render/Animation.h"

struct SDL_Texture;

class Scena_Pinball : public Module {

public:
	Scena_Pinball(bool startEnabled);
	~Scena_Pinball();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2) override;

private:
	// Maquina estats
	
};

#endif