#include "Scena.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleOscuridad.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"

Scena::Scena(bool startEnabled) : Module(startEnabled) {

}

Scena::~Scena() {
}

bool Scena::Start()
{

	textura_fondo2 = App->textures->Load(FI_Mapa_Level1.c_str());
	textura_oscuridad = App->textures->Load(FI_Mapa_Overlay.c_str());

	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	rectFondo.x = 0;
	rectFondo.y = 0;
	rectFondo.w = weigthNivell;
	rectFondo.h = heightNivell;

	//// POSITION INITIAL CAMERA
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->oscuridad->Enable();
	App->player->Enable();
	App->collisions->Enable();

	// TODO: Poner en la posicion inical / puerta del nivel
	App->player->position.x = 64;
	App->player->position.y = 64;
	App->player->collider->SetPos(400, 500);


	//App->collisions->AddCollider({ 0, 0, 1920, 192}, Collider::Type::WALL);
	App->collisions->AddCollider({ 128 , 1344, 128 , 256 }, Collider::Type::TR_NIVELL_12);

	return true;
}

Update_Status Scena::Update() {

	if (!App->player->alive) {
		App->fade->FadeToBlack((Module*)this, (Module*)App->scene_01_tutorial, 60);
	}

	if (App->player->position.x <= 10)
		App->player->position.x = 10;
	if (App->player->position.x >= weigthNivell - 10 - 128)
		App->player->position.x = weigthNivell - 10 - 128;

	if (App->player->position.y <= 10)
		App->player->position.y = 10;
	if (App->player->position.y >= heightNivell - 128 - 10)
		App->player->position.y = heightNivell - 128 - 10;


	if (App->player->position.x > 0 && App->player->position.x < weigthNivell - 1920) App->render->camera.x = App->player->position.x;
	if (App->player->position.y > 540 && App->player->position.y < heightNivell - 1080 + 540) App->render->camera.y = App->player->position.y - 540;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scena::PostUpdate() {
	App->render->Blit(textura_fondo2, 0, 0, &rectFondo);
	return Update_Status::UPDATE_CONTINUE;
}

bool Scena::CleanUp() {
	App->oscuridad->Disable();
	App->player->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}
