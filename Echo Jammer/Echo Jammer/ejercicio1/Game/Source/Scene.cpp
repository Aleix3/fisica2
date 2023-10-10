#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

int boxX = 200;
int boxY = 320;

int plX = 1000;
int plY = 500;

int plX2 = 1000;
int plY2 = 500;

int direcction = boxX;

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
	img = app->tex->Load("Assets/Textures/caja.png");

	img2 = app->tex->Load("Assets/Textures/planta.png");

	img3 = app->tex->Load("Assets/Textures/planta2.png");

	img4 = app->tex->Load("Assets/Textures/suelo.png");

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
	
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		boxX -= 4; // Move left
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		boxX += 4; // Move right
	}

	

	//Get the size of the window
	uint windowW, windowH;
	app->win->GetWindowSize(windowW, windowH);



	//Get the size of the texture
	uint texW, texH;
	app->tex->GetSize(img, texW, texH);
	app->tex->GetSize(img2, texW, texH);

	
	int sentido = 0;

	if (boxX > (plX - 300) && boxX < plX + 120)
	{
		plY = 2000;
		plY2 = 550;


		if (direcction < boxX || (direcction == boxX && sentido == 0))
		{
			sentido = -1;
			app->render->DrawTexture(img3, plX2, plY2, NULL, NULL, 60);
			app->render->DrawTexture(img, boxX, boxY);
		}

		else if (direcction > boxX || (direcction == boxX && sentido == 0))
		{
			sentido = 1;
			app->render->DrawTexture(img3, plX2, plY2, NULL, NULL, -60);
			app->render->DrawTexture(img, boxX, boxY);
		}

		
		if (sentido == 1)
		{
			app->render->DrawTexture(img3, plX2, plY2, NULL, NULL, 60);
			app->render->DrawTexture(img, boxX, boxY);
			sentido = 0;
		}

		else if (sentido == -1)
		{
			app->render->DrawTexture(img3, plX2, plY2, NULL, NULL, 60);
			app->render->DrawTexture(img, boxX, boxY);
			sentido = 0;
		}

		

	}
	else if (boxX > (plX + 100) || boxX < plX + 120)
	{
		plY = 2000;
		plY2 = 500;
		app->render->DrawTexture(img3, plX2, plY2);
		app->render->DrawTexture(img, boxX, boxY);
	}



	// Renders the image in the center of the screen
	/*app->render->DrawTexture(img, windowW /1 - texW / 1, windowH /1 - texH / 1);*/
	
		

		// Renders the image with scaled dimensions
	else
	{
		app->render->DrawTexture(img2, plX, plY);

		app->render->DrawTexture(img, boxX, boxY);
	}
		
	
	

	

	app->render->DrawTexture(img4, 0, 620);

	


	
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}