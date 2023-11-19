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
#include "PostScene.h"

PostScene::PostScene() : Module()
{
	name.Create("Postscene");
}

PostScene::~PostScene()
{
}

bool PostScene::Awake(pugi::xml_node config)
{
	LOG("Loading PostScene");
	return true;
}

bool PostScene::Start()
{

	return true;
}

bool PostScene::PreUpdate()
{
	return true;
}

bool PostScene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_UP)
	{
		// Passa a l'escena inicial
		app->modules[5]->active = true;
		app->modules[7]->active = false;
		app->modules[9]->active = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_UP)
	{
		// Passa a l'escena joc
		app->modules[6]->active = true;
		app->modules[9]->active = true;
		app->modules[7]->active = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		app->modules[6]->active = true;
		app->modules[7]->active = false;
	}
	

	return true;
}

bool PostScene::PostUpdate()
{
	img = app->tex->Load("Assets/Textures/Game_Over.png");
	rectImg = { 300, 500, 130, 21 };
	app->render->DrawTexture(img, 0, 0, &rectImg);
	return true;
}

bool PostScene::CleanUp()
{
	LOG("Freeing postscene");
	return true;
}
