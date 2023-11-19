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
	return true;
}

bool PostScene::PostUpdate()
{
	return true;
}

bool PostScene::CleanUp()
{
	LOG("Freeing postscene");
	return true;
}
