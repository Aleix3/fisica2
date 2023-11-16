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

int tunnelFoc[152] = {
	468, 268,
	479, 247,
	488, 229,
	493, 211,
	493, 198,
	486, 169,
	480, 160,
	468, 149,
	452, 128,
	441, 115,
	426, 115,
	418, 94,
	443, 78,
	452, 77,
	463, 83,
	476, 87,
	488, 94,
	494, 101,
	508, 109,
	516, 117,
	527, 127,
	538, 134,
	544, 152,
	549, 160,
	554, 170,
	561, 183,
	564, 198,
	565, 216,
	559, 249,
	556, 260,
	552, 279,
	544, 293,
	538, 304,
	531, 318,
	524, 334,
	518, 347,
	515, 334,
	523, 323,
	528, 305,
	535, 293,
	540, 279,
	544, 262,
	549, 241,
	549, 231,
	549, 214,
	547, 198,
	540, 183,
	534, 174,
	525, 158,
	518, 148,
	508, 140,
	501, 134,
	494, 128,
	483, 123,
	475, 118,
	464, 111,
	460, 108,
	453, 109,
	455, 119,
	474, 128,
	480, 136,
	491, 147,
	499, 154,
	506, 162,
	513, 170,
	517, 178,
	519, 197,
	520, 213,
	519, 221,
	516, 230,
	510, 241,
	505, 252,
	497, 265,
	487, 279,
	481, 275,
	474, 267
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
	294, 88,
	320, 106,
	319, 124,
	266, 149,
	260, 146,
	264, 110,
	273, 123,
	275, 136,
	313, 120,
	312, 109
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


Scene::Scene() : Module()
{
	name.Create("scene");
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

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	_velocitatInicial_Y = 2;

	_texturaGeneral = app->tex->Load("Assets/Textures/SpaceCadet3DPinball2.png");
	_textura_ball = app->tex->Load("Assets/Textures/aspid3.png");

	//Music is commented so that you can add your own music
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	//Get the size of the window
	app->win->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	app->tex->GetSize(_textura_ball, texW, texH);

	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;

	position.x = 650; position.y = 730;


	// L07 DONE 5: Add physics to the player - initialize physics body

	//pbody = app->physics->CreateCircle(position.x, position.y, 10, bodyType::DYNAMIC);
	pbody = app->physics->CreateCircle(position.x, position.y, 10, bodyType::DYNAMIC);

	Create_circularBumper(210, 95, 15);
	Create_circularBumper(333, 205, 17);
	Create_circularBumper(410, 190, 17);
	Create_circularBumper(370, 250, 17);

	Create_circularBumper(111, 440, 13);
	Create_circularBumper(177, 457, 13);
	Create_circularBumper(130, 488, 13);

	Create_rectangularBumper(388, 125, 5, 20); //rectangulars bumpers
	Create_rectangularBumper(352, 125, 5, 20);

	Create_rectangularBumper(125, 387, 5, 20);
	Create_rectangularBumper(158, 397, 5, 20);

	_ballAnimation.PushBack({ 37, 6, 25, 26 });
	_ballAnimation.loop = false;

	_rectEscenari = { 0, 0, 1040, 855 };

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
	b2Vec2 velocity = pbody->body->GetLinearVelocity();

	//L02 DONE 3: Make the camera movement independent of framerate
	float camSpeed = 1;

	// cambiar angle de rotacio de la pala
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		_palaRight->body->ApplyTorque(-40.0f, true);
	}
	else
	{
		_palaRight->body->ApplyTorque(45.0f, true);
	}
	

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		_palaLeft->body->ApplyTorque(40.0f, true);
	}
	else
	{
		_palaLeft->body->ApplyTorque(-45.0f, true);
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		_graus = 0;
		_angle = _graus * M_PI / 180; // Angle en radians
		_temps = 0;

		_velocitatInicial_Y += 0.2;

		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		velocity.y = -_velocitat_Y;
		pbody->body->SetLinearVelocity(velocity);
		_velocitatInicial_Y = 2;
		suelo = false;
	}
	b2Transform pbodyPos = pbody->body->GetTransform();

	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - 10;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - 10;

	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		position.x = 650;
		position.y = 750;
		app->physics->DestroyBody(pbody);
		pbody = app->physics->CreateCircle(position.x, position.y, 11, bodyType::DYNAMIC);
		/*pbody->listener = this;*/
		pbody->ctype = ColliderType::PLAYER;

	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	_ballAnimation.Update();
	//app->render->DrawTexture(_textura_ball, position.x, position.y, NULL, 1.0f, c->data->GetRotation());
	app->render->DrawTexture(_textura_ball, position.x, position.y, &_ballAnimation.GetCurrentFrame());
	//app->render->DrawTexture(_texturaGeneral, 0, 0, &_rectEscenari);

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
	circularBumper->body->GetFixtureList()->SetRestitution(1.5f);
}

void Scene::Create_rectangularBumper(int x, int y, int w, int h)
{
	PhysBody* rectangularBumper = app->physics->CreateRectangle(x, y, w, h, bodyType::STATIC);
	rectangularBumper->body->GetFixtureList()->SetRestitution(0.2f); 
}
