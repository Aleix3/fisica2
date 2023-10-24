#pragma once
#include <cmath>
#include <corecrt_math_defines.h>

struct CosesTirParabolic
{
	int gravetat;
	float alturaInicial;
	float graus;
	float angle;
	float temps;
	int velocitatInicial;
	float velocitatInicial_X;
	float velocitatInicial_Y;
	float velocitat_X;
	float velocitat_Y;
	float posicio_X;
	float posicio_Y;
};

class TirParabolic
{

public:
	CosesTirParabolic Calculating(CosesTirParabolic objecteActual);

private:
	int _gravetat = 550; //m/s^2

	float _alturaInicial = 256; // m
	float _alturaInicialDeslpassamentX = 200; // m

	int _graus = 30;
	float _angle = _graus * M_PI / 180; // Angle en radians

	float _temps = 0;

	int _velocitatInicial = 500; // m/s
	float _velocitatInicial_X = _velocitatInicial * cos(_angle); // Vo * cos(angle) m/s
	float _velocitatInicial_Y = _velocitatInicial * sin(_angle); // Vo * sin(angle) m/s

	float _velocitat_X = _velocitatInicial_X;
	float _velocitat_Y = _velocitatInicial_Y - _gravetat * _temps;

	float _position_X = _velocitat_X * _temps;
	float _position_Y = _alturaInicial + (_velocitatInicial_Y * _temps) - (0.5 * _gravetat * (_temps * _temps));


};

