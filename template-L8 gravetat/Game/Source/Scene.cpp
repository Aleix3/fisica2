#include "Scene.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "Item.h"
#include "Physics.h"
#include "Defs.h"
#include "Log.h"
#include "Score.h"
#include "Hud.h"
#include "SDL_image/include/SDL_image.h"

Scene::Scene() : Module()
{
	name.Create("scene");

}

// Destructor
Scene::~Scene() {}

// Called before render is available
bool Scene::Awake(pugi::xml_node config)
{
	LOG("Loading Scene");
	bool ret = true;
	


	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	_texturaGeneral = app->tex->Load("Assets/Textures/SpaceCadet3DPinball.png");
	_texball = app->tex->Load("Assets/Textures/ball.png");
	//_rectEscenari = { 0, 0, 1040, 855 };

	_rectPelota = { 0,0,15,15 };


	app->physics->CreateRectangle(388, 125, 5, 20, bodyType::STATIC);
	app->physics->CreateRectangle(352, 125, 5, 20, bodyType::STATIC);
	app->physics->CreateRectangle(125, 387, 5, 20, bodyType::STATIC);
	app->physics->CreateRectangle(158, 397, 5, 20, bodyType::STATIC);

	if (app->score != NULL) {
		app->score->Reset();
	}

	_texturaSprite_ = app->tex->Load("Assets/Textures/Game_Over.png");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{	
	bool ret = true;
	


	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}