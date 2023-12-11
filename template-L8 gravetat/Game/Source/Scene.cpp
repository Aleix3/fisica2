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

#pragma region Cos1
	cos1 = app->physics->CreateCircle(100, 100, 25, bodyType::DYNAMIC);

	b2Vec2 forceToApply(15000.0f, 0.0f);

	int x, y;
	cos1->GetPosition(x, y);

	int width = 50;
	int height = 50;

	b2MassData massDataCos1;
	b2Vec2 vectCos1 = { 100,100 };
	massDataCos1.mass = 100;
	massDataCos1.center = vectCos1;
	cos1->body->SetMassData(&massDataCos1);

	b2Vec2 pointOfApplication(PIXEL_TO_METERS(x + width), PIXEL_TO_METERS(y + height));

	cos1->body->ApplyForce(forceToApply, pointOfApplication, true);
#pragma endregion

#pragma region Cos2
	cos2 = app->physics->CreateCircle(100, 200, 25, bodyType::DYNAMIC);
	b2MassData massData;
	b2Vec2 vect = { 150,150 };
	massData.mass = 50;
	massData.center = vect;
	cos2->body->SetMassData(&massData);
#pragma endregion


	vectorDeUrgotsCelestials.push_back(cos1);
	vectorDeUrgotsCelestials.push_back(cos2);

	return true;
}

bool Scene::PreUpdate()
{
	return true;
}

bool Scene::Update(float dt)
{
	iPoint mousePos;
	app->input->GetMousePosition(mousePos.x, mousePos.y);

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		app->physics->CreateCircle(mousePos.x, mousePos.y, 15, bodyType::DYNAMIC);
		PhysBody* cosTemporal;

		vectorDeUrgotsCelestials.push_back(cosTemporal);
	}

	int sizeVector = vectorDeUrgotsCelestials.size();
	for (int i = 0; i < sizeVector; i++)
	{
		for (int k = 0; k < sizeVector; k++)
		{
			b2Vec2 forcaGravitatoria = ApplyGravity(vectorDeUrgotsCelestials[i], vectorDeUrgotsCelestials[k]);
			vectorDeUrgotsCelestials[i]->body->ApplyForce(forcaGravitatoria, { 0,0 }, true);
		}
	}

	b2Vec2 forcaGravitatoria = ApplyGravity(cos1, cos2);	
	cos1->body->ApplyForce(forcaGravitatoria, {0,0}, true);
	b2Vec2 forcaGravitatoria2 = ApplyGravity(cos2, cos1);
	cos2->body->ApplyForce(forcaGravitatoria2, {0,0}, true);

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
