#include "Scena_Exercisi5.h"

#include "../../Application/Application.h"

#include "../Core/ModuleTextures.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleCollisions.h"
#include "../Core/ModuleAudio.h"
#include "../Core/ModuleInput.h"
#include "../Foreground/ModuleFadeToBlack.h"
#include "../Foreground/ModuleHUD.h"
#include "../Gameplay/ModulePlayer.h"

#include <SDL_timer.h>
#include <ctime>

Scena_Exercisi5::Scena_Exercisi5(bool startEnabled) : Module(startEnabled) {
	// https://www.fisicalab.com/apartado/movimiento-parabolico
}

Scena_Exercisi5::~Scena_Exercisi5() {
}

bool Scena_Exercisi5::Start()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	_posicioAspidAleatoriX = std::rand() % 601 + 300;

	// Load textures
	_textura_fondo = App->textures->Load(FI_Background.c_str());
	_textura_canon = App->textures->Load(FI_canon.c_str());
	_textura_boom = App->textures->Load(FI_boom.c_str());

	// Load animations
	for (int i = 0; i < 6; i++)
		_shootAnimation.PushBack({ 48 * i, 0, 48, 48 });
	_shootAnimation.loop = false;
	_shootAnimation.speed = 0.2f;

	// Load aduio
	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	// Set position / sizes
	_rectFondo = { 0, 0, _weigthNivell, _heightNivell };
	_rectCanon = { 220, 210, 48, 48 };
	_rectBallSprite = { 288, 0, 48, 48 };
	_rectBall = { 220, 210, 48, 48 };
	_rectRectangle_1 = { _posicioAspidAleatoriX, 350, 2, 57 };
	_rectRectangle_2 = { _posicioAspidAleatoriX, 350, 58, 2 };
	_rectRectangle_3 = { _posicioAspidAleatoriX + 57, 350 , 2, 57 };
	_rectRectangle_4 = { _posicioAspidAleatoriX, 350 + 57, 58, 2 };
	_rectIdleCanon = { 48 * 4, 0, 48, 48 };
	_rectGround1 = { 0, 400, 1000, 70 };

	// Initial position camera
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// Enable modules	
	App->collisions->Enable();

	// Initial position player
	App->player->position.x = 100;
	App->player->position.y = 300;

	// Load coliders
	App->collisions->AddCollider(_rectGround1, Collider::Type::GROUND, this);
	_colliderAspid = App->collisions->AddCollider(_rectAspid, Collider::Type::TR_OBJECTIVE_1, this);
	_colliderBall = App->collisions->AddCollider(_rectBall, Collider::Type::BALL, this);
	_colliderRectangle_1 = App->collisions->AddCollider(_rectRectangle_1, Collider::Type::RECTANGLE_1, this);
	_colliderRectangle_2 = App->collisions->AddCollider(_rectRectangle_2, Collider::Type::RECTANGLE_2, this);
	_colliderRectangle_3 = App->collisions->AddCollider(_rectRectangle_3, Collider::Type::RECTANGLE_3, this);
	_colliderRectangle_4 = App->collisions->AddCollider(_rectRectangle_4, Collider::Type::RECTANGLE_4, this);
	

	return true;
}

Update_Status Scena_Exercisi5::Update() {

#pragma region Angles / potencia

	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && !_start) {
		_graus += 1;
		_angle = _graus * M_PI / 180; // Angle en radians
		_temps = 0;

		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && !_start) {
		_graus -= 1;
		_angle = _graus * M_PI / 180; // Angle en radians
		_temps = 0;

		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && !_start) {
		_velocitatInicial += 10;
		_angle = _graus * M_PI / 180; // Angle en radians

		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
	}

	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && !_start) {
		_velocitatInicial -= 10;
		_angle = _graus * M_PI / 180; // Angle en radians

		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
	}

#pragma endregion

#pragma region Gravetat

	if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_REPEAT && !_start) {
		_gravetat += 10;
		_angle = _graus * M_PI / 180; // Angle en radians

		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
	}

	if (App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_REPEAT && !_start) {
		_gravetat -= 10;
		_angle = _graus * M_PI / 180; // Angle en radians

		_velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
		_velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

		_velocitat_X = _velocitatInicial_X;
		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));
	}

#pragma endregion

#pragma region Reset / Disparo

	if (App->input->keys[SDL_SCANCODE_R] == Key_State::KEY_DOWN) {
		_start = false;
		_shooting = false;

		_temps = 0;

		_colliderBall->rect.x = _rectBall.x;
		_colliderBall->rect.y = _rectBall.y;

		_posicioAspidAleatoriX = std::rand() % 601 + 300;
		_rectAspid.x = _posicioAspidAleatoriX;
		_colliderAspid->rect.x = _posicioAspidAleatoriX;
		LOG("Nova posicio Aspid: %d", _posicioAspidAleatoriX);
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN && !_start) {
		_start = true;
		_shooting = true;
		_shootAnimation.Reset();
		_start_time = SDL_GetTicks();
		LOG("SHOOT!");
	}

#pragma endregion


	if (_start) {
		_temps = ((float)SDL_GetTicks() - (float)_start_time) / 1000;

		_position_X = _velocitat_X * _temps;
		_position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));

		_colliderBall->rect.x = _position_X + _alturaInicialDeslpassamentX;
		_colliderBall->rect.y = SCREEN_HEIGHT - _position_Y;

		LOG("TEMPS: %f, X:%f, Y:%f, Yscreen: %f", _temps, _position_X, _position_Y, (SCREEN_HEIGHT - _position_Y));
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scena_Exercisi5::PostUpdate() {
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
		App->render->Blit(_textura_canon, _position_X + _alturaInicialDeslpassamentX, (SCREEN_HEIGHT - _position_Y), &_rectBallSprite);

	// Init/end explode animation

	App->hud->PaintSentence("S-disparar", { 10, 0 });
	App->hud->PaintSentence("R-reset", { 10, 30 });
	App->hud->PaintSentence("UpDown-Graus<" + std::to_string(_graus), { 10, 60 });
	App->hud->PaintSentence("LeftRight-V.I<" + std::to_string(_velocitatInicial), { 10, 90 });
	App->hud->PaintSentence("M/L-Gravetat<" + std::to_string(_gravetat), { 10, 120 });

	return Update_Status::UPDATE_CONTINUE;
}

bool Scena_Exercisi5::CleanUp() {
	App->player->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}

void Scena_Exercisi5::OnCollision(Collider* c1, Collider* c2) {

	if (c1->type == Collider::BALL && c2->type == Collider::TR_OBJECTIVE_1) {
		LOG("OBJECTIU ABATUT!");
		_shooting = false;
		_start = false;
		_colliderBall->rect = _rectBall;
	}
	if (c1->type == Collider::BALL && c2->type == Collider::GROUND) {
		LOG("TERRA!");
		_shooting = false;
		_start = false;
		_colliderBall->rect = _rectBall;
	}
	if (c1->type == Collider::BALL && c2->type == Collider::RECTANGLE_1) { // Esquerra
		LOG("Esquerra!");
		_shooting = false;
		_start = false;
		_colliderBall->rect = _rectBall;
	}
	if (c1->type == Collider::BALL && c2->type == Collider::RECTANGLE_2) { // Arriba
		LOG("Arriba!");
		_shooting = false;
		_start = false;
		_colliderBall->rect = _rectBall;
	}
	if (c1->type == Collider::BALL && c2->type == Collider::RECTANGLE_3) { // Dreta
		LOG("Dreta!");
		_shooting = false;
		_start = false;
		_colliderBall->rect = _rectBall;
	}
	if (c1->type == Collider::BALL && c2->type == Collider::RECTANGLE_4) { // Abajo
		LOG("Abajo!");
		_shooting = false;
		_start = false;
		_colliderBall->rect = _rectBall;
	}
}