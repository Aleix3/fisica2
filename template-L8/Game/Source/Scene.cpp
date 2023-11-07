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

	// TODO: Change player -> ball with physics
	//Instantiate the player using the entity manager
	//Get player paremeters
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	//Assigns the XML node to a member in player
	player->config = config.child("player");

	

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	_velocitatInicial_Y = 2;
	// NOTE: We have to avoid the use of paths in the code, we will move it later to a config file
	PhysBody* c1 = app->physics->CreateRectangle(600, 735, 56, 64, STATIC);
	c1->ctype = ColliderType::PLATFORM;
	
	_texturaGeneral = app->tex->Load("Assets/Textures/SpaceCadet3DPinball2.png");
	_textura_aspid = app->tex->Load("Assets/Textures/aspid2.png");
	//Music is commented so that you can add your own music
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	//Get the size of the window
	app->win->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	app->tex->GetSize(_textura_aspid, texW, texH);

	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;

	position.x = 600; position.y = 730;
	

	// L07 DONE 5: Add physics to the player - initialize physics body
	
	pbody = app->physics->CreateCircle(position.x, position.y, 15, bodyType::DYNAMIC);


	for (int i = 0; i < 4; i++)
		_aspidAnimation.PushBack({ 29 * i + 2, 0, 29, 29 });
	_aspidAnimation.loop = true;
	_aspidAnimation.speed = 0.2f;

	_rectEscenari = { 0, 0, 1040, 855 };

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

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && suelo == true)
	{
		_graus = 0;
		_angle = _graus * M_PI / 180; // Angle en radians
		_temps = 0;

		_velocitatInicial_Y += 0.2;

		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;

		
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && suelo == true)
	{
		velocity.y = -_velocitat_Y;
		pbody->body->SetLinearVelocity(velocity);
		_velocitatInicial_Y = 2;
		suelo = false;
	}

	b2Transform pbodyPos = pbody->body->GetTransform();

	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - 15;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - 15;

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
	app->render->DrawTexture(_textura_aspid, position.x, position.y, &_aspidAnimation.GetCurrentFrame());
	//app->render->DrawTexture(_texturaGeneral, 0, 0, &_rectEscenari);

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
