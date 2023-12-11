#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Score.h"
#include "Animation.h"
#include "Render.h"
#include <vector>

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

	/*void calculateGravityForce(const Body& body1, const Body& body2, double& fx, double& fy);*/
	
private:
	SDL_Texture* _imgTerra;
	SDL_Texture* _imgLluna;

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

	PhysBody* cos1;
	PhysBody* cos2;
	
	std::vector<PhysBody*> vectorDeCossos;
};

#endif // __SCENE_H__