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
    void Reset();
    int GetScore() const;
private:
    int score = 0;

};

#endif