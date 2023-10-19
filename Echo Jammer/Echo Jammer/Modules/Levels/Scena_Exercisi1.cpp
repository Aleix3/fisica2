#include "Scena_Exercisi1.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/Render/ModuleTextures.h"
#include "../../Modules/Core/Render/ModuleRender.h"
#include "../../Modules/Core/Collisions/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/Audio/ModuleAudio.h"
#include "../../Modules/Core/Inputs/ModuleInput.h"

Scena_Exercisi1::Scena_Exercisi1(bool startEnabled) : Module(startEnabled) {

}

Scena_Exercisi1::~Scena_Exercisi1() {
}

bool Scena_Exercisi1::Start() {
	_caja = App->textures->Load(FI_Player_caja.c_str());
	_planta = App->textures->Load(FI_Player_planta.c_str());
	_planta2 = App->textures->Load(FI_Player_planta2.c_str());
	_suelo = App->textures->Load(FI_Player_planta2.c_str());

	return true;
}

Update_Status Scena_Exercisi1::Update() {
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		boxX -= 4; // Move left
	}
	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		boxX += 4; // Move right
	}


	//Get the size of the texture
	uint texW, texH;
	App->textures->GetTextureSize(_caja, texW, texH);
	App->textures->GetTextureSize(_planta, texW, texH);

	if (boxX > (plX - 300) && boxX < plX + 120) {
		plY = 2000;
		plY2 = 550;

		if (direcction < boxX) {
			App->render->Blit(_planta2, plX2, plY2, NULL, NULL, 60);
			App->render->Blit(_caja, boxX, boxY);
		}
		else if (direcction > boxX) {
			App->render->Blit(_planta2, plX2, plY2, NULL, NULL, -60);
			App->render->Blit(_caja, boxX, boxY);
		}
		else if (direcction = boxX) {
			App->render->Blit(_planta2, plX2, plY2);
			App->render->Blit(_caja, boxX, boxY);
		}
	}
	else if (boxX > (plX + 100) || boxX < plX + 120) {
		plY = 2000;
		plY2 = 500;
		App->render->Blit(_planta2, plX2, plY2);
		App->render->Blit(_caja, boxX, boxY);
	}



	// Renders the image in the center of the screen
	/*app->render->DrawTexture(img, windowW /1 - texW / 1, windowH /1 - texH / 1);*/



		// Renders the image with scaled dimensions
	else {
		App->render->Blit(_planta, plX, plY);
		App->render->Blit(_caja, boxX, boxY);
	}

	direcction = boxX;
	App->render->Blit(_suelo, 0, 620);

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