#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Animation.h"

struct SDL_Texture;

class Scene : public Module{

public:
	Scene();
	virtual ~Scene();
	bool Awake(pugi::xml_node config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void Create_circularBumper(int x, int y, int radious);
	void Create_rectangularBumper(int x, int y, int h, int w, float angle);

	PhysBody* pbody;
	PhysBody* c1;
	iPoint position;
	float jumpSpeed = 5.0f;
	bool suelo = false;


private:
	SDL_Texture* img;
	float textPosX, textPosY = 0;

	Player* player;

	SDL_Texture* _textura_aspid = nullptr;

	SDL_Texture* _texturaGeneral = nullptr;
	SDL_Rect _rectEscenari;
	SDL_Rect _rectMarcadors;
	SDL_Rect _rectPalaRight;
	SDL_Rect _rectPalaLeft;

	PhysBody* _palaRight;
	PhysBody* _palaRightPivot;
	PhysBody* _palaLeft;
	PhysBody* _palaLeftPivot;
	float _angleRadiansPalaRight = 0.0f;
	float _limitAngleRadiansPalaRight = -0.7854f;
	float _angleRadiansPalaLeft = 0.0f;
	float _limitAngleRadiansPalaLeft = 0.7854f;

	// Fisiques
	int _gravetat = 550; //m/s^2
	float _alturaInicial = 256; // m
	int _graus = 30;
	float _alturaInicialDeslpassamentX = 200; // m
	float _angle = _graus * M_PI / 180; // Angle en radians
	float _temps = 0;

	int _velocitatInicial = 5; // m/s
	float _velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
	float _velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

	float _velocitat_X = _velocitatInicial_X;
	float _velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;

	float _position_X = _velocitat_X * _temps;
	float _position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));

};

#endif // __SCENE_H__