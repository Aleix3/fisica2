#include "Scene_0.h"
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


Scene_0::Scene_0() : Module()
{
	name.Create("scene");

}

// Destructor
Scene_0::~Scene_0() {}

// Called before render is available
bool Scene_0::Awake(pugi::xml_node config)
{
	LOG("Loading Scene");
	bool ret = true;
	app->modules[6]->active = true;
	app->modules[7]->active = false;
	app->modules[8]->active = false;
	return ret;
}

// Called before the first frame
bool Scene_0::Start()
{
	app->modules[6]->active = true;
	app->modules[7]->active = false;
	app->modules[8]->active = false;

	if (app->modules[6]->active)
	{
#pragma region Cos1
		int x = 400, y = 400;
		int width = 120, height = 120;

		cos1 = app->physics->CreateCircle(x, y, width / 2, bodyType::DYNAMIC);
		cos1->GetPosition(x, y);
		b2MassData massDataCos1;
		b2Vec2 vectCos1 = { (float32)x,(float32)y };
		massDataCos1.mass = 150;
		massDataCos1.center = vectCos1;
		cos1->body->SetMassData(&massDataCos1);
		cos1->body->SetActive(false);

		b2Vec2 pointOfApplication(PIXEL_TO_METERS(x + width), PIXEL_TO_METERS(y + height));


#pragma endregion

#pragma region Cos2
		b2Vec2 forceToApply(4000.0f, 0.0f);
		cos2 = app->physics->CreateCircle(300, 250, 25, bodyType::DYNAMIC);
		b2MassData massData;
		b2Vec2 vect = { 150,150 };
		massData.mass = 10;
		massData.center = vect;
		cos2->body->SetMassData(&massData);
		cos2->body->ApplyForce(forceToApply, pointOfApplication, true);
#pragma endregion

		vectorDeCossos.push_back(cos1);
		vectorDeCossos.push_back(cos2);


	}


	return true;
}

bool Scene_0::PreUpdate()
{
	return true;
}
bool F2 = false;
bool Scene_0::Update(float dt)
{
	if (app->modules[6]->active)
	{

#pragma region Canvi escenes

		printf_s("1_Escena 1: %s ", app->modules[6]->active ? "true" : "false");
		printf_s("1_Escena 2: %s ", app->modules[7]->active ? "true" : "false");
		printf_s("1_Escena 3: %s ", app->modules[8]->active ? "true" : "false");
		printf_s("\n");
	}
		if (app->input->GetKey(SDLK_F2) == KEY_UP)
		{
			F2 = true;
			printf_s("Neteja escena 1");
			CleanUp();
			printf_s("Canvi escena 2");

#pragma region Cos3
			int x = 400, y = 400;
			int width = 120, height = 120;

			cos3 = app->physics->CreateCircle(x, y, width / 2, bodyType::DYNAMIC);
			cos3->GetPosition(x, y);
			b2MassData massDataCos1;
			b2Vec2 vectCos1 = { (float32)x,(float32)y };
			massDataCos1.mass = 150;
			massDataCos1.center = vectCos1;
			cos3->body->SetMassData(&massDataCos1);

			b2Vec2 forceToApply(50000.0f, 0.0f);
			b2Vec2 pointOfApplication2(PIXEL_TO_METERS(x + width), PIXEL_TO_METERS(y + height));
			cos3->body->ApplyForce(forceToApply, pointOfApplication2, true);


#pragma endregion

#pragma region Cos4
			b2Vec2 forceToApply2(50000.0f, 0.0f);
			cos4 = app->physics->CreateCircle(400, 100, 30, bodyType::DYNAMIC);
			b2MassData massData;
			b2Vec2 vect = { 150,150 };
			massData.mass = 80;
			massData.center = vect;
			cos4->body->SetMassData(&massData);
			cos4->body->ApplyForce(forceToApply2, pointOfApplication2, true);
#pragma endregion

			vectorDeCossos.push_back(cos3);
			vectorDeCossos.push_back(cos4);


		}
	
		
		if (app->input->GetKey(SDLK_F3) == KEY_DOWN)
		{
			printf_s("Neteja escena 1");
			CleanUp();
			app->modules[6]->active = false;
			app->modules[7]->active = false;
			app->modules[8]->active = true;
			printf_s("Canvi escena 3");
		}

#pragma endregion

		iPoint mousePos;
		app->input->GetMousePosition(mousePos.x, mousePos.y);

		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			PhysBody* cosTemporal;
			cosTemporal = app->physics->CreateCircle(mousePos.x, mousePos.y, 15, bodyType::DYNAMIC);

			b2Vec2 forceToApply(2200.0f, 0.0f);

			b2MassData massData;
			b2Vec2 vect = { (float32)mousePos.x, (float32)mousePos.y };
			massData.mass = 5;
			massData.center = vect;
			cosTemporal->body->SetMassData(&massData);

			cosTemporal->body->ApplyForce(forceToApply, { (float32)mousePos.x , (float32)mousePos.y }, true);

			vectorDeCossos.push_back(cosTemporal);
		}

		if (app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
		{
			PhysBody* cosTemporal;
			cosTemporal = app->physics->CreateCircle(mousePos.x, mousePos.y, 100, bodyType::DYNAMIC);
			b2Vec2 forceToApply(0.0f, 8000.0f);

			b2MassData massData;
			b2Vec2 vect = { (float32)mousePos.x, (float32)mousePos.y };
			massData.mass = 200;
			massData.center = vect;
			cosTemporal->body->SetMassData(&massData);

			/*cosTemporal->body->ApplyForce(forceToApply, { (float32)mousePos.x , (float32)mousePos.y }, true);*/

			vectorDeCossos.push_back(cosTemporal);
		}

		int sizeVector = vectorDeCossos.size();
		for (int i = 0; i < sizeVector; i++)
		{
			for (int k = 0; k < sizeVector; k++)
			{
				if (vectorDeCossos[i] != 0 || vectorDeCossos[k] != 0)
				{
					b2Vec2 forcaGravitatoria = ApplyGravity(vectorDeCossos[i], vectorDeCossos[k]);
					vectorDeCossos[i]->body->ApplyForce(forcaGravitatoria, { 0,0 }, true);
				}

			}
		}

	

	if (F2 == true)
	{
		if (app->input->GetKey(SDLK_F1) == KEY_UP)
		{
			CleanUp();

#pragma region Cos1
			int x = 400, y = 400;
			int width = 120, height = 120;

			cos1 = app->physics->CreateCircle(x, y, width / 2, bodyType::DYNAMIC);
			cos1->GetPosition(x, y);
			b2MassData massDataCos1;
			b2Vec2 vectCos1 = { (float32)x,(float32)y };
			massDataCos1.mass = 150;
			massDataCos1.center = vectCos1;
			cos1->body->SetMassData(&massDataCos1);

			b2Vec2 pointOfApplication(PIXEL_TO_METERS(x + width), PIXEL_TO_METERS(y + height));


#pragma endregion

#pragma region Cos2
			b2Vec2 forceToApply(4000.0f, 0.0f);
			cos2 = app->physics->CreateCircle(300, 250, 25, bodyType::DYNAMIC);
			b2MassData massData;
			b2Vec2 vect = { 150,150 };
			massData.mass = 10;
			massData.center = vect;
			cos2->body->SetMassData(&massData);
			cos2->body->ApplyForce(forceToApply, pointOfApplication, true);
#pragma endregion

			vectorDeCossos.push_back(cos1);
			vectorDeCossos.push_back(cos2);
			F2 = false;

		}
			
		
	}

	if (app->input->GetKey(SDLK_F3) == KEY_UP)
	{

		CleanUp();
	}

	return true;
}

// Called each loop iteration
bool Scene_0::PostUpdate()
{
	bool ret = true;



	return ret;
}

// Called before quitting
bool Scene_0::CleanUp()
{
	LOG("Freeing scene");

	int sizeVector = vectorDeCossos.size();

	if (sizeVector > 0)
	{
		for (int i = 0; i < sizeVector; i++)
		{
			app->physics->DestroyBody(vectorDeCossos[i]);
		}
		vectorDeCossos.clear();
	}
	return true;
}
