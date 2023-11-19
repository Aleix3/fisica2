#include "App.h"
#include "Scene.h"
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
void Score::restLives()
{
    lives = lives - 1;
}
void Score::Reset()
{
    score = 0;
   
}
int Score::GetScore() const
{
    return score;
}

int Score::GetLives() const
{
    return lives;
}