#ifndef __SCORE_H__
#define __SCORE_H__

#include "Module.h"
#include "Player.h"
#include "Animation.h"

class Score : public Module {

public:
    Score();
    ~Score();
    void AddPoints(int points);
    void restLives();
    void Reset();
    int GetScore() const;
    int Score::GetLives() const;
  
    int lives = 3;
private:
    int score = 0;
    

    
};

#endif