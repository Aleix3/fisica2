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

	// Load animations
	for (int i = 0; i < 6; i++)
		_shootAnimation.PushBack({ 48 * i, 0, 48, 48 });
	_shootAnimation.loop = true;
	_shootAnimation.speed = 0.2f;

	// Load aduio
	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	// Set position / sizes
	_rectFondo = { 0, 0, _weigthNivell, _heightNivell };
	_rectCanon = { 220, 210, 48, 48 };

	// Initial position camera
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// Enable modules
	App->player->Enable();
	App->collisions->Enable();

	// Initial position player
	App->player->position.x = 100;
	App->player->position.y = 300;

	// Load coliders
	App->collisions->AddCollider({ 600 , 200, 20 , 220 }, Collider::Type::TR_T1_SALT_LINK, this);

	return true;
}

Update_Status Scena_Exercisi3::Update() {

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {
		_start = true;
		_start_time = SDL_GetTicks();
		LOG("SHOOT!");
	}

	if (_start) {
		_temps = SDL_GetTicks() - _start_time;
		_position_X = _velocitat_X * _temps;
		_position_Y = _velocitatInicial_Y - _gravetat * _temps;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scena_Exercisi3::PostUpdate() {
	App->render->Blit(_textura_fondo, 0, 0, &_rectFondo);

	if (_shooting)
	{
		_shootAnimation.Update();
		App->render->Blit(_textura_canon, 0, 0, &_shootAnimation.GetCurrentFrame());
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

	if (c1->type == Collider::TR_OBJECTIU_1 && c2->type == Collider::PLAYER && !_shooting)
	{
		LOG("OBJECTIU ABATUT!");
		_shooting = true;
	}
}
