#include "Scena_Pinball.h"

Scena_Pinball::Scena_Pinball(bool startEnabled)
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
