#include "Score.h"
Score::Score() : score(0)
{
}
Score::~Score()
{
}
void Score::AddPoints(int points)
{
    score += points;
}
void Score::Reset()
{
    score = 0;
}
int Score::GetScore() const
{
    return score;
}