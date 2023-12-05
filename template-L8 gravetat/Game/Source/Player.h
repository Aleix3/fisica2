#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "SDL/include/SDL.h"
#include "Box2D/Box2D/Box2D.h"

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void Reset();

public:

	pugi::xml_node config;


	

	//Audio fx
	int pickCoinFxId;

	// L07 DONE 5: Add physics to the player - declare a Physics body
	PhysBody* pbody;

	 // Color rojo en formato RGBA
	
};

#endif // __PLAYER_H__