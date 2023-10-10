#include "Scena_Exercisi1.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/ModuleAudio.h"

Scena_Exercisi1::Scena_Exercisi1(bool startEnabled) : Module(startEnabled) {

}

Scena_Exercisi1::~Scena_Exercisi1() {
}

bool Scena_Exercisi1::Start(){
	_caja = App->textures->Load(FI_Player_caja.c_str());
	_planta = App->textures->Load(FI_Player_planta.c_str());
	_planta2 = App->textures->Load(FI_Player_planta2.c_str());
	_suelo = App->textures->Load(FI_Player_planta2.c_str());

	return true;
}

Update_Status Scena_Exercisi1::Update() {

	
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scena_Exercisi1::PostUpdate() {
	
	return Update_Status::UPDATE_CONTINUE;
}

bool Scena_Exercisi1::CleanUp() {
	App->player->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}