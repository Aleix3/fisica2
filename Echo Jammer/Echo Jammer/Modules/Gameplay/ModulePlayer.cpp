#include "ModulePlayer.h"

#include <stdio.h>
#include <SDL_timer.h>

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleInput.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleParticles.h"
#include "../Core/ModuleAudio.h"
#include "../Core/ModuleCollisions.h"
#include "../Foreground/ModuleFadeToBlack.h"
#include "../../Utils/DirectionHelper.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled) {


}

ModulePlayer::~ModulePlayer() {
}

bool ModulePlayer::Start()
{
	texturePlayer = App->textures->Load(FI_Player_car.c_str());
	collider = App->collisions->AddCollider({ position.x, position.y, 96, 64 }, Collider::Type::PLAYER, this);

	_currentAnimation = &_eastAnim;

	alive = true;
	position.x = 100;
	position.y = 400;

#pragma region MOVES

	// EAST
	for (int i = 0; i < _numFrames; i++)
		_eastAnim.PushBack({ 96 * i, 64 * 1, 96, 64 });
	_eastAnim.loop = true;
	_eastAnim.speed = 0.2f;


	// WEAST
	for (int i = 0; i < _numFrames; i++)
		_weastAnim.PushBack({ 96 * i, 64 * 3, 96, 64 });
	_weastAnim.loop = true;
	_weastAnim.speed = 0.2f;


#pragma endregion



	return true;
}

Update_Status ModulePlayer::Update() {
	App->player->positionAnterior = App->player->position;

	PlaceHolderMove();

	collider->SetPos(position.x, position.y);

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate() {
	_currentAnimation->Update();
	App->render->Blit(texturePlayer, position.x, position.y, &_currentAnimation->GetCurrentFrame());

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {

	if (c2->type == Collider::WALL) {
		if (c1->rect.x < c2->rect.x + c2->rect.w
			&& c1->rect.x + c1->rect.w > c2->rect.x
			&& c1->rect.y < c2->rect.y + c2->rect.h
			&& c1->rect.y + c1->rect.h > c2->rect.y) {

			position = positionAnterior;
			//LOG("Hay superposicion");
		}
	}

	//if (c2->type == Collider::TR_NIVELL_T1) {
	//	LOG("TRIGGER NIVELL TUTORIAL ACTIVAT!");	
	//	App->fade->FadeToBlack((Module*)App->scene_01_tutorial, (Module*)App->scena, 60);
	//}

	//if (c2->type == Collider::TR_NIVELL_12) {
	//	LOG("TRIGGER NIVELL 1 ACTIVAT!");
	//	//App->fade->FadeToBlack(this, (Module*)App->scene_03_nivel2, 60);
	//	App->fade->FadeToBlack((Module*)App->scena, (Module*)App->scene_03_nivel2, 60);
	//}
}

void ModulePlayer::PlaceHolderMove()
{
	const PlayerInput& controller = App->input->controlP1;


	if (controller.moveRight == Key_State::KEY_REPEAT) {
		// EAST
		_currentAnimation = &_eastAnim;
		position.x += speed;
		_actualDirection = Directions::EAST;
	}
	else if (controller.moveLeft == Key_State::KEY_REPEAT) {
		// WEAST
		_currentAnimation = &_weastAnim;
		position.x -= speed;
		_actualDirection = Directions::WEST;
	}
}

void ModulePlayer::GetInputDirection()
{
	const PlayerInput& p1 = App->input->controlP1;
	iPoint dirVect;

	dirVect.y += (int)(p1.moveUp == Key_State::KEY_REPEAT ? -1 : 0);
	dirVect.y += (int)(p1.moveDown == Key_State::KEY_REPEAT ? 1 : 0);
	dirVect.x += (int)(p1.moveLeft == Key_State::KEY_REPEAT ? -1 : 0);
	dirVect.x += (int)(p1.moveRight == Key_State::KEY_REPEAT ? 1 : 0);

	_actualDirection = DirectionHelper::GetDirection({ 0,0 }, dirVect);

}

void ModulePlayer::ApplyMovement()
{

	switch (_actualDirection)
	{
	case Directions::EAST: {
		_currentAnimation = &_eastAnim;
		position.x += speed;
		break;
	}
	case Directions::WEST: {
		_currentAnimation = &_weastAnim;
		position.x -= speed;
		break;
	}
	case Directions::NONE: {
		// Per defecte IDLE		
		if (_currentAnimation == &_eastAnim) _currentAnimation = &_eastAnim;
		else if (_currentAnimation == &_weastAnim) _currentAnimation = &_weastAnim;
	}
	default:
		break;
	}

}
