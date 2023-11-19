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
#include "PreScene.h"

PreScene::PreScene() : Module()
{
	name.Create("Prescene");
}

PreScene::~PreScene()
{
}

bool PreScene::Awake(pugi::xml_node config)
{
	LOG("Loading PreScene");
	return true;
}

bool PreScene::Start()
{
	app->modules[6]->active = false;
	app->modules[7]->active = false;
	
	img = app->tex->Load("Assets/Textures/Startup Screen.png");
	rectImg = {0, 0, 320, 222};
	return true;
}

bool PreScene::PreUpdate()
{
	return true;
}

bool PreScene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_UP)
	{
		// Passa a l'escena joc
		app->modules[6]->active = true;		
		app->modules[5]->active = false;		
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_UP)
	{
		// Passa a l'escena game over
		app->modules[7]->active = true;
		app->modules[5]->active = false;
	}

	return true;
}

bool PreScene::PostUpdate()
{
	app->render->DrawTexture(img, 0, 0, &rectImg);
	app->hud->PaintSentence("Inicio juego - pre scena", { 0,0 });
	return true;
}

bool PreScene::CleanUp()
{
	LOG("Freeing prescene");
	return true;
}
