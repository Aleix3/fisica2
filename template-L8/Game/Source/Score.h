#pragma once

class Score
{
public:
    Score();
    ~Score();
    void AddPoints(int points);
    void Reset();
    int GetScore() const;
private:
    int score;
};
