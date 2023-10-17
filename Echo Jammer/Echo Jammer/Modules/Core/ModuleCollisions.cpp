#include "ModuleCollisions.h"

#include "../../Application/Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include <SDL_scancode.h>

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled) {

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;
	
	// EXERCISI 2
	matrix[Collider::Type::TR_T1_SALT_LINK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::PLATAFORM][Collider::Type::PLAYER] = true;
	
	// EXERCISI 3
	matrix[Collider::Type::TR_OBJECTIVE_1][Collider::Type::BALL] = true;

	// EXERCISI 5
	//matrix[Collider::Type::RECTANGLE_1][Collider::Type::BALL] = true;
	//matrix[Collider::Type::RECTANGLE_2][Collider::Type::BALL] = true;
	//matrix[Collider::Type::RECTANGLE_3][Collider::Type::BALL] = true;
	//matrix[Collider::Type::RECTANGLE_4][Collider::Type::BALL] = true;

}


// Destructor
ModuleCollisions::~ModuleCollisions() {
}

Update_Status ModuleCollisions::PreUpdate() {
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k) {
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect)) {
				// Check Module* listeners first
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr)
						c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr)
						c2->listeners[i]->OnCollision(c2, c1);

				// Check function callbacks
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listenerFunctions[i] != nullptr)
						(*c1->listenerFunctions[i])(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listenerFunctions[i] != nullptr)
						(*c2->listenerFunctions[i])(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update() {
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN || pad.r1 == true)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate() {
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw() {
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type) {
		case Collider::Type::NONE: App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha); break;// white

		case Collider::Type::WALL: App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha); break;// blue
		case Collider::Type::GROUND: App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha); break;// blue
		case Collider::Type::FLOOR: App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha); break; // bluex

		case Collider::Type::PLAYER: App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha); break;// green
		case Collider::Type::BALL: App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha); break;// red
		
		case Collider::Type::TR_T1_SALT_LINK: App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha); break; // yellow
		case Collider::Type::PLATAFORM: App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha); break; // yellow
		case Collider::Type::TR_OBJECTIVE_1: App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha); break; // yellow

		case Collider::Type::RECTANGLE_1: App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha); break;
		case Collider::Type::RECTANGLE_2: App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha); break;
		case Collider::Type::RECTANGLE_3: App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha); break;
		case Collider::Type::RECTANGLE_4: App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha); break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp() {
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener) {
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr) {
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, std::function<void(Collider*, Collider*)>* listener) {
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr) {
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider) {
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == collider) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}