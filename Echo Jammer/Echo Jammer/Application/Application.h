#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include <vector>
#include "../Utils/SString.h"
#include "../Utils/List.h"
#include "../Modules/Core/Timers/PerfTimer.h"
#include "../Modules/Core/Timers/Timer.h"

//#include "EntityManager.h"
//#include "PugiXml/src/pugixml.hpp"

class Module;

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class ModulePhysics;
class ModuleHUD;

class Scena_Exercisi1;
class Scena_Exercisi2;
class Scena_Exercisi3;
class Scena_Exercisi5;
class Scena_Pinball;

class Application {

public:

	Application();
	~Application();

	// Load config file
	bool LoadConfig();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();


public:
	std::vector<Module*> modules;

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;
	ModulePlayer* player = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;
	ModulePhysics* physics = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;
	ModuleRender* render = nullptr;
	ModuleHUD* hud = nullptr;

	Scena_Exercisi1* scena_Exercisi1 = nullptr;
	Scena_Exercisi2* scena_Exercisi2 = nullptr;
	Scena_Exercisi3* scena_Exercisi3 = nullptr;
	Scena_Exercisi5* scena_Exercisi5 = nullptr;
	Scena_Pinball* scena_Pinball = nullptr;

private:
	int sizeVector = 0;

	int argc;
	char** args;
	SString title;
	SString organization;

//	List<Module*> modules;

	uint frames;
	float dt;

	Timer startupTime;
	PerfTimer frameTime;
	PerfTimer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;
	uint32 secondsSinceStartup = 0;
	uint32 maxFrameDuration = 16;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__