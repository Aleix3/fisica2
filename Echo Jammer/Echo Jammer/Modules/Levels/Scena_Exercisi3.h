#ifndef __SCENE_EXERCISI3_H__
#define __SCENE_EXERCISI3_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scena_Exercisi3 : public Module {

public:
	Scena_Exercisi3(bool startEnabled);
	~Scena_Exercisi3();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2) override;

	bool stopGame = false;

private:
	int _start_time;

	SDL_Texture* _textura_fondo = nullptr;
	SDL_Texture* _textura_canon = nullptr;
	SDL_Texture* _textura_boom = nullptr;
	SDL_Rect _rectFondo;
	SDL_Rect _rectCanon;
	SDL_Rect _rectBall;

	Animation _shootAnimation;

	int _weigthNivell = 1000;
	int _heightNivell = 465;

	bool _start = false;
	bool _shooting = false;
	bool _endShoot = true;

	// Formules
	float _gravetat = 9.81; //m/s^2
	float _alturaInicial = 30; // m
	float _angle = 71 * M_PI / 180; // Angle en radians
	float _temps = 0;

	float _velocitatInicial = 9.00; // m/s
	float _velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
	float _velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

	float _velocitat_X = _velocitatInicial_X;
	float _velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;

	float _position_X;
	float _position_Y;

};

#endif