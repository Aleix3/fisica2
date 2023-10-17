#include "Application.h"
#include <iostream>
#include <SDL.h>

#include "../Modules/Module.h"
#include "../Modules/Core/ModuleWindow.h"
#include "../Modules/Core/ModuleInput.h"
#include "../Modules/Core/ModuleTextures.h"
#include "../Modules/Core/ModuleAudio.h"
#include "../Modules/Core/ModuleParticles.h"
#include "../Modules/Core/ModuleCollisions.h"
#include "../Modules/Core/ModuleFadeToBlack.h"
#include "../Modules/Core/ModuleFonts.h"
#include "../Modules/Core/ModulePhysics.h"
#include "../Modules/Core/ModuleRender.h"
#include "../Modules/Core/ModuleHUD.h"
#include "../Modules/Gameplay/ModulePlayer.h"

#include "../Modules/Levels/Scena_Exercisi1.h"
#include "../Modules/Levels/Scena_Exercisi2.h"
#include "../Modules/Levels/Scena_Exercisi3.h"
#include "../Modules/Levels/Scena_Exercisi5.h"

int _start_time = SDL_GetTicks();
int last_frame_time = _start_time;
int frame_counter = 0;
int elapsed_time = 0;
int fps = 0;

Application::Application() {
	modules.push_back(window = new ModuleWindow(true));
	modules.push_back(input = new ModuleInput(true));
	modules.push_back(textures = new ModuleTextures(true));
	modules.push_back(audio = new ModuleAudio(true));

	modules.push_back(scena_Exercisi1 = new Scena_Exercisi1(false));
	modules.push_back(scena_Exercisi2 = new Scena_Exercisi2(true));
	modules.push_back(scena_Exercisi3 = new Scena_Exercisi3(false));
	modules.push_back(scena_Exercisi5 = new Scena_Exercisi5(false));

	modules.push_back(player = new ModulePlayer(false));
	modules.push_back(particles = new ModuleParticles(true));
	modules.push_back(fade = new ModuleFadeToBlack(true));
	modules.push_back(fonts = new ModuleFonts(true));
	modules.push_back(collisions = new ModuleCollisions(false));
	modules.push_back(hud = new ModuleHUD(true));
	modules.push_back(render = new ModuleRender(true));

	sizeVector = modules.size();
}

Application::~Application() {
	for (int i = 0; i < sizeVector; ++i) {
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init() {
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < sizeVector && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < sizeVector && ret; ++i)
		ret = modules[i]->startEnabled ? modules[i]->Enable() : true;

	return ret;
}

Update_Status Application::Update() {
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < sizeVector && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < sizeVector && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < sizeVector && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;



	// Control the FPS
	elapsed_time = SDL_GetTicks() - last_frame_time;
	if (elapsed_time < 1000 / 60) {
		SDL_Delay(1000 / 60 - elapsed_time);
	}

	frame_counter++;
	if (SDL_GetTicks() - _start_time > 1000) {
		fps = frame_counter * 1000 / (SDL_GetTicks() - _start_time);
		std::cout << "FPS: " << fps << std::endl;
		_start_time = SDL_GetTicks();
		frame_counter = 0;
	}

	last_frame_time = SDL_GetTicks();

	return ret;
}

bool Application::CleanUp() {
	bool ret = true;

	for (int i = sizeVector - 1; i >= 0 && ret; --i)
		ret = modules[i]->Disable();

	return ret;
}