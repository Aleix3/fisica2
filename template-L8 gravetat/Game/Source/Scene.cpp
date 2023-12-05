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
#include "SDL_image/include/SDL_image.h"

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
	_texturaGeneral = app->tex->Load("Assets/Textures/SpaceCadet3DPinball.png");
	_texball = app->tex->Load("Assets/Textures/ball.png");
	//_rectEscenari = { 0, 0, 1040, 855 };

	_rectPelota = { 0,0,15,15 };



	app->audio->PlayMusic("Assets/Audio/Pinball_th.mp3", 10.0f);
	app->hud->Start();

	app->physics->CreateRectangle(388, 125, 5, 20, bodyType::STATIC);
	app->physics->CreateRectangle(352, 125, 5, 20, bodyType::STATIC);
	app->physics->CreateRectangle(125, 387, 5, 20, bodyType::STATIC);
	app->physics->CreateRectangle(158, 397, 5, 20, bodyType::STATIC);

	if (app->score != NULL) {
		app->score->Reset();
	}

	_texturaSprite_ = app->tex->Load("Assets/Textures/Game_Over.png");

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
	player->Update(dt);

	if (app->score->GetLives() <= 0 && bucle == false) {
		app->modules[7]->active = true;
		app->modules[6]->active = false;
		app->modules[9]->active = false;
		bucle = true;
	}

	//L02 DONE 3: Make the camera movement independent of framerate
	float camSpeed = 1;

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_UP)
	{
		// Passa a l'escena inicial
		app->modules[5]->active = true;
		app->modules[6]->active = false;
		app->modules[9]->active = false;
		gameover = false;
	}
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_UP)
	{
		// Passa a l'escena inicial

		gameover = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_UP)
	{
		// Passa a l'escena game over
		app->modules[7]->active = true;
		app->modules[6]->active = false;
		app->modules[9]->active = false;
		/*app->modules[6]->active = false;*/
		app->audio->PlayFx(sfx_Over);
		gameover = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		AnimSpring.PushBack({ 610,635,14,42 });
		AnimSpring.PushBack({ 610,625,14,42 });
		AnimSpring.PushBack({ 610,615,14,42 });
		AnimSpring.PushBack({ 610,605,14,42 });
		AnimSpring.PushBack({ 610,595,14,42 });
		AnimSpring.PushBack({ 650, 241, 6,  6 });
		AnimSpring.loop = false;
		AnimSpring.speed = 0.1f;
		app->audio->PlayFx(sfx_Spring);
	}
	// cambiar angle de rotacio de la pala
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		_palaRight->body->ApplyTorque(-80.0f, true);
	}
	else
	{
		_palaRight->body->ApplyTorque(45.0f, true);
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		app->audio->PlayFx(sfx_Pala);
	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		_palaLeft->body->ApplyTorque(80.0f, true);
	}
	else
	{
		_palaLeft->body->ApplyTorque(-45.0f, true);
	}
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		app->audio->PlayFx(sfx_Pala);
	}
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		player->Reset();
		gameover = false;
	}


	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		app->render->camera.y += (int)ceil(camSpeed * dt);

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		app->render->camera.y -= (int)ceil(camSpeed * dt);

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		app->render->camera.x += (int)ceil(camSpeed * dt);

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		app->render->camera.x -= (int)ceil(camSpeed * dt);

	currentAnimBump1->Update();
	currentAnimBump2->Update();
	currentAnimBump3->Update();
	currentAnimBump4->Update();
	currentAnimBump5->Update();
	currentAnimBump6->Update();
	currentAnimBump7->Update();
	currentAnimLight1->Update();
	currentAnimLight2->Update();
	currentAnimLight3->Update();
	currentAnimLight4->Update();
	currentAnimLight5->Update();
	currentAnimLight6->Update();
	currentAnimArrow1->Update();
	currentAnimArrow2->Update();
	currentAnimSpring->Update();

	ballRect = { player->position.x, player->position.y, 16, 16 };

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	//app->render->DrawTexture(_texturaGeneral, 0, 0, &_rectEscenari);

	//Anim
	_rectBump1 = currentAnimBump1->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 185, 65, &_rectBump1);
	_rectBump2 = currentAnimBump2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 389, 157, &_rectBump2);
	_rectBump3 = currentAnimBump3->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 345, 229, &_rectBump3);
	_rectBump4 = currentAnimBump4->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 309, 175, &_rectBump4);
	_rectBump5 = currentAnimBump5->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 155, 435, &_rectBump5);
	_rectBump6 = currentAnimBump6->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 88, 415, &_rectBump6);
	_rectBump7 = currentAnimBump7->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 105, 465, &_rectBump7);

	_rectLight1 = currentAnimLight1->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 495, 85, &_rectLight1);
	_rectLight2 = currentAnimLight2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 548, 130, &_rectLight2);
	_rectLight3 = currentAnimLight3->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 573, 192, &_rectLight3);
	_rectLight4 = currentAnimLight4->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 584, 276, &_rectLight4);
	_rectLight5 = currentAnimLight5->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 598, 372, &_rectLight5);
	_rectLight6 = currentAnimLight6->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 613, 473, &_rectLight6);

	_rectArrow1 = currentAnimArrow1->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 290, 388, &_rectArrow1);
	_rectArrow2 = currentAnimArrow2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 477, 314, &_rectArrow2);
	_rectSpring = currentAnimSpring->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 663, 780, &_rectSpring);
	//
	bool ret = true;
	if (app->score != NULL) {
		app->hud->PaintSentence(std::to_string(app->score->GetScore()), { 770, 400 });
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->hud->PaintSentence(std::to_string(app->score->GetLives()), { 1080, 300 });

	if (app->modules[7]->active == true || gameover == true)
	{
		app->render->DrawTexture(_texturaSprite_, 363, 380);
	}
	render = app->render;


	app->render->DrawTexture(_texball, ballRect.x, ballRect.y, &_rectPelota);	
	app->render->DrawTexture(_texturaGeneral, 300, 765, &_rectPala1, 1, _palaRight->GetRotation());
	app->render->DrawTexture(_texturaGeneral, 440, 765, &_rectPala2, 1, _palaLeft->GetRotation());


	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::Create_circularBumper(int x, int y, int radious)
{
	PhysBody* circularBumper = app->physics->CreateCircle(x, y, radious, bodyType::STATIC);
	circularBumper->body->GetFixtureList()->SetRestitution(1.3f);

	circularBumper->ctype = ColliderType::BUMPER1;
}

void Scene::Create_rectangularBumper(int x, int y, int w, int h, float angle)
{
	PhysBody* rectangularBumper = app->physics->CreateRectangle(x, y, w, h, bodyType::STATIC);
	rectangularBumper->body->GetFixtureList()->SetRestitution(1.1f);
	int _angle = angle * M_PI / 180;
	b2Transform transform = rectangularBumper->body->GetTransform();
	transform.Set(transform.p, _angle);
	rectangularBumper->body->SetTransform(transform.p, transform.q.GetAngle());
	rectangularBumper->ctype = ColliderType::BUMPER;
}

