#include "Collider.h"

#include "App.h"
#include "Scene.h"
#include "Textures.h"
#include "Render.h"
#include "Input.h"
#include "Player.h"
#include "Log.h"
#include "Defs.h"

Collider::Collider() : Module() {

}

Collider::~Collider() {
	// Destructor
}

bool Collider::Start() {

	//textureFont = app->tex->Load("Assets/Textures/Font.png");
	bool ret = true;
	return ret;
}

bool Collider::Update()
{
	bool ret = true;
	return ret;
}

bool Collider::PostUpdate() {
	bool ret = true;
	return ret;
}

bool Collider::CleanUp()
{
	return true;
}