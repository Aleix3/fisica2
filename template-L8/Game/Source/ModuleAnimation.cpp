#include "ModuleAnimation.h"

#include "Scene.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Animation.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "Item.h"
#include "Physics.h"
#include "Defs.h"
#include "Log.h"
#include "Score.h"
#include "Hud.h"
#include "SDL_image/include/SDL_image.h"

ModuleAnimation::ModuleAnimation() : Module() {
	AnimLight1.PushBack({ 650, 241, 6,  6 });
	AnimLight1.PushBack({ 650, 241, 6,  6 });
	AnimLight1.PushBack({ 650, 241, 6,  6 });
	AnimLight1.PushBack({ 650, 241, 6,  6 });
	AnimLight1.PushBack({ 650, 241, 6,  6 });
	AnimLight1.PushBack({ 529, 196, 28,  28 });
	AnimLight1.loop = true;
	AnimLight1.speed = 0.1f;

	AnimLight2.PushBack({ 650, 241, 6,  6 });
	AnimLight2.PushBack({ 650, 241, 6,  6 });
	AnimLight2.PushBack({ 650, 241, 6,  6 });
	AnimLight2.PushBack({ 650, 241, 6,  6 });
	AnimLight2.PushBack({ 495, 194, 23,  30 });
	AnimLight2.PushBack({ 650, 241, 6,  6 });
	AnimLight2.loop = true;
	AnimLight2.speed = 0.1f;

	AnimLight3.PushBack({ 650, 241, 6,  6 });
	AnimLight3.PushBack({ 650, 241, 6,  6 });
	AnimLight3.PushBack({ 650, 241, 6,  6 });
	AnimLight3.PushBack({ 457, 196, 28,  28 });
	AnimLight3.PushBack({ 650, 241, 6,  6 });
	AnimLight3.PushBack({ 650, 241, 6,  6 });
	AnimLight3.loop = true;
	AnimLight3.speed = 0.1f;

	AnimLight4.PushBack({ 650, 241, 6,  6 });
	AnimLight4.PushBack({ 650, 241, 6,  6 });
	AnimLight4.PushBack({ 81, 197, 30,  18 });
	AnimLight4.PushBack({ 650, 241, 6,  6 });
	AnimLight4.PushBack({ 650, 241, 6,  6 });
	AnimLight4.PushBack({ 650, 241, 6,  6 });
	AnimLight4.loop = true;
	AnimLight4.speed = 0.1f;

	AnimLight5.PushBack({ 650, 241, 6,  6 });
	AnimLight5.PushBack({ 44, 193, 30,  21 });
	AnimLight5.PushBack({ 650, 241, 6,  6 });
	AnimLight5.PushBack({ 650, 241, 6,  6 });
	AnimLight5.PushBack({ 650, 241, 6,  6 });
	AnimLight5.PushBack({ 650, 241, 6,  6 });
	AnimLight5.loop = true;
	AnimLight5.speed = 0.1f;

	AnimLight6.PushBack({ 4, 190, 31,  24 });
	AnimLight6.PushBack({ 650, 241, 6,  6 });
	AnimLight6.PushBack({ 650, 241, 6,  6 });
	AnimLight6.PushBack({ 650, 241, 6,  6 });
	AnimLight6.PushBack({ 650, 241, 6,  6 });
	AnimLight6.PushBack({ 650, 241, 6,  6 });
	AnimLight6.loop = true;
	AnimLight6.speed = 0.1f;

	AnimArrow1.PushBack({ 426,164,15,17 });
	AnimArrow1.PushBack({ 650, 241, 6,  6 });
	AnimArrow1.loop = true;
	AnimArrow1.speed = 0.08f;

	AnimArrow2.PushBack({ 428,192,20,20 });
	AnimArrow2.PushBack({ 650, 241, 6,  6 });
	AnimArrow2.loop = true;
	AnimArrow2.speed = 0.08f;

}

ModuleAnimation::~ModuleAnimation() {
//destructor
}
bool ModuleAnimation::Awake(pugi::xml_node config)
{
	LOG("Loading ModuleAnimation");
	return true;
}
bool ModuleAnimation::Start() {
	currentAnimLight1 = &AnimLight1;
	currentAnimLight2 = &AnimLight2;
	currentAnimLight3 = &AnimLight3;
	currentAnimLight4 = &AnimLight4;
	currentAnimLight5 = &AnimLight5;
	currentAnimLight6 = &AnimLight6;

	currentAnimArrow1 = &AnimArrow1;
	currentAnimArrow2 = &AnimArrow2;
	_texturaSprite = app->tex->Load("Assets/Textures/SpaceSprites200.png");

	return true;
}

bool ModuleAnimation::Update()
{
	currentAnimLight1->Update();
	currentAnimLight2->Update();
	currentAnimLight3->Update();
	currentAnimLight4->Update();
	currentAnimLight5->Update();
	currentAnimLight6->Update();
	currentAnimArrow1->Update();
	currentAnimArrow2->Update();
	return true;
}

bool ModuleAnimation::PostUpdate() {
	_rectLight1 = currentAnimLight1->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 495, 85, &_rectLight1);
	_rectLight2 = currentAnimLight2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 548, 130, &_rectLight2);
	_rectLight3 = currentAnimLight3->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 573, 192, &_rectLight3);
	_rectLight4 = currentAnimLight4->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 584, 276, &_rectLight4);
	_rectLight5 = currentAnimLight5->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 598, 372, &_rectLight5);
	_rectLight6 = currentAnimLight6->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 613, 473, &_rectLight6);

	_rectArrow1 = currentAnimArrow1->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 290, 388, &_rectArrow1);
	_rectArrow2 = currentAnimArrow2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 477, 314, &_rectArrow2);
	return true;
}

bool ModuleAnimation::CleanUp()
{
	return true;
}