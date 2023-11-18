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

	PhysBody* c2 = app->physics->CreateRectangle(365, 850, 300, 10, bodyType::STATIC);

	c2->ctype = ColliderType::DIE;

	_velocitatInicial_Y = 2;
	_textura_ball = app->tex->Load("Assets/Textures/aspid3.png");	
	app->tex->GetSize(_textura_ball, texW, texH);
	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;
	position.x = 650; position.y = 730;
	pbody = app->physics->CreateCircle(position.x, position.y, 10, bodyType::DYNAMIC);

	pbody->listener = this;

	pbody->ctype = ColliderType::PLAYER;

	return true;
}

bool Player::Update(float dt)
{
	b2Transform pbodyPos = pbody->body->GetTransform();

	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - 10;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - 10;

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
		position.x = 650;
		position.y = 750;
		app->physics->DestroyBody(pbody);
		pbody = app->physics->CreateCircle(position.x, position.y, 10, bodyType::DYNAMIC);

		pbody->listener = this;

		pbody->ctype = ColliderType::PLAYER;

		reset = true;

	}
	
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
		pbody = app->physics->CreateCircle(position.x, position.y, 10, bodyType::DYNAMIC);

		pbody->listener = this;

		pbody->ctype = ColliderType::PLAYER;

		

	
		
		

}

// L07 DONE 6: Define OnCollision function for the player. 
void Player::OnCollision(PhysBody* physA, PhysBody* physB) {
	switch (physB->ctype)
	{
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		break;
	case ColliderType::ITEM:
		LOG("Collision ITEM");
		app->audio->PlayFx(pickCoinFxId);
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
	case ColliderType::BUMPER:
		LOG("Collision BUMPER");
		//app->score->AddPoints(50);
		break;
	default:
		break;
	}
}