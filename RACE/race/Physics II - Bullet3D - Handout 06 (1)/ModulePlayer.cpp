#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
	turn = acceleration = friccion = 0.0f;

	isBoosting = false;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->collision_listeners.add(this); // Add this module as listener to callbacks from vehicle
	vehicle->SetPos(0, 12, 10);
	/*vehicle->GetPosition();*/

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	/*vec3 pos = GetPosition();*/
	vehicle->GetKmh();
	turn = acceleration = brake = deacceleration = 0.0f;
	turn = acceleration = friccion = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	vehicle->SetFriccionn(friccion);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		/*brake = BRAKE_POWER;*/
		deacceleration = MAX_DEACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT)
	{
		car.mass += 10;
	}
	if (vehicle->GetKmh() < 0)
	{
		friccion = FRICCION_COEFICIENT * car.mass;
	}
	if (vehicle->GetKmh() >= 0)
	{
		friccion = FRICCION_COEFICIENT * car.mass;
	}
	
	// Calcular la resistencia del aire (arrastre)
	//float speed = vehicle->GetKmh();
	//float dragForce = -FRICCION_COEFICIENT * speed * speed;
	//vehicle->ApplyEngineForce(dragForce);

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		ActivateBoost();
	}	

	if (isBoosting) {

		btTransform trans;
		vehicle->vehicle->getRigidBody()->getMotionState()->getWorldTransform(trans); // Obtener la matriz de transformación del vehículo

		btVector3 forwardVector = trans.getBasis().getColumn(2); // Obtener la dirección hacia adelante (asumiendo que es la tercera columna)
		btVector3 boostForce = forwardVector * 300000; // Calcular la fuerza de boost
		vehicle->vehicle->getRigidBody()->applyCentralForce(boostForce); // Aplicar la fuerza de boost
		isBoosting = false;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	
	if (vehicle->GetKmh() <= 0)
	{
		vehicle->ApplyEngineForce(deacceleration);
	}
	if (vehicle->GetKmh() >= 0)
	{
		vehicle->Brake(brake);
		vehicle->Brake(friccion);
	}
	

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	// Randomly teleport the sensor cube around 1st quadrant
	
	if (body2 == App->scene_intro->sensor_cube)	body2->SetPos(20 * rand() / RAND_MAX, 3, 20 * rand() / RAND_MAX);
	/*if (body2 == App->scene_intro.);*/
}

void ModulePlayer::ActivateBoost() {
	isBoosting = true;
}
