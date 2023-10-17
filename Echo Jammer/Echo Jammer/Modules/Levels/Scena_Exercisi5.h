#ifndef __SCENE_EXERCISI5_H__
#define __SCENE_EXERCISI5_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scena_Exercisi5 : public Module {

public:
	Scena_Exercisi5(bool startEnabled);
	~Scena_Exercisi5();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2) override;

	bool stopGame = false;

private:
	int _start_time;
	int _posicioAspidAleatoriX;

	SDL_Texture* _textura_fondo = nullptr;
	SDL_Texture* _textura_canon = nullptr;
	SDL_Texture* _textura_boom = nullptr;

	SDL_Rect _rectFondo;
	SDL_Rect _rectCanon;
	SDL_Rect _rectBallSprite;
	SDL_Rect _rectBall;
	SDL_Rect _rectAspid;
	SDL_Rect _rectIdleCanon;
	SDL_Rect _rectGround1;
	SDL_Rect _rectRectangle_1;
	SDL_Rect _rectRectangle_2;
	SDL_Rect _rectRectangle_3;
	SDL_Rect _rectRectangle_4;

	Animation _shootAnimation;
	Animation _aspidAnimation;
	Animation _explodeAnimation;

	Collider* _colliderBall = nullptr;
	Collider* _colliderAspid = nullptr;
	Collider* _colliderRectangle_1 = nullptr;
	Collider* _colliderRectangle_2 = nullptr;
	Collider* _colliderRectangle_3 = nullptr;
	Collider* _colliderRectangle_4 = nullptr;

	int _weigthNivell = 1000;
	int _heightNivell = 465;

	// Maquina estats
	bool _start = false; // Inici disparo
	bool _shooting = false; // Animacio disparo
	bool _boom = false; // Animacio exlposio

	// Formules
	int _gravetat = 550; //m/s^2
	float _alturaInicial = 256; // m
	int _graus = 30;
	float _alturaInicialDeslpassamentX = 200; // m
	float _angle = _graus * M_PI / 180; // Angle en radians
	float _temps = 0;

	//float _velocitatInicial = 70.00; // m/s
	int _velocitatInicial = 500; // m/s
	float _velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
	float _velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

	float _velocitat_X = _velocitatInicial_X;
	float _velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;

	float _position_X = _velocitat_X * _temps;
	float _position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));

};

#endif