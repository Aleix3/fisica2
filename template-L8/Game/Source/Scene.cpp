#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Item.h"
#include "Physics.h"
#include "Defs.h"
#include "Log.h"

int escenariGeneral[110] = {
	679, 766,
	605, 203,
	594, 165,
	584, 145,
	568, 130,
	550, 111,
	525, 91,
	497, 69,
	470, 59,
	429, 48,
	392, 43,
	348, 40,
	322, 40,
	295, 47,
	268, 54,
	250, 41,
	231, 35,
	207, 35,
	187, 35,
	163, 44,
	159, 59,
	155, 78,
	159, 96,
	176, 106,
	187, 111,
	169, 133,
	155, 146,
	147, 167,
	138, 191,
	133, 217,
	134, 245,
	140, 263,
	130, 282,
	116, 294,
	105, 303,
	102, 329,
	98, 349,
	75, 483,
	91, 498,
	110, 507,
	110, 519,
	91, 541,
	81, 559,
	44, 763,
	91, 770,
	101, 703,
	218, 796,
	216, 845,
	522, 850,
	525, 794,
	586, 745,
	592, 760,
	606, 770,
	626, 767,
	636, 757
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

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node config)
{
	LOG("Loading Scene");
	bool ret = true;

	// TODO: Change player -> ball with physics
	//Instantiate the player using the entity manager
	//Get player paremeters
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	//Assigns the XML node to a member in player
	player->config = config.child("player");



	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	_velocitatInicial_Y = 2;
	// NOTE: We have to avoid the use of paths in the code, we will move it later to a config file
	PhysBody* c1 = app->physics->CreateRectangle(600, 735, 56, 64, bodyType::STATIC);
	c1->ctype = ColliderType::PLATFORM;

	_texturaGeneral = app->tex->Load("Assets/Textures/SpaceCadet3DPinball2.png");
	_textura_aspid = app->tex->Load("Assets/Textures/aspid2.png");
	//Music is commented so that you can add your own music
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	//Get the size of the window
	app->win->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	app->tex->GetSize(_textura_aspid, texW, texH);

	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;

	position.x = 600; position.y = 730;


	// L07 DONE 5: Add physics to the player - initialize physics body

	pbody = app->physics->CreateCircle(position.x, position.y, 15, bodyType::DYNAMIC);

	//Create_Bumper(30, 20, 20);

	for (int i = 0; i < 4; i++)
		_aspidAnimation.PushBack({ 29 * i + 2, 0, 29, 29 });
	_aspidAnimation.loop = true;
	_aspidAnimation.speed = 0.2f;

	_rectEscenari = { 0, 0, 1040, 855 };

	PhysBody* pb_estructuraEscenari = app->physics->CreateChain(0, 0, escenariGeneral, sizeEscenariGeneral, bodyType::STATIC);
	PhysBody* pb_outLaneRight = app->physics->CreateChain(0, 0, outLaneRight, sizeOutLaneRight, bodyType::STATIC);
	PhysBody* pb_outLaneLeft = app->physics->CreateChain(0, 0, outLaneLeft, sizeOutLaneLeft, bodyType::STATIC);
	PhysBody* pb_obstacleSuperiorDelTunel = app->physics->CreateChain(0, 0, obstacleSuperiorDelTunel, sizeObstacleSuperiorDelTunel, bodyType::STATIC);
	PhysBody* pb_tunnelFoc = app->physics->CreateChain(0, 0, tunnelFoc, sizeTunnelFoc, bodyType::STATIC);

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

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && suelo == true)
	{
		_graus = 0;
		_angle = _graus * M_PI / 180; // Angle en radians
		_temps = 0;

		_velocitatInicial_Y += 0.2;

		_velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && suelo == true)
	{
		velocity.y = -_velocitat_Y;
		pbody->body->SetLinearVelocity(velocity);
		_velocitatInicial_Y = 2;
		suelo = false;
	}

	b2Transform pbodyPos = pbody->body->GetTransform();

	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - 15;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - 15;

	// Renders the image in the center of the screen 
	//app->render->DrawTexture(img, (int)textPosX, (int)textPosY);

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	_aspidAnimation.Update();
	app->render->DrawTexture(_textura_aspid, position.x, position.y, &_aspidAnimation.GetCurrentFrame());
	//app->render->DrawTexture(_texturaGeneral, 0, 0, &_rectEscenari);

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

//void Scene::Create_Bumper(int x, int y, int radious)
//{
//	app->physics->CreateCircle(x, y, radious, STATIC);
//}