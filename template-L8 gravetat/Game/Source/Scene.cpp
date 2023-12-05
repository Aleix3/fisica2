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


	
	pbody2 = app->physics->CreateCircle(159, 159, 15, bodyType::DYNAMIC);

	

#pragma region Cos1
	pbody = app->physics->CreateCircle(100, 100, 25, bodyType::DYNAMIC);

	b2Vec2 forceToApply(200.0f, 0.0f);

	int x, y;
	pbody->GetPosition(x, y);

	int width = 50;
	int height = 50;

	b2Vec2 pointOfApplication(PIXEL_TO_METERS(x + width), PIXEL_TO_METERS(y + height));

	pbody->body->ApplyForce(forceToApply, pointOfApplication, true);
#pragma endregion


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
	


	iPoint mousePos;
	app->input->GetMousePosition(mousePos.x, mousePos.y);

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) 
	{
		app->physics->CreateCircle(mousePos.x, mousePos.y, 15, bodyType::DYNAMIC);
	}
	

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

//void Scene::calculateGravityForce(const Body& body1, const Body& body2, double& fx, double& fy)
//{
//	double dx = body2.x - body1.x;
//	double dy = body2.y - body1.y;
//	double distance = sqrt(dx * dx + dy * dy);
//
//	double forceMagnitude = (G * body1.mass * body2.mass) / (distance * distance);
//	fx = forceMagnitude * (dx / distance);
//	fy = forceMagnitude * (dy / distance);
//}
