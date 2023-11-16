#include "Score.h"

Score::Score() : score(0) // Inicializa la puntuación a 0 en el constructor
{
}

Score::~Score()
{
    // Aquí puedes liberar cualquier recurso que Score pueda haber adquirido
}

void Score::AddPoints(int points)
{
    score += points; // Añade 'points' a 'score'
}

void Score::Reset()
{
    score = 0; // Resetea 'score' a 0
}

int Score::GetScore() const
{
    return score; // Devuelve la puntuación actual
}
