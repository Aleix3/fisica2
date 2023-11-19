#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Score.h"
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
	/*Scene(bool startEnabled);*/
	
	void Create_circularBumper(int x, int y, int radious);
	void Create_rectangularBumper(int x, int y, int h, int w, float angle);

	PhysBody* pbody;
	PhysBody* c1;
	iPoint position;
	float jumpSpeed = 5.0f;
	bool suelo = false;


private:
	Score* score;
	SDL_Texture* img;
	float textPosX, textPosY = 0;

	Player* player;

	SDL_Rect _rectBump1;
	Animation* currentAnimBump1 = nullptr;
	Animation AnimBump1;
	SDL_Rect _rectBump2;
	Animation* currentAnimBump2 = nullptr;
	Animation AnimBump2;
	SDL_Rect _rectBump3;
	Animation* currentAnimBump3 = nullptr;
	Animation AnimBump3;
	SDL_Rect _rectBump4;
	Animation* currentAnimBump4 = nullptr;
	Animation AnimBump4;
	SDL_Rect _rectBump5;
	Animation* currentAnimBump5 = nullptr;
	Animation AnimBump5;
	SDL_Rect _rectBump6;
	Animation* currentAnimBump6 = nullptr;
	Animation AnimBump6;
	SDL_Rect _rectBump7;
	Animation* currentAnimBump7 = nullptr;
	Animation AnimBump7;

	SDL_Rect _rectLight1;
	Animation* currentAnimLight1 = nullptr;
	Animation AnimLight1;
	SDL_Rect _rectLight2;
	Animation* currentAnimLight2 = nullptr;
	Animation AnimLight2;
	SDL_Rect _rectLight3;
	Animation* currentAnimLight3 = nullptr;
	Animation AnimLight3;
	SDL_Rect _rectLight4;
	Animation* currentAnimLight4 = nullptr;
	Animation AnimLight4;
	SDL_Rect _rectLight5;
	Animation* currentAnimLight5 = nullptr;
	Animation AnimLight5;
	SDL_Rect _rectLight6;
	Animation* currentAnimLight6 = nullptr;
	Animation AnimLight6;


	SDL_Texture* _textura_aspid = nullptr;
	SDL_Texture* _texturaSprite = nullptr;
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

	//FOnt
	SDL_Surface* numberSurface = nullptr;
	SDL_Texture* numberTexture = nullptr;
	SDL_Rect numberRects[10];
	int widthOfEachNumber = 15;  // Ancho de cada número en la imagen
	int heightOfEachNumber = 21;  // Altura de cada número en la imagen
	int xPosition = 200;  // Posición x donde empezar a dibujar la puntuación
	int yPosition = 300;  // Posición y donde empezar a dibujar la puntuación

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