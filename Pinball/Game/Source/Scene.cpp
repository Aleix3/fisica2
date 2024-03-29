#include "Scene.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
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

#pragma region colliders escneari

int escenariGeneral[128] = {
	455, 91,
	488, 103,
	512, 127,
	537, 155,
	556, 186,
	560, 241,
	517, 352,
	523, 415,
	562, 437,
	593, 435,
	598, 498,
	608, 577,
	614, 618,
	625, 691,
	631, 768,
	606, 770,
	577, 749,
	525, 800,
	519, 846,
	214, 847,
	215, 796,
	103, 707,
	96, 758,
	83, 770,
	53, 765,
	85, 553,
	115, 520,
	81, 490,
	103, 307,
	133, 273,
	132, 197,
	177, 112,
	155, 90,
	159, 59,
	182, 39,
	219, 33,
	249, 41,
	265, 54,
	312, 46,
	368, 39,
	422, 44,
	467, 55,
	511, 77,
	567, 126,
	601, 192,
	617, 274,
	631, 378,
	645, 474,
	662, 573,
	678, 679,
	686, 724,
	692, 767,
	691, 824,
	650, 825,
	645, 768,
	635, 685,
	625, 603,
	610, 488,
	596, 389,
	579, 288,
	569, 198,
	545, 143,
	509, 109,
	450, 77
};
int sizeEscenariGeneral = sizeof(escenariGeneral) / sizeof(escenariGeneral[0]);

int outLaneRight[10] = {
	119, 564,
	111, 638,
	264, 757,
	108, 639,
	118, 564
};
int sizeOutLaneRight = sizeof(outLaneRight) / sizeof(outLaneRight[0]);

int outLaneLeft[12] = {
	576, 573,
	586, 671,
	477, 754,
	478, 753,
	585, 671,
	575, 573
};
int sizeOutLaneLeft = sizeof(outLaneLeft) / sizeof(outLaneLeft[0]);

int obstacleSuperiorDelTunel[62] = {
	321, 367,
	311, 348,
	300, 332,
	283, 314,
	273, 301,
	272, 288,
	266, 275,
	253, 270,
	236, 264,
	214, 258,
	196, 250,
	186, 237,
	180, 221,
	179, 205,
	179, 189,
	180, 180,
	172, 180,
	167, 191,
	165, 204,
	165, 218,
	167, 236,
	171, 252,
	172, 259,
	196, 261,
	204, 262,
	215, 265,
	230, 267,
	242, 272,
	252, 277,
	259, 281,
	264, 290
};
int sizeObstacleSuperiorDelTunel = sizeof(obstacleSuperiorDelTunel) / sizeof(obstacleSuperiorDelTunel[0]);

int tunnelFoc[48] = {
	451, 152,
	470, 140,
	492, 155,
	502, 169,
	507, 185,
	513, 205,
	513, 225,
	510, 237,
	506, 248,
	500, 260,
	488, 273,
	477, 286,
	465, 279,
	473, 271,
	480, 262,
	484, 253,
	489, 242,
	496, 224,
	496, 213,
	491, 200,
	485, 186,
	476, 172,
	471, 162,
	462, 154
};
int sizeTunnelFoc = sizeof(tunnelFoc) / sizeof(tunnelFoc[0]);

int tunnelLeftRight[52] = {
	158, 315,
	152, 327,
	150, 333,
	160, 348,
	171, 351,
	181, 358,
	192, 366,
	198, 378,
	192, 497,
	178, 519,
	162, 540,
	163, 567,
	161, 623,
	164, 626,
	168, 629,
	169, 575,
	165, 572,
	163, 555,
	167, 537,
	177, 525,
	187, 509,
	194, 490,
	199, 393,
	197, 371,
	187, 357,
	169, 342
};
int sizetunnelLeftRight = sizeof(tunnelLeftRight) / sizeof(tunnelLeftRight[0]);

int upperLeftObstacle[20] = {
	297, 84,
	320, 106,
	319, 124,
	266, 149,
	260, 146,
	259, 105,
	267, 100,
	274, 96,
	282, 91,
	291, 86
};
int sizeupperLeftObstacle = sizeof(upperLeftObstacle) / sizeof(upperLeftObstacle[0]);

int middleObstacle[16] = {
	327, 255,
	326, 264,
	388, 283,
	396, 278,
	393, 258,
	384, 264,
	347, 256,
	344, 247
};
int sizemiddleObstacle = sizeof(middleObstacle) / sizeof(middleObstacle[0]);

int middleDRObstacle[10] = {
	524, 569,
	482, 687,
	490, 696,
	540, 660,
	532, 569
};
int sizemiddleDRObstacle = sizeof(middleDRObstacle) / sizeof(middleDRObstacle[0]);

int middleLRObstacle[10] = {
	218, 571,
	257, 688,
	249, 694,
	201, 662,
	207, 571
};
int sizemiddleLRObstacle = sizeof(middleLRObstacle) / sizeof(middleLRObstacle[0]);

int tunnelEnd[8] = {
	423, 105,
420, 130,
427, 137,
445, 120
};
int sizetunnelEnd = sizeof(tunnelEnd) / sizeof(tunnelEnd[0]);

int tunnelELeft[24] = {
	188, 297,
203, 327,
219, 338,
232, 331,
253, 365,
258, 384,
258, 391,
264, 387,
250, 349,
233, 324,
216, 308,
201, 301
};
int sizetunnelELeft = sizeof(tunnelELeft) / sizeof(tunnelELeft[0]);

int triangle1[6] = {
191, 418,
178, 429,
191, 440
};
int sizetriangle1 = sizeof(triangle1) / sizeof(triangle1[0]);

int triangle2[6] = {
93, 405,
	107, 420,
	92, 425
};
int sizetriangle2 = sizeof(triangle2) / sizeof(triangle2[0]);
#pragma endregion


Scene::Scene() : Module()
{
	name.Create("scene");

#pragma region 
	//Animaciones
	AnimBump1.PushBack({ 404, 537, 44,  44 });
	AnimBump1.PushBack({ 451, 537, 44,  44 });
	AnimBump1.PushBack({ 404, 537, 44,  44 });
	AnimBump1.loop = true;
	AnimBump1.speed = 0.1f;
	AnimBump2.PushBack({ 421, 482, 44,  47 });
	AnimBump2.PushBack({ 471, 482, 44,  47 });
	AnimBump2.PushBack({ 421, 482, 44,  47 });
	AnimBump2.loop = true;
	AnimBump2.speed = 0.1f;
	AnimBump3.PushBack({ 3, 480, 45,  37 });
	AnimBump3.PushBack({ 55, 480, 45,  37 });
	AnimBump3.PushBack({ 3, 480, 45,  37 });
	AnimBump3.loop = true;
	AnimBump3.speed = 0.1f;
	AnimBump4.PushBack({ 3, 535, 44,  45 });
	AnimBump4.PushBack({ 53, 535, 44,  45 });
	AnimBump4.PushBack({ 3, 535, 44,  45 });
	AnimBump4.loop = true;
	AnimBump4.speed = 0.1f;
	AnimBump5.PushBack({ 2, 588, 37,  37 });
	AnimBump5.PushBack({ 44, 588, 37,  37 });
	AnimBump5.PushBack({ 2, 588, 37,  37 });
	AnimBump5.loop = true;
	AnimBump5.speed = 0.1f;
	AnimBump6.PushBack({ 341, 586, 38,  38 });
	AnimBump6.PushBack({ 384, 586, 38,  38 });
	AnimBump6.PushBack({ 341, 586, 38,  38 });
	AnimBump6.loop = true;
	AnimBump6.speed = 0.1f;
	AnimBump7.PushBack({ 685, 586, 38,  38 });
	AnimBump7.PushBack({ 730, 586, 38,  38 });
	AnimBump7.PushBack({ 685, 586, 38,  38 });
	AnimBump7.loop = true;
	AnimBump7.speed = 0.1f;

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

	AnimArrow1.PushBack({ 650, 241, 6,  6 });
	AnimArrow1.PushBack({ 650, 241, 6,  6 });
	AnimArrow1.PushBack({ 426,164,15,17 });
	AnimArrow1.PushBack({ 650, 241, 6,  6 });
	AnimArrow1.loop = true;
	AnimArrow1.speed = 0.12f;
	AnimArrow1W.PushBack({ 650, 241, 6,  6 });
	AnimArrow1W.PushBack({ 426,164,15,17 });
	AnimArrow1W.PushBack({ 650, 241, 6,  6 });
	AnimArrow1W.PushBack({ 650, 241, 6,  6 });
	AnimArrow1W.loop = true;
	AnimArrow1W.speed = 0.12f;
	AnimArrow1Q.PushBack({ 426,164,15,17 });
	AnimArrow1Q.PushBack({ 650, 241, 6,  6 });
	AnimArrow1Q.PushBack({ 650, 241, 6,  6 });
	AnimArrow1Q.PushBack({ 650, 241, 6,  6 });
	AnimArrow1Q.loop = true;
	AnimArrow1Q.speed = 0.12f;

	AnimArrow2.PushBack({ 650, 241, 6,  6 });
	AnimArrow2.PushBack({ 650, 241, 6,  6 });
	AnimArrow2.PushBack({ 428,192,20,20 });
	AnimArrow2.PushBack({ 650, 241, 6,  6 });
	AnimArrow2.loop = true;
	AnimArrow2.speed = 0.12f;
	AnimArrow2W.PushBack({ 650, 241, 6,  6 });
	AnimArrow2W.PushBack({ 428,192,20,20 });
	AnimArrow2W.PushBack({ 650, 241, 6,  6 });
	AnimArrow2W.PushBack({ 650, 241, 6,  6 });
	AnimArrow2W.loop = true;
	AnimArrow2W.speed = 0.12f;
	AnimArrow2Q.PushBack({ 428,192,20,20 });
	AnimArrow2Q.PushBack({ 650, 241, 6,  6 });
	AnimArrow2Q.PushBack({ 650, 241, 6,  6 });
	AnimArrow2Q.PushBack({ 650, 241, 6,  6 });
	AnimArrow2Q.loop = true;
	AnimArrow2Q.speed = 0.12f;

	AnimArrow1D.PushBack({ 50,156,22,27 });
	AnimArrow1D.PushBack({ 650, 241, 6,  6 });
	AnimArrow1D.loop = true;
	AnimArrow1D.speed = 0.05f;
	AnimArrow2D.PushBack({ 78,156,22,27 });
	AnimArrow2D.PushBack({ 650, 241, 6,  6 });
	AnimArrow2D.loop = true;
	AnimArrow2D.speed = 0.05f;
#pragma endregion
}

// Destructor
Scene::~Scene() {}

// Called before render is available
bool Scene::Awake(pugi::xml_node config)
{
	LOG("Loading Scene");
	bool ret = true;
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);

	player->config = config.child("player");

	score = new Score();

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	_texturaGeneral = app->tex->Load("Assets/Textures/SpaceCadet3DPinball2.png");
	_texball = app->tex->Load("Assets/Textures/ball.png");
	//_rectEscenari = { 0, 0, 1040, 855 };

	_rectPelota = { 0,0,15,15 };
	

	currentAnimBump1 = &AnimBump1;
	currentAnimBump2 = &AnimBump2;
	currentAnimBump3 = &AnimBump3;
	currentAnimBump4 = &AnimBump4;
	currentAnimBump5 = &AnimBump5;
	currentAnimBump6 = &AnimBump6;
	currentAnimBump7 = &AnimBump7;

	currentAnimLight1 = &AnimLight1;
	currentAnimLight2 = &AnimLight2;
	currentAnimLight3 = &AnimLight3;
	currentAnimLight4 = &AnimLight4;
	currentAnimLight5 = &AnimLight5;
	currentAnimLight6 = &AnimLight6;

	currentAnimArrow1 = &AnimArrow1;
	currentAnimArrow1W = &AnimArrow1W;
	currentAnimArrow1Q = &AnimArrow1Q;
	currentAnimArrow2 = &AnimArrow2;
	currentAnimArrow2W = &AnimArrow2W;
	currentAnimArrow2Q = &AnimArrow2Q;
	currentAnimArrow1D = &AnimArrow1D;
	currentAnimArrow2D = &AnimArrow2D;
	currentAnimSpring = &AnimSpring;

	sfx_Spring = app->audio->LoadFx("Assets/Audio/sfx/Spring.wav");
	sfx_Start = app->audio->LoadFx("Assets/Audio/sfx/Start.wav");
	sfx_Pala = app->audio->LoadFx("Assets/Audio/sfx/Pala.wav");
	sfx_Over = app->audio->LoadFx("Assets/Audio/sfx/Game_over.wav");

	app->audio->PlayFx(sfx_Start);

	_texturaSprite = app->tex->Load("Assets/Textures/SpaceSprites200.png");
	_pala1 = app->tex->Load("Assets/Textures/Pala1.png");
	_pala2 = app->tex->Load("Assets/Textures/Pala2.png");
	_rectPala1 = { 0,0,90,20 };
	_rectPala2 = { 0,0,90,20 };

	app->audio->PlayMusic("Assets/Audio/Pinball_th.mp3", 10.0f);
	app->hud->Start();

#pragma region Bumpers
	PhysBody* circularBumper = app->physics->CreateCircle(210, 95, 15, bodyType::STATIC);//BUmper1
	circularBumper->body->GetFixtureList()->SetRestitution(0.5f);

	circularBumper->ctype = ColliderType::BUMPER1;

	PhysBody* circularBumper2 = app->physics->CreateCircle(333, 205, 17, bodyType::STATIC);//BUmper2
	circularBumper2->body->GetFixtureList()->SetRestitution(1.3f);

	circularBumper2->ctype = ColliderType::BUMPER2;

	PhysBody* circularBumper3 = app->physics->CreateCircle(410, 190, 17, bodyType::STATIC);//BUmper3
	circularBumper3->body->GetFixtureList()->SetRestitution(1.3f);

	circularBumper3->ctype = ColliderType::BUMPER3;

	PhysBody* circularBumper4 = app->physics->CreateCircle(370, 250, 17, bodyType::STATIC);//BUmper4
	circularBumper4->body->GetFixtureList()->SetRestitution(1.3f);

	circularBumper4->ctype = ColliderType::BUMPER4;

	PhysBody* circularBumper5 = app->physics->CreateCircle(111, 440, 13, bodyType::STATIC);//BUmper5
	circularBumper5->body->GetFixtureList()->SetRestitution(1.3f);

	circularBumper5->ctype = ColliderType::BUMPER5;

	PhysBody* circularBumper6 = app->physics->CreateCircle(177, 457, 13, bodyType::STATIC);//BUmper6
	circularBumper6->body->GetFixtureList()->SetRestitution(1.3f);

	circularBumper6->ctype = ColliderType::BUMPER6;

	PhysBody* circularBumper7 = app->physics->CreateCircle(130, 488, 13, bodyType::STATIC);//BUmper7
	circularBumper7->body->GetFixtureList()->SetRestitution(1.3f);

	circularBumper7->ctype = ColliderType::BUMPER7;
#pragma endregion	

	PhysBody* smallRectU = app->physics->CreateRectangle(388, 125, 5, 20, bodyType::STATIC);
	smallRectU->ctype = ColliderType::RECTU;
	PhysBody* smallRectU2=app->physics->CreateRectangle(352, 125, 5, 20, bodyType::STATIC);
	smallRectU2->ctype = ColliderType::RECTU;
	PhysBody* smallRectD=app->physics->CreateRectangle(125, 387, 5, 20, bodyType::STATIC);
	smallRectD->ctype = ColliderType::RECTD;
	PhysBody* smallRectD2 = app->physics->CreateRectangle(158, 397, 5, 20, bodyType::STATIC);
	smallRectD2->ctype = ColliderType::RECTD;

#pragma region Obstacles escenari
	PhysBody* pb_estructuraEscenari = app->physics->CreateChain(0, 0, escenariGeneral, sizeEscenariGeneral, bodyType::STATIC);
	PhysBody* pb_outLaneRight = app->physics->CreateChain(0, 0, outLaneRight, sizeOutLaneRight, bodyType::STATIC);
	PhysBody* pb_outLaneLeft = app->physics->CreateChain(0, 0, outLaneLeft, sizeOutLaneLeft, bodyType::STATIC);
	PhysBody* pb_obstacleSuperiorDelTunel = app->physics->CreateChain(0, 0, obstacleSuperiorDelTunel, sizeObstacleSuperiorDelTunel, bodyType::STATIC);
	PhysBody* pb_tunnelFoc = app->physics->CreateChain(0, 0, tunnelFoc, sizeTunnelFoc, bodyType::STATIC);
	PhysBody* pb_tunnelLeftRight = app->physics->CreateChain(0, 0, tunnelLeftRight, sizetunnelLeftRight, bodyType::STATIC);
	PhysBody* pb_upperLeftObstacle = app->physics->CreateChain(0, 0, upperLeftObstacle, sizeupperLeftObstacle, bodyType::STATIC);
	PhysBody* pb_middleObstacle = app->physics->CreateChain(0, 0, middleObstacle, sizemiddleObstacle, bodyType::STATIC);
	PhysBody* pb_middleDRObstacle = app->physics->CreateChain(0, 0, middleDRObstacle, sizemiddleDRObstacle, bodyType::STATIC);
	PhysBody* pb_middleLRObstacle = app->physics->CreateChain(0, 0, middleLRObstacle, sizemiddleLRObstacle, bodyType::STATIC);
	PhysBody* pb_tunnelEnd = app->physics->CreateChain(0, 0, tunnelEnd, sizetunnelEnd, bodyType::STATIC);
	PhysBody* pb_tunnelELeft = app->physics->CreateChain(0, 0, tunnelELeft, sizetunnelELeft, bodyType::STATIC);
	PhysBody* pb_triangle1 = app->physics->CreateChain(0, 0, triangle1, sizetriangle1, bodyType::STATIC);
	PhysBody* pb_triangle2 = app->physics->CreateChain(0, 0, triangle2, sizetriangle2, bodyType::STATIC);
	//Palas
	_palaRight = app->physics->CreateRectangle(300, 765, 90, 20, bodyType::DYNAMIC);
	_palaRightPivot = app->physics->CreateCircle(265, 770, 0.5, bodyType::STATIC);
	_palaLeft = app->physics->CreateRectangle(440, 765, 90, 20, bodyType::DYNAMIC);
	_palaLeftPivot = app->physics->CreateCircle(475, 770, 0.5, bodyType::STATIC);


	b2RevoluteJointDef palaRightJoinDef;
	palaRightJoinDef.bodyA = _palaRightPivot->body;
	palaRightJoinDef.bodyB = _palaRight->body;
	palaRightJoinDef.collideConnected = false;
	palaRightJoinDef.lowerAngle = -45 * DEGTORAD;
	palaRightJoinDef.upperAngle = 45 * DEGTORAD;
	palaRightJoinDef.referenceAngle = 0;
	palaRightJoinDef.enableLimit = true;
	palaRightJoinDef.localAnchorA.Set(0, 0);
	palaRightJoinDef.localAnchorB.Set(-0.8, 0);
	b2RevoluteJoint* revoluteJointRight = (b2RevoluteJoint*)app->physics->world->CreateJoint(&palaRightJoinDef);

	b2RevoluteJointDef palaLeftJoinDef;
	palaLeftJoinDef.bodyA = _palaLeftPivot->body;
	palaLeftJoinDef.bodyB = _palaLeft->body;
	palaLeftJoinDef.collideConnected = false;
	palaLeftJoinDef.lowerAngle = -45 * DEGTORAD;
	palaLeftJoinDef.upperAngle = 45 * DEGTORAD;
	palaLeftJoinDef.referenceAngle = 0;
	palaLeftJoinDef.enableLimit = true;
	palaLeftJoinDef.localAnchorA.Set(0, 0);
	palaLeftJoinDef.localAnchorB.Set(0.8, 0);
	b2RevoluteJoint* revoluteJointLeft = (b2RevoluteJoint*)app->physics->world->CreateJoint(&palaLeftJoinDef);
#pragma endregion



	if (app->score != NULL) {
		app->score->Reset();
	}

	_texturaSprite_ = app->tex->Load("Assets/Textures/Game_Over.png");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	player->Update(dt);

	if (app->score->GetLives() <= 0 && bucle == false) {
		app->audio->PlayFx(sfx_Over);
		app->modules[7]->active = true;
		app->modules[6]->active = false;
		app->modules[9]->active = false;
		bucle = true;
	}

	//L02 DONE 3: Make the camera movement independent of framerate
	float camSpeed = 1;

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_UP)
	{
		// Passa a l'escena inicial
		app->modules[5]->active = true;
		app->modules[6]->active = false;
		app->modules[9]->active = false;
		gameover = false;
	}
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_UP)
	{
		// Passa a l'escena inicial

		gameover = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_UP)
	{
		// Passa a l'escena game over
		app->modules[7]->active = true;
		app->modules[6]->active = false;
		app->modules[9]->active = false;
		/*app->modules[6]->active = false;*/
		app->audio->PlayFx(sfx_Over);
		gameover = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		AnimSpring.PushBack({ 610,635,14,42 });
		AnimSpring.PushBack({ 610,625,14,42 });
		AnimSpring.PushBack({ 610,615,14,42 });
		AnimSpring.PushBack({ 610,605,14,42 });
		AnimSpring.PushBack({ 610,595,14,42 });
		AnimSpring.PushBack({ 650, 241, 6,  6 });
		AnimSpring.loop = false;
		AnimSpring.speed = 0.1f;
		app->audio->PlayFx(sfx_Spring);
	}
	// cambiar angle de rotacio de la pala
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		_palaRight->body->ApplyTorque(-80.0f, true);
	}
	else
	{
		_palaRight->body->ApplyTorque(45.0f, true);
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		app->audio->PlayFx(sfx_Pala);
	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		_palaLeft->body->ApplyTorque(80.0f, true);
	}
	else
	{
		_palaLeft->body->ApplyTorque(-45.0f, true);
	}
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		app->audio->PlayFx(sfx_Pala);
	}
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		player->Reset();
		gameover = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)
	{
		b2Vec2 gravity = app->physics->world->GetGravity();
		gravity.y += 1;
		if (gravity.y <= 0)
		{
			gravity.y = 0;
		}
		app->physics->world->SetGravity(gravity);
	}
	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
	{
		b2Vec2 gravity = app->physics->world->GetGravity();
		gravity.y -= 1;
		if (gravity.y <= 0)
		{
			gravity.y = 0;
		}
		app->physics->world->SetGravity(gravity);
	}



	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		app->render->camera.y += (int)ceil(camSpeed * dt);

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		app->render->camera.y -= (int)ceil(camSpeed * dt);

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		app->render->camera.x += (int)ceil(camSpeed * dt);

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		app->render->camera.x -= (int)ceil(camSpeed * dt);

	currentAnimBump1->Update();
	currentAnimBump2->Update();
	currentAnimBump3->Update();
	currentAnimBump4->Update();
	currentAnimBump5->Update();
	currentAnimBump6->Update();
	currentAnimBump7->Update();
	currentAnimLight1->Update();
	currentAnimLight2->Update();
	currentAnimLight3->Update();
	currentAnimLight4->Update();
	currentAnimLight5->Update();
	currentAnimLight6->Update();
	currentAnimArrow1->Update();
	currentAnimArrow1W->Update();
	currentAnimArrow1Q->Update();
	currentAnimArrow2->Update();
	currentAnimArrow2W->Update();
	currentAnimArrow2Q->Update();
	currentAnimArrow1D->Update();
	currentAnimArrow2D->Update();
	currentAnimSpring->Update();

	ballRect = { player->position.x, player->position.y, 16, 16 };

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	//app->render->DrawTexture(_texturaGeneral, 0, 0, &_rectEscenari);
	b2Vec2 gravity = app->physics->world->GetGravity();
	//Anim
	_rectBump1 = currentAnimBump1->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 185, 65, &_rectBump1);
	_rectBump2 = currentAnimBump2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 389, 157, &_rectBump2);
	_rectBump3 = currentAnimBump3->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 345, 229, &_rectBump3);
	_rectBump4 = currentAnimBump4->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 309, 175, &_rectBump4);
	_rectBump5 = currentAnimBump5->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 155, 435, &_rectBump5);
	_rectBump6 = currentAnimBump6->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 88, 415, &_rectBump6);
	_rectBump7 = currentAnimBump7->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 105, 465, &_rectBump7);

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
	_rectArrow1W = currentAnimArrow1W->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 300, 410, &_rectArrow1W);
	_rectArrow1Q = currentAnimArrow1Q->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 310, 433, &_rectArrow1Q);
	_rectArrow2 = currentAnimArrow2->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 477, 314, &_rectArrow2);
	_rectArrow2W = currentAnimArrow2W->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 457, 339, &_rectArrow2W);
	_rectArrow2Q = currentAnimArrow2Q->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 439, 365, &_rectArrow2Q);
	_rectArrow1D = currentAnimArrow1D->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 585, 690, &_rectArrow1D);
	_rectArrow2D = currentAnimArrow2D->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 91, 650, &_rectArrow2D);
	_rectSpring = currentAnimSpring->GetCurrentFrame();
	app->render->DrawTexture(_texturaSprite, 663, 780, &_rectSpring);
	//
	bool ret = true;
	if (app->score != NULL) {
		app->hud->PaintSentence(std::to_string(app->score->GetScore()), { 770, 400 });
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->hud->PaintSentence(std::to_string(gravity.y), { 920, 385 });
	app->hud->PaintSentence(std::to_string(app->score->GetLives()), { 1080, 300 });

	if (app->modules[7]->active == true || gameover == true)
	{
		app->render->DrawTexture(_texturaSprite_, 363, 380);
	}
	
	int xxx, yyy;
	int xxx2, yyy2;
	_palaRight->GetPosition(xxx, yyy);
	_palaLeft->GetPosition(xxx2, yyy2);

	app->render->DrawTexture(_texball, ballRect.x, ballRect.y, &_rectPelota);	
	app->render->DrawTexture(_texturaGeneral, xxx, yyy, &_rectPala1, 1, _palaRight->GetRotation());
	app->render->DrawTexture(_texturaGeneral, xxx2, yyy2, &_rectPala2, 1, _palaLeft->GetRotation());


	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::Create_circularBumper(int x, int y, int radious)
{
	PhysBody* circularBumper = app->physics->CreateCircle(x, y, radious, bodyType::STATIC);
	circularBumper->body->GetFixtureList()->SetRestitution(1.3f);

	circularBumper->ctype = ColliderType::BUMPER1;
}

void Scene::Create_rectangularBumper(int x, int y, int w, int h, float angle)
{
	PhysBody* rectangularBumper = app->physics->CreateRectangle(x, y, w, h, bodyType::STATIC);
	rectangularBumper->body->GetFixtureList()->SetRestitution(1.1f);
	int _angle = angle * M_PI / 180;
	b2Transform transform = rectangularBumper->body->GetTransform();
	transform.Set(transform.p, _angle);
	rectangularBumper->body->SetTransform(transform.p, transform.q.GetAngle());
	rectangularBumper->ctype = ColliderType::BUMPER;
}

