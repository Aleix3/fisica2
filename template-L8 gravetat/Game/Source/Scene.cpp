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
	_imgTerra = app->tex->Load("Assets/Textures/Terra.png");
	_imgLluna = app->tex->Load("Assets/Textures/Lluna.png");


	app->physics->CreateCircle(100, 100, 25, bodyType::STATIC);
	app->physics->CreateCircle(100, 100, 25, bodyType::STATIC);	

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