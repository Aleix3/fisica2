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
#include "SDL_image/include/SDL_image.h"


Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
	AnimCirc1.PushBack({ 608,172,12,10 });
	AnimCirc1.PushBack({ 650, 241, 6,  6 });
	AnimCirc1.loop = false;
	AnimCirc1.speed = 0.05f;
	AnimCirc2.PushBack({ 254,245,12,10 });
	AnimCirc2.PushBack({ 650, 241, 6,  6 });
	AnimCirc2.loop = false;
	AnimCirc2.speed = 0.05f;
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
	currentAnimCirc1 = &AnimCirc1;
	_texturaSprite = app->tex->Load("Assets/Textures/SpaceSprites200.png");
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

	
	
	pbody->body->SetGravityScale(23);
	

	return true;
}

bool Player::Update(float dt)
{
	b2Transform pbodyPos = pbody->body->GetTransform();

	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - 8;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - 8;

	if (app->scene->suelo == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			_graus = 0;
			_angle = _graus * M_PI / 180; // Angle en radians
			_temps = 0;

			_velocitatInicial_Y += 0.2;



			_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		}

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
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

	
	return true;
}
bool Player::PostUpdate()
{
	
	_rectCirc1 = currentAnimCirc1->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 364, 96, &_rectCirc1);
	_rectCirc1 = currentAnimCirc1->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 329, 102, &_rectCirc1);
	_rectCirc1 = currentAnimCirc1->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 399, 102 ,&_rectCirc1);
	_rectCirc2 = currentAnimCirc2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 112, 367 ,&_rectCirc2);
	_rectCirc2 = currentAnimCirc2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 143, 374, &_rectCirc2);
	_rectCirc2 = currentAnimCirc2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 175, 382, &_rectCirc2);
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
	case ColliderType::RECTU:
		LOG("Collision RECTU");
		currentAnimCirc1->Update();
		currentAnimCirc2->Update();
		break;
	case ColliderType::BUMPER2:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper2Hit = true;
			CheckCombo1();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER3:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper3Hit = true;
			CheckCombo1();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER4:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper4Hit = true;
			CheckCombo1();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER5:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper5Hit = true;
			CheckCombo2();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER6:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper6Hit = true;
			CheckCombo2();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	case ColliderType::BUMPER7:
		LOG("Collision BUMPER");
		if (app->score != NULL) {
			bumper7Hit = true;
			CheckCombo2();
			app->score->AddPoints(50);
			app->audio->PlayFx(sfx_Bumper);
		}
		break;
	default:
		break;
	}
}

void Player::ResetCombo1() {
	bumper2Hit = false;
	bumper3Hit = false;
	bumper4Hit = false;
}

void Player::ResetCombo2() {
	bumper5Hit = false;
	bumper6Hit = false;
	bumper7Hit = false;
}


void Player::CheckCombo1() {
	if (bumper2Hit && bumper3Hit && bumper4Hit) {
		app->score->AddPoints(1000);
		ResetCombo1();
	}
}

void Player::CheckCombo2() {
	if (bumper5Hit && bumper6Hit && bumper7Hit) {
		app->score->AddPoints(1000);
		ResetCombo2();
	}
}

