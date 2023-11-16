#include "Score.h"

Score::Score() : score(0) // Inicializa la puntuaci�n a 0 en el constructor
{
}

Score::~Score()
{
    // Aqu� puedes liberar cualquier recurso que Score pueda haber adquirido
}

void Score::AddPoints(int points)
{
    score += points; // A�ade 'points' a 'score'
}

void Score::Reset()
{
    score = 0; // Resetea 'score' a 0
}

int Score::GetScore() const
{
    return score; // Devuelve la puntuaci�n actual
}
