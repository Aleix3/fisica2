#include "Scena_Exercisi2.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"

Scena_Exercisi2::Scena_Exercisi2(bool startEnabled) : Module(startEnabled) {

}

Scena_Exercisi2::~Scena_Exercisi2() {
}

bool Scena_Exercisi2::Start()
{

	textura_fondo = App->textures->Load(FI_Mapa_Scena.c_str());
	textura_plataform = App->textures->Load(FI_Plataform.c_str());
	textura_link = App->textures->Load(FI_Player_linkJump.c_str());

	for (int i = 0; i < 9; i++)
		_jumpAnimation.PushBack({ 32 * i, 0, 32, 32 });
	_jumpAnimation.loop = true;
	_jumpAnimation.speed = 0.2f;

	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	rectFondo.x = 0;
	rectFondo.y = 0;
	rectFondo.w = weigthNivell;
	rectFondo.h = heightNivell;

	// POSITION INITIAL CAMERA
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->collisions->Enable();

	App->player->position.x = 100;
	App->player->position.y = 300;

	App->collisions->AddCollider({ 600 , 200, 20 , 220 }, Collider::Type::TR_T1_SALT_LINK, this);
	App->collisions->AddCollider({ 0 , 355, 1000 , 100 }, Collider::Type::TR_T1_FLOOR, this);
	App->collisions->AddCollider({ 150 , 225, 240 , 50 }, Collider::Type::TR_T1_PLATAFORM, this);
	
	return true;
}

Update_Status Scena_Exercisi2::Update() {

	/*if (App->player->position.x <= 10)
		App->player->position.x = 10;
	if (App->player->position.x >= weigthNivell - 10 - 128)
		App->player->position.x = weigthNivell - 10 - 128;*/

	/*if (App->player->position.y <= 10)
		App->player->position.y = 10;
	if (App->player->position.y >= heightNivell - 128 - 10)
		App->player->position.y = heightNivell - 128 - 10;*/


	/*if (App->player->position.x > 0 && App->player->position.x < weigthNivell - 1920) 
		App->render->camera.x = App->player->position.x;
	if (App->player->position.y > 540 && App->player->position.y < heightNivell - 1080 + 540) 
		App->render->camera.y = App->player->position.y - 540;*/

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scena_Exercisi2::PostUpdate() {
	App->render->Blit(textura_fondo, 0, 0, &rectFondo);
	App->render->Blit(textura_plataform, 150, 220);
	App->render->Blit(textura_plataform, 550, 220);
	
	if (saltActivat)
	{
		_jumpAnimation.Update();
		App->render->Blit(textura_link, 600, 200, &_jumpAnimation.GetCurrentFrame());
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

bool Scena_Exercisi2::CleanUp() {
	App->player->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}

void Scena_Exercisi2::OnCollision(Collider* c1, Collider* c2) {
	
	if (c1->type == Collider::TR_T1_SALT_LINK && c2->type == Collider::PLAYER && !saltActivat)
	{
		shouldResetPlayerPosition = true;
		LOG("TRIGGER ACTIVAT");
		saltActivat = true;
	}

	if (c1->type == Collider::TR_T1_SALT_LINK && c2->type == Collider::PLAYER )
	{
		shouldResetPlayerPosition = true;
		LOG("TRIGGER ACTIVAT");
		saltActivat = true;
	}
	if (shouldResetPlayerPosition == true)
	{
		// Reset the player's position
		App->player->position.x = 100;
		App->player->position.y = 300;

		// Reset the flag to prevent continuous resetting
		shouldResetPlayerPosition = true;
	}


}
