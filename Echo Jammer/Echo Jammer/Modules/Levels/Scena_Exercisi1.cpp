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
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		boxX -= 4; // Move left
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		boxX += 4; // Move right
	}



	//Get the size of the window
	uint windowW, windowH;
	app->win->GetWindowSize(windowW, windowH);



	//Get the size of the texture
	uint texW, texH;
	app->tex->GetSize(_caja, texW, texH);
	app->tex->GetSize(img2, texW, texH);




	if (boxX > (plX - 300) && boxX < plX + 120)
	{
		plY = 2000;
		plY2 = 550;


		if (direcction < boxX)
		{
			app->render->DrawTexture(_planta2, plX2, plY2, NULL, NULL, 60);
			app->render->DrawTexture(_caja, boxX, boxY);
		}

		else if (direcction > boxX)
		{
			app->render->DrawTexture(_planta2, plX2, plY2, NULL, NULL, -60);
			app->render->DrawTexture(_caja, boxX, boxY);
		}

		else if (direcction = boxX)
		{
			app->render->DrawTexture(_planta2, plX2, plY2);
			app->render->DrawTexture(_caja, boxX, boxY);
		}




	}
	else if (boxX > (plX + 100) || boxX < plX + 120)
	{
		plY = 2000;
		plY2 = 500;
		app->render->DrawTexture(_planta2, plX2, plY2);
		app->render->DrawTexture(_caja, boxX, boxY);
	}



	// Renders the image in the center of the screen
	/*app->render->DrawTexture(img, windowW /1 - texW / 1, windowH /1 - texH / 1);*/



		// Renders the image with scaled dimensions
	else
	{
		app->render->DrawTexture(_planta, plX, plY);

		app->render->DrawTexture(_caja, boxX, boxY);
	}




	direcction = boxX;

	app->render->DrawTexture(_suelo, 0, 620);



	
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