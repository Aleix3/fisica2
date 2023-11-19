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
#include "gameOver.h"
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
		app->escenaActiva = 1;
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_UP)
	{
		// Passa a l'escena game over
		app->escenaActiva = 2;
	}

	return true;
}

bool PreScene::PostUpdate()
{
	return true;
}

bool PreScene::CleanUp()
{
	LOG("Freeing prescene");
	return true;
}
