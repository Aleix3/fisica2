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
#include "gameOver.h"
#include "SDL_image/include/SDL_image.h"
#include "PreScene.h"

PreScene::PreScene()
{
}

PreScene::~PreScene()
{
}

bool PreScene::Awake(pugi::xml_node config)
{
	return false;
}

bool PreScene::Start()
{
	return false;
}

bool PreScene::PreUpdate()
{
	return false;
}

bool PreScene::Update(float dt)
{
	return false;
}

bool PreScene::PostUpdate()
{
	return false;
}
