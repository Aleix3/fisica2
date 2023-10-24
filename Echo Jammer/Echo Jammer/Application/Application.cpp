#include "Application.h"
#include <iostream>
#include <SDL.h>

#include "../Modules/Module.h"

#include "../Modules/Core/Render/ModuleWindow.h"
#include "../Modules/Core/Render/ModuleTextures.h"
#include "../Modules/Core/Render/ModuleRender.h"
#include "../Modules/Core/Inputs/ModuleInput.h"
#include "../Modules/Core/Audio/ModuleAudio.h"
#include "../Modules/Core/Entities/ModuleParticles.h"
#include "../Modules/Core/Collisions/ModuleCollisions.h"
#include "../Modules/Core/Physics/ModulePhysics.h"

#include "../Modules/Foreground/ModuleFadeToBlack.h"
#include "../Modules/Foreground/ModuleHUD.h"

#include "../Modules/Gameplay/ModulePlayer.h"

#include "../Modules/Levels/Scena_Exercisi1.h"
#include "../Modules/Levels/Scena_Exercisi2.h"
#include "../Modules/Levels/Scena_Exercisi3.h"
#include "../Modules/Levels/Scena_Exercisi5.h"


Application::Application() {
	Timer timer = Timer();
	startupTime = Timer();
	frameTime = PerfTimer();
	lastSecFrameTime = PerfTimer();

	frames = 0;

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
	modules.push_back(collisions = new ModuleCollisions(false));
	modules.push_back(hud = new ModuleHUD(true));
	modules.push_back(render = new ModuleRender(true));

	sizeVector = modules.size();

	LOG("Timer App Constructor: %f", timer.ReadMSec());
}

Application::~Application() {
	for (int i = 0; i < sizeVector; ++i) {
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::LoadConfig()
{
	return false;
}

bool Application::Init() {
	Timer timer = Timer();

	//bool ret = LoadConfig();

	bool ret = true;

	title.Create("Fisica 2 ...");
	window->SetTitle(title.GetString());

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < sizeVector && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < sizeVector && ret; ++i)
		ret = modules[i]->startEnabled ? modules[i]->Enable() : true;

	LOG("Timer App Awake(): %f", timer.ReadMSec());

	return ret;
}

Update_Status Application::Update() {
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	frameTime.Start(); // PrepareUpdate

	for (int i = 0; i < sizeVector && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < sizeVector && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < sizeVector && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;



	double currentDt = frameTime.ReadMs();
	if (maxFrameDuration > 0 && currentDt < maxFrameDuration) {
		uint32 delay = (uint32)(maxFrameDuration - currentDt);

		PerfTimer delayTimer = PerfTimer();
		SDL_Delay(delay);
	}

	// Amount of frames since startup
	frameCount++;

	// Amount of time since game start (use a low resolution timer)
	secondsSinceStartup = startupTime.ReadSec();

	// Amount of ms took the last update (dt)
	dt = (float)frameTime.ReadMs();

	// Amount of frames during the last second
	lastSecFrameCount++;

	// Average FPS for the whole game life
	if (lastSecFrameTime.ReadMs() > 1000) {
		lastSecFrameTime.Start();
		averageFps = (averageFps + lastSecFrameCount) / 2;
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
	}

	// Shows the time measurements in the window title
	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last sec frames: %i Last dt: %.3f Time since startup: %I32u Frame Count: %I64u ",
		averageFps, framesPerSecond, dt, secondsSinceStartup, frameCount);

	window->SetTitle(title);

	return ret;
}


bool Application::CleanUp() {
	bool ret = true;

	for (int i = sizeVector - 1; i >= 0 && ret; --i)
		ret = modules[i]->Disable();

	return ret;
}