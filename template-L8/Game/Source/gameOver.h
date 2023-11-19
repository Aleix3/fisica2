#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "Module.h"
#include "SDL/include/SDL.h" 
#include "SDL_image/include/SDL_image.h" 

class gameOver : public Module {
public:
    gameOver();
    ~gameOver();

    bool Start() override;
    bool Update();
    bool PostUpdate();
    bool CleanUp();
    void DrawGameOver();

private:
    SDL_Texture* _gameOverText; 
};

#endif // __GAMEOVER_H__
