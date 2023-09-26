#include "ModuleOscuridad.h"

#include <SDL_timer.h>
#include <SDL_image.h>

#include "../../Application/FileNames.h"
#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Gameplay/ModulePlayer.h"

ModuleOscuridad::ModuleOscuridad(bool startEnabled) : Module(startEnabled) {
}

ModuleOscuridad::~ModuleOscuridad() {
}

bool ModuleOscuridad::Start() {
	textura_oscuridad = App->textures->Load(FI_Mapa_Overlay.c_str());

	return true;
}

Update_Status ModuleOscuridad::Update() {


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleOscuridad::PostUpdate() {
		
	App->render->Blit(textura_oscuridad, App->player->position.x -1856, App->player->position.y-1856);
	
	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleOscuridad::CleanUp() {
	return true;
}