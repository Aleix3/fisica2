#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Item.h"
#include "Physics.h"
#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

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
	
	PhysBody* c1 = app->physics->CreateRectangle(100, 550, 256, 64, STATIC);
	c1->ctype = ColliderType::PLATFORM;
	//Music is commented so that you can add your own music
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	//Get the size of the window
	app->win->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	app->tex->GetSize(_textura_aspid, texW, texH);

	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;

	position.x = 100;
	position.y = 100;
	

	// L07 DONE 5: Add physics to the player - initialize physics body
	
	pbody = app->physics->CreateCircle(position.x, position.y, 29, bodyType::DYNAMIC);


	_rectEscenari = { 0, 0, 570, 470 };

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
	b2Vec2 velocity = pbody->body->GetLinearVelocity();

	//L02 DONE 3: Make the camera movement independent of framerate
	float camSpeed = 1;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		_graus = 0;
		_angle = _graus * M_PI / 180; // Angle en radians
		_temps = 0;

		_velocitatInicial_Y += 0.2 ;

		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;

		
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		velocity.y = -_velocitat_Y;
		pbody->body->SetLinearVelocity(velocity);
		_velocitatInicial_Y = 5;
	}

	b2Transform pbodyPos = pbody->body->GetTransform();

	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - 29;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - 29;

	// Renders the image in the center of the screen 
	//app->render->DrawTexture(img, (int)textPosX, (int)textPosY);

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	_aspidAnimation.Update();
	app->render->DrawTexture(_textura_aspid, _rectAspid.x, _rectAspid.y, &_aspidAnimation.GetCurrentFrame());
	app->render->DrawTexture(_texturaGeneral, 0, 0, &_rectEscenari);

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
