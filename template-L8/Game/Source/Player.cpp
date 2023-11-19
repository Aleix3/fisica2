#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Score.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	//L03: DONE 2: Initialize Player parameters
	position = iPoint(config.attribute("x").as_int(), config.attribute("y").as_int());

	return true;
}

bool Player::Start() {

	PhysBody* c1 = app->physics->CreateRectangle(645, 820, 80, 10, bodyType::STATIC);

	c1->ctype = ColliderType::SALTO;

	PhysBody* c3 = app->physics->CreateRectangle(618, 775, 25, 10, bodyType::STATIC);

	c3->ctype = ColliderType::SALTO;

	PhysBody* c4 = app->physics->CreateRectangle(73, 772, 25, 10, bodyType::STATIC);

	c4->ctype = ColliderType::SALTO;

	PhysBody* c2 = app->physics->CreateRectangle(365, 850, 300, 10, bodyType::STATIC);

	c2->ctype = ColliderType::DIE;

	sfx_Bumper = app->audio->LoadFx("Assets/Audio/sfx/Bumper.wav");
	_velocitatInicial_Y = 2;
	_textura_ball = app->tex->Load("Assets/Textures/aspid3.png");
	app->tex->GetSize(_textura_ball, texW, texH);
	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;
	position.x = 650; position.y = 730;
	pbody = app->physics->CreateCircle(position.x, position.y, 8, bodyType::DYNAMIC);

	pbody->listener = this;

	pbody->ctype = ColliderType::PLAYER;

	
	
	
	

	return true;
}

bool Player::Update(float dt)
{
	b2Transform pbodyPos = pbody->body->GetTransform();

	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - 8;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - 8;

	if (app->scene->suelo == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		{
			_graus = 0;
			_angle = _graus * M_PI / 180; // Angle en radians
			_temps = 0;

			_velocitatInicial_Y += 0.2;



			_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		}

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
		{
			velocity.y = -_velocitat_Y;
			pbody->body->SetLinearVelocity(velocity);
			_velocitatInicial_Y = 2;
			app->scene->suelo = false;
		}
	}

	if (reset == false)
	{
		app->score->restLives();
		if (app->score != NULL) {
			app->score->Reset();
		}
		position.x = 650;
		position.y = 750;
		app->physics->DestroyBody(pbody);
		pbody = app->physics->CreateCircle(position.x, position.y, 8, bodyType::DYNAMIC);

		pbody->listener = this;

		pbody->ctype = ColliderType::PLAYER;

		reset = true;

	}

	//SDL_Rect ballRect = { position.x - 8, position.y - 8, 16, 16 };

	//Uint8 r = 255, g = 0, b = 0, a = 255; // Color rojo en formato RGBA

	//Render* render = app->render;
	//render->DrawRectangle(ballRect, r, g, b, a, true, true);

	return true;
}

bool Player::CleanUp()
{
	return true;
}

void Player::Reset()
{

	position.x = 650;
	position.y = 750;
	app->physics->DestroyBody(pbody);
	pbody = app->physics->CreateCircle(position.x, position.y, 8, bodyType::DYNAMIC);

	pbody->listener = this;

	pbody->ctype = ColliderType::PLAYER;

		app->score->lives = 3;



}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {
	switch (physB->ctype)
	{
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		break;
	case ColliderType::ITEM:
		LOG("Collision ITEM");
		//app->audio->PlayFx(pickCoinFxId);
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	case ColliderType::SALTO:
		LOG("Collision SALTO");
		app->scene->suelo = true;
		break;
	case ColliderType::DIE:
		LOG("Collision SALTO");
		reset = false;

		break;
	case ColliderType::BUMPER1:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper1Hit = true;
			app->score->AddPoints(50);
			//	app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER2:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper2Hit = true;
			//app->score->CheckCombo1();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER3:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper3Hit = true;
			//app->score->CheckCombo1();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER4:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper4Hit = true;
			//app->score->CheckCombo1();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER5:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper5Hit = true;
			//app->score->CheckCombo2();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER6:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper6Hit = true;
			//app->score->CheckCombo2();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER7:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper7Hit = true;
			//app->score->CheckCombo2();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	default:
		break;
	}
}


