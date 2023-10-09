#include "Scena_Exercisi3.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"
#include "../Core/ModuleInput.h"
#include <SDL_timer.h>

Scena_Exercisi3::Scena_Exercisi3(bool startEnabled) : Module(startEnabled) {
	// https://www.fisicalab.com/apartado/movimiento-parabolico
}

Scena_Exercisi3::~Scena_Exercisi3() {
}

bool Scena_Exercisi3::Start()
{
	// Load textures
	_textura_fondo = App->textures->Load(FI_Background.c_str());
	_textura_canon = App->textures->Load(FI_canon.c_str());
	_textura_boom = App->textures->Load(FI_boom.c_str());
	_textura_aspid = App->textures->Load(FI_aspid.c_str());

	// Load animations
	for (int i = 0; i < 6; i++)
		_shootAnimation.PushBack({ 48 * i, 0, 48, 48 });
	_shootAnimation.loop = false;
	_shootAnimation.speed = 0.2f;

	for (int i = 0; i < 4; i++)
		_aspidAnimation.PushBack({ 58 * i + 2, 0, 58, 57 });
	_aspidAnimation.loop = true;
	_aspidAnimation.speed = 0.2f;

	for (int i = 0; i < 4; i++)
		for (int k = 0; k < 6; k++)
			_explodeAnimation.PushBack({ 333 * k, 313 * i, 333, 313 });
	_explodeAnimation.loop = true;
	_explodeAnimation.speed = 0.2f;


	// Load aduio
	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	// Set position / sizes
	_rectFondo = { 0, 0, _weigthNivell, _heightNivell };
	_rectCanon = { 220, 210, 48, 48 };
	_rectBall = { 288, 0, 48, 48 };
	_rectAspid = { 800, 350, 58, 57 };
	_rectIdleCanon = { 48*4, 0, 48, 48 };

	// Initial position camera
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// Enable modules	
	App->collisions->Enable();

	// Initial position player
	App->player->position.x = 100;
	App->player->position.y = 300;

	// Load coliders
	App->collisions->AddCollider(_rectAspid, Collider::Type::TR_T1_SALT_LINK, this);

	return true;
}

Update_Status Scena_Exercisi3::Update() {

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN && !_start) {
		_boom = false;
		_start = true;
		_shooting = true;
		_shootAnimation.Reset();
		_start_time = SDL_GetTicks();
		LOG("SHOOT!");
	}

	if (_start) {
		_temps = ((float)SDL_GetTicks() - (float)_start_time) / 1000;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
		LOG("TEMPS: %f, X:%f, Y:%f, Yscreen: %f", _temps, _position_X, _position_Y, (SCREEN_HEIGHT - _position_Y));

		if ((SCREEN_HEIGHT - _position_Y) >= 380) {
			_start = false;
			_boom = true;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scena_Exercisi3::PostUpdate() {
	App->render->Blit(_textura_fondo, 0, 0, &_rectFondo);
	/*App->render->Blit(_textura_canon, 48, (SCREEN_HEIGHT - _position_Y), &_rectBall);*/


	if (_shooting) {
		_shootAnimation.Update();
		App->render->Blit(_textura_canon, _alturaInicialDeslpaçamentX, (SCREEN_HEIGHT - _alturaInicial), &_shootAnimation.GetCurrentFrame());
	}
	else
		App->render->Blit(_textura_canon, _alturaInicialDeslpaçamentX, (SCREEN_HEIGHT - _alturaInicial), &_rectIdleCanon);

	if (_start)
		App->render->Blit(_textura_canon, _position_X + _alturaInicialDeslpaçamentX, (SCREEN_HEIGHT - _position_Y), &_rectBall);


	if (!_boom) {
		_aspidAnimation.Update();
		App->render->Blit(_textura_aspid, _rectAspid.x, _rectAspid.y, &_aspidAnimation.GetCurrentFrame());
	}
	if (_boom) {
		_explodeAnimation.Update();
		App->render->Blit(_textura_boom, _rectAspid.x - 150, _rectAspid.y - 150, &_explodeAnimation.GetCurrentFrame());
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool Scena_Exercisi3::CleanUp() {
	App->player->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}

void Scena_Exercisi3::OnCollision(Collider* c1, Collider* c2) {

	if (c1->type == Collider::TR_OBJECTIU_1 && c2->type == Collider::PLAYER && !_shooting) {
		LOG("OBJECTIU ABATUT!");
		_shooting = true;
	}
}
