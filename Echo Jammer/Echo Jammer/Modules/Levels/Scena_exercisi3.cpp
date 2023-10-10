#include "Scena_Exercisi3.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"
#include "../../Modules/Core/ModuleHUD.h"
#include "../Core/ModuleInput.h"
#include <SDL_timer.h>

Scena_Exercisi3::Scena_Exercisi3(bool startEnabled) : Module(startEnabled) {
	// https://www.fisicalab.com/apartado/movimiento-parabolico
}

Scena_Exercisi3::~Scena_Exercisi3() {
}

bool Scena_Exercisi3::Start() {
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
	_rectIdleCanon = { 48 * 4, 0, 48, 48 };

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
	_rectGround1 = { 0, 400, 1000, 70 };
	App->collisions->AddCollider(_rectGround1, Collider::Type::GROUND, this);

	return true;
}

Update_Status Scena_Exercisi3::Update() {

	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && !_start) {
		_graus += 0.5;
		_angle = _graus * M_PI / 180; // Angle en radians
		_temps = 0;

		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
		App->hud->PaintSentence("Graus: " + std::to_string(_graus) + " Velocitat inicial: " + std::to_string(_velocitatInicial), { 100,100 });

	}
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && !_start) {
		_graus -= 0.5;
		_angle = _graus * M_PI / 180; // Angle en radians
		_temps = 0;

		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
		App->hud->PaintSentence("Graus: " + std::to_string(_graus) + " Velocitat inicial: " + std::to_string(_velocitatInicial), { 100,100 });
	}
	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && !_start) {
		_velocitatInicial += 10;
		_angle = _graus * M_PI / 180; // Angle en radians

		// m/s
		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
		App->hud->PaintSentence("Graus: " + std::to_string(_graus) + " Velocitat inicial: " + std::to_string(_velocitatInicial), { 100,100 });
	}
	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && !_start) {
		_velocitatInicial -= 10;
		_angle = _graus * M_PI / 180; // Angle en radians

		// m/s
		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
		App->hud->PaintSentence("Graus: " + std::to_string(_graus) + " Velocitat inicial: " + std::to_string(_velocitatInicial), { 100,100 });
	}

	if (App->input->keys[SDL_SCANCODE_R] == Key_State::KEY_DOWN && !_start) {
		// TODO: RESET		
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN && !_start) {
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

	// Init/end shoot animation 
	if (_shooting) {
		_shootAnimation.Update();
		App->render->Blit(_textura_canon, _alturaInicialDeslpassamentX, (SCREEN_HEIGHT - _alturaInicial), &_shootAnimation.GetCurrentFrame());
	}
	else
		App->render->Blit(_textura_canon, _alturaInicialDeslpassamentX, (SCREEN_HEIGHT - _alturaInicial), &_rectIdleCanon);

	// Init/end ball moves
	if (_start)
		App->render->Blit(_textura_canon, _position_X + _alturaInicialDeslpassamentX, (SCREEN_HEIGHT - _position_Y), &_rectBall);

	// Init/end explode animation
	if (_boom) {
		_explodeAnimation.Update();
		App->render->Blit(_textura_boom, _rectAspid.x - 150, _rectAspid.y - 150, &_explodeAnimation.GetCurrentFrame());
	}
	else {
		_aspidAnimation.Update();
		App->render->Blit(_textura_aspid, _rectAspid.x, _rectAspid.y, &_aspidAnimation.GetCurrentFrame());
	}

	App->hud->PaintSentence("S-disparar", { 10, 0 });
	App->hud->PaintSentence("Fletxes-angles/potencia", { 10, 30 });
	App->hud->PaintSentence("Graus<" + std::to_string(_graus), { 10, 60 });
	App->hud->PaintSentence("V.I<" + std::to_string(_velocitatInicial), { 10, 90 });

	return Update_Status::UPDATE_CONTINUE;
}

bool Scena_Exercisi3::CleanUp() {
	App->player->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}

void Scena_Exercisi3::OnCollision(Collider* c1, Collider* c2) {

	if (c1->type == Collider::TR_OBJECTIVE_1 && c2->type == Collider::PLAYER && !_shooting) {
		LOG("OBJECTIU ABATUT!");
		_shooting = true;
	}
}