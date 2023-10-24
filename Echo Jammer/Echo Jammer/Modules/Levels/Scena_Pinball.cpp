#include "Scena_Pinball.h"

#include "../../Application/Application.h"

#include "../Core/Render/ModuleTextures.h"
#include "../Core/Render/ModuleRender.h"
#include "../Core/Collisions/ModuleCollisions.h"
#include "../Core/Audio/ModuleAudio.h"
#include "../Core/Inputs/ModuleInput.h"
#include "../Foreground/ModuleFadeToBlack.h"
#include "../Foreground/ModuleHUD.h"
#include "../Gameplay/ModulePlayer.h"

Scena_Pinball::Scena_Pinball(bool startEnabled)	: Module(startEnabled)
{
}

Scena_Pinball::~Scena_Pinball()
{
}

bool Scena_Pinball::Start()
{
	return false;
}

Update_Status Scena_Pinball::Update()
{
	return Update_Status();
}

Update_Status Scena_Pinball::PostUpdate()
{
	return Update_Status();
}

bool Scena_Pinball::CleanUp()
{
	return false;
}

void Scena_Pinball::OnCollision(Collider* c1, Collider* c2)
{
}
