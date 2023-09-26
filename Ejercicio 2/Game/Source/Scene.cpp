#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "SDL/include/SDL.h"
#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	plataforma = { 150, 300, 300, 100 };
	plataforma2 = { 780, 300, 300, 100 };
//({ 613,686, 200, 80 });
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	sprite_png = app->tex->Load("Assets/Textures/sprite.png");
	/*LettersAnimationG = &AnimPlat;*/
	background_png = app->tex->Load("Assets/Textures/background.png");
	/*img = app->tex->Load("Assets/Textures/test.png");*/

	app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");
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
	//L02 TODO 3: Make the camera movement independent of framerate

	//if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	//	app->render->camera.y -= 1;

	//if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	//	app->render->camera.y += 1;

	//if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	//	app->render->camera.x -= 1;

	//if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	//	app->render->camera.x += 1;

	//Get the size of the window
	uint windowW, windowH;
	app->win->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	uint texW, texH;
	app->tex->GetSize(img, texW, texH);

	// Renders the image in the center of the screen
	app->render->DrawTexture(img, windowW /2 - texW / 2, windowH /2 - texH / 2);

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;
	/*app->render->DrawTexture(plataform_png, 613, 686, 200, 80);*/
	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	app->render->DrawTexture(background_png, 0, 0, NULL);
	app->render->DrawRectangle(plataforma, 255, 100, 30);
	app->render->DrawRectangle(plataforma2, 255, 100, 30);
	
	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	
	return true;
}
