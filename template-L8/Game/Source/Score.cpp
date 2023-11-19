#include "App.h"
#include "Scene.h"
#include "Score.h"
#include "Player.h"
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

void Score::ResetCombo1() {
    app->player->bumper2Hit = false;
    app->player->bumper3Hit = false;
    app->player->bumper4Hit = false;
}

void Score::ResetCombo2() {
    app->player->bumper5Hit = false;
    app->player->bumper6Hit = false;
    app->player->bumper7Hit = false;
}


void Score::CheckCombo1() {
    if (app->player->bumper2Hit && app->player->bumper3Hit && app->player->bumper4Hit) {
        AddPoints(1000);
        ResetCombo1();
    }
}

void Score::CheckCombo2() {
    if (app->player->bumper5Hit && app->player->bumper6Hit && app->player->bumper7Hit) {
        AddPoints(1000);
        ResetCombo2();
    }
}

