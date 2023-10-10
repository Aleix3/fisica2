#ifndef __SCENE_EXERCISI4_H__
#define __SCENE_EXERCISI4_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scena_Exercisi4 : public Module {

public:
	Scena_Exercisi4(bool startEnabled);
	~Scena_Exercisi4();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2) override;

	bool stopGame = false;

public:
	int _start_time;

	SDL_Texture* _textura_fondo = nullptr;
	SDL_Texture* _textura_canon = nullptr;
	SDL_Rect _rectRectangle;
	SDL_Rect _rectRectangle_1;
	SDL_Rect _rectRectangle_2;
	SDL_Rect _rectRectangle_3;
	SDL_Rect _rectRectangle_4;
	SDL_Rect _rectFondo;
	SDL_Rect _rectCanon;
	SDL_Rect _rectBall;
	SDL_Rect _rectIdleCanon;
	SDL_Rect _rectGround1;

	Animation _shootAnimation;

	int _weigthNivell = 1000;
	int _heightNivell = 465;

	bool _start = false;
	bool _shooting = false;
	bool _endShoot = true;

	// Formules
	//float _gravetat = 9.81; //m/s^2
	float _gravetat = 550.00; //m/s^2
	float _alturaInicial = 256; // m
	float _graus = 30;
	float _alturaInicialDeslpassamentX = 200; // m
	float _angle = _graus * M_PI / 180; // Angle en radians
	float _temps = 0;

	//float _velocitatInicial = 70.00; // m/s
	float _velocitatInicial = 500.00; // m/s
	float _velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
	float _velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

	float _velocitat_X = _velocitatInicial_X;
	float _velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;

	float _position_X = _velocitat_X * _temps;
	float _position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));

};

#endif